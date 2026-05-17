/*
 * MainWindow.cpp
 * 
 * Copyright (c) 2024 A. Khouk
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "CsvExporter.h"
#include "LogParser.h"
#include "LogStatistics.h"

#include <QApplication>
#include <QDragEnterEvent>
#include <QFileDialog>
#include <QHeaderView>
#include <QMap>
#include <QMessageBox>
#include <QMimeData>
#include <QSignalBlocker>
#include <QUrl>
#include <QtConcurrent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAcceptDrops(true);

    logTableModel = new LogTableModel(this);
    filterProxyModel = new LogFilterProxyModel(this);
    filterProxyModel->setSourceModel(logTableModel);

    setupTable();
    setupFilter();
    setupLanguageSelector();

    connect(&fileLoadWatcher, &QFutureWatcher<QVector<LogEntry>>::finished,
            this, &MainWindow::onFileLoaded);

    applyLanguage();
    statusBar()->showMessage(text("ready"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupTable()
{
    ui->logTableView->setModel(filterProxyModel);
    ui->logTableView->setSortingEnabled(true);
    ui->logTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->logTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->logTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->logTableView->horizontalHeader()->setStretchLastSection(true);
    ui->logTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->logTableView->sortByColumn(LogTableModel::TimestampColumn, Qt::AscendingOrder);
}

void MainWindow::setupFilter()
{
    ui->levelFilterComboBox->addItem("ALL");
    ui->levelFilterComboBox->addItem("ERROR");
    ui->levelFilterComboBox->addItem("WARN");
    ui->levelFilterComboBox->addItem("INFO");

    ui->moduleFilterComboBox->addItem("ALL");
}

void MainWindow::setupLanguageSelector()
{
    ui->languageComboBox->addItem("English");
    ui->languageComboBox->addItem("Deutsch");
    ui->languageComboBox->addItem("العربية");
    ui->languageComboBox->setCurrentIndex(0);
}

QString MainWindow::text(const QString& key) const
{
    return translator.text(key);
}

void MainWindow::applyLanguage()
{
    setWindowTitle(text("windowTitle"));

    ui->openLogButton->setText(text("openLog"));
    ui->exportCsvButton->setText(text("exportCsv"));
    ui->statisticsButton->setText(text("statistics"));

    ui->filterLabel->setText(text("levelFilter"));
    ui->moduleFilterLabel->setText(text("moduleFilter"));
    ui->searchLabel->setText(text("search"));
    ui->languageLabel->setText(text("language"));
    ui->searchLineEdit->setPlaceholderText(text("searchPlaceholder"));
    ui->dropHintLabel->setText(text("dropHint"));

    ui->aboutButton->setText(text("about"));

    updateStatusBar();
}

void MainWindow::on_languageComboBox_currentIndexChanged(int index)
{
    if (index == 0) {
        translator.setLanguage(AppLanguage::English);
        qApp->setLayoutDirection(Qt::LeftToRight);
    } else if (index == 1) {
        translator.setLanguage(AppLanguage::German);
        qApp->setLayoutDirection(Qt::LeftToRight);
    } else if (index == 2) {
        translator.setLanguage(AppLanguage::Arabic);
        qApp->setLayoutDirection(Qt::RightToLeft);
    }

    applyLanguage();
}

void MainWindow::on_openLogButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        text("openDialog"),
        "",
        "Log files (*.txt *.log *.csv);;All files (*.*)"
    );

    if (filePath.isEmpty()) {
        return;
    }

    loadFileAsync(filePath);
}

void MainWindow::loadFileAsync(const QString& filePath)
{
    if (fileLoadWatcher.isRunning()) {
        return;
    }

    progressDialog = new QProgressDialog(text("loading"), QString(), 0, 0, this);
    progressDialog->setWindowModality(Qt::WindowModal);
    progressDialog->setCancelButton(nullptr);
    progressDialog->show();

    auto future = QtConcurrent::run([filePath]() {
        LogParser parser;
        return parser.parseFile(filePath);
    });

    fileLoadWatcher.setFuture(future);
}

void MainWindow::onFileLoaded()
{
    if (progressDialog != nullptr) {
        progressDialog->close();
        progressDialog->deleteLater();
        progressDialog = nullptr;
    }

    allEntries = fileLoadWatcher.result();

    if (allEntries.isEmpty()) {
        QMessageBox::warning(
            this,
            text("noValidLogsTitle"),
            text("noValidLogsText")
        );
    }

    logTableModel->setEntries(allEntries);

    updateModuleFilter();
    applyCurrentFilter();
    ui->logTableView->resizeColumnsToContents();
    updateStatusBar();
}

void MainWindow::updateModuleFilter()
{
    QString currentModule = ui->moduleFilterComboBox->currentText();

    QSignalBlocker blocker(ui->moduleFilterComboBox);

    ui->moduleFilterComboBox->clear();
    ui->moduleFilterComboBox->addItem("ALL");

    QStringList modules;

    for (const LogEntry& entry : allEntries) {
        if (!modules.contains(entry.module)) {
            modules.append(entry.module);
        }
    }

    modules.sort();

    for (const QString& module : modules) {
        ui->moduleFilterComboBox->addItem(module);
    }

    int index = ui->moduleFilterComboBox->findText(currentModule);
    ui->moduleFilterComboBox->setCurrentIndex(index >= 0 ? index : 0);
}

void MainWindow::on_exportCsvButton_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(
        this,
        text("exportDialog"),
        "",
        "CSV files (*.csv);;All files (*.*)"
    );

    if (filePath.isEmpty()) {
        return;
    }

    CsvExporter exporter;

    if (!exporter.exportToCsv(filePath, visibleEntries())) {
        QMessageBox::warning(this, text("error"), text("csvCreateError"));
        return;
    }

    QMessageBox::information(this, text("export"), text("csvSuccess"));
}

void MainWindow::on_statisticsButton_clicked()
{
    showErrorStatistics();
}

void MainWindow::on_levelFilterComboBox_currentTextChanged(const QString &value)
{
    Q_UNUSED(value);
    applyCurrentFilter();
    updateStatusBar();
}

void MainWindow::on_moduleFilterComboBox_currentTextChanged(const QString &value)
{
    Q_UNUSED(value);
    applyCurrentFilter();
    updateStatusBar();
}

void MainWindow::on_searchLineEdit_textChanged(const QString &value)
{
    Q_UNUSED(value);
    applyCurrentFilter();
    updateStatusBar();
}

void MainWindow::applyCurrentFilter()
{
    filterProxyModel->setLevelFilter(ui->levelFilterComboBox->currentText());
    filterProxyModel->setModuleFilter(ui->moduleFilterComboBox->currentText());
    filterProxyModel->setSearchText(ui->searchLineEdit->text());
}

QVector<LogEntry> MainWindow::visibleEntries() const
{
    QVector<LogEntry> entries;

    for (int proxyRow = 0; proxyRow < filterProxyModel->rowCount(); ++proxyRow) {
        QModelIndex proxyIndex = filterProxyModel->index(proxyRow, 0);
        QModelIndex sourceIndex = filterProxyModel->mapToSource(proxyIndex);

        if (!sourceIndex.isValid()) {
            continue;
        }

        entries.append(logTableModel->entryAt(sourceIndex.row()));
    }

    return entries;
}

void MainWindow::updateStatusBar()
{
    LogStatistics statistics;
    QMap<QString, int> levelCounts = statistics.countByLevel(allEntries);

    QString message = QString("%1: %2 | %3: %4 | ERROR: %5 | WARN: %6 | INFO: %7")
                          .arg(text("visible"))
                          .arg(filterProxyModel->rowCount())
                          .arg(text("total"))
                          .arg(allEntries.size())
                          .arg(levelCounts.value("ERROR"))
                          .arg(levelCounts.value("WARN"))
                          .arg(levelCounts.value("INFO"));

    statusBar()->showMessage(message);
}

void MainWindow::showErrorStatistics()
{
    LogStatistics statistics;
    QMap<QString, int> errorCountByModule = statistics.errorCountByModule(visibleEntries());

    QString result;

    for (auto it = errorCountByModule.begin(); it != errorCountByModule.end(); ++it) {
        result += it.key() + ": " + QString::number(it.value()) + " ERROR\n";
    }

    if (result.isEmpty()) {
        result = text("noErrors");
    }

    QMessageBox::information(this, text("statisticsTitle"), result);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (!event->mimeData()->hasUrls()) {
        return;
    }

    const QList<QUrl> urls = event->mimeData()->urls();

    if (urls.isEmpty()) {
        return;
    }

    QString filePath = urls.first().toLocalFile();

    if (filePath.endsWith(".txt", Qt::CaseInsensitive)
        || filePath.endsWith(".log", Qt::CaseInsensitive)
        || filePath.endsWith(".csv", Qt::CaseInsensitive)) {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    const QList<QUrl> urls = event->mimeData()->urls();

    if (urls.isEmpty()) {
        return;
    }

    QString filePath = urls.first().toLocalFile();

    if (!filePath.isEmpty()) {
        loadFileAsync(filePath);
    }
}

/*void MainWindow::on_aboutButton_clicked()
{
    QMessageBox aboutBox(this);

    aboutBox.setWindowTitle("About CanLogAnalyzer");
    aboutBox.setIcon(QMessageBox::Information);

    aboutBox.setText(
        "<h2>CanLogAnalyzer</h2>"
        "<p>A C++/Qt desktop application for loading, filtering, analyzing, "
        "and exporting automotive-style log files.</p>"

        "<p><b>Developer:</b> Ibn Abad Obayda</p>"
        "<p><b>License:</b> MIT License</p>"

        "<p><b>GitHub:</b><br>"
        "<a href='https://github.com/Ibn3abad/CanLogAnalyzer'>"
        "https://github.com/Ibn3abad/CanLogAnalyzer"
        "</a></p>"

        "<p>Copyright (c) 2026 Ibn Abad Obayda</p>"
        );

    aboutBox.setTextFormat(Qt::RichText);
    aboutBox.setTextInteractionFlags(Qt::TextBrowserInteraction);
    aboutBox.setStandardButtons(QMessageBox::Ok);

    aboutBox.exec();
}*/

void MainWindow::on_aboutButton_clicked()
{
    QMessageBox aboutBox(this);

    aboutBox.setWindowTitle(text("aboutTitle"));
    aboutBox.setIcon(QMessageBox::Information);
    aboutBox.setText(text("aboutText"));

    aboutBox.setTextFormat(Qt::RichText);
    aboutBox.setTextInteractionFlags(Qt::TextBrowserInteraction);
    aboutBox.setStandardButtons(QMessageBox::Ok);

    aboutBox.exec();
}