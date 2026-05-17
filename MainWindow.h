/*
 * MainWindow.h
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

#pragma once

#include "AppTranslator.h"
#include "LogEntry.h"
#include "LogFilterProxyModel.h"
#include "LogTableModel.h"

#include <QFutureWatcher>
#include <QMainWindow>
#include <QProgressDialog>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

private slots:
    void on_openLogButton_clicked();
    void on_exportCsvButton_clicked();
    void on_statisticsButton_clicked();
    void on_aboutButton_clicked();

    void on_levelFilterComboBox_currentTextChanged(const QString &text);
    void on_moduleFilterComboBox_currentTextChanged(const QString &text);
    void on_searchLineEdit_textChanged(const QString &text);
    void on_languageComboBox_currentIndexChanged(int index);

private:
    void setupTable();
    void setupFilter();
    void setupLanguageSelector();

    void applyLanguage();
    QString text(const QString& key) const;

    void loadFileAsync(const QString& filePath);
    void onFileLoaded();

    void updateModuleFilter();
    void applyCurrentFilter();
    void updateStatusBar();
    void showErrorStatistics();

    QVector<LogEntry> visibleEntries() const;

private:
    Ui::MainWindow *ui;

    LogTableModel *logTableModel = nullptr;
    LogFilterProxyModel *filterProxyModel = nullptr;

    QVector<LogEntry> allEntries;

    QFutureWatcher<QVector<LogEntry>> fileLoadWatcher;
    QProgressDialog *progressDialog = nullptr;

    AppTranslator translator;
};
