/*
 * LogFilterProxyModel.cpp
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

#include "LogFilterProxyModel.h"

LogFilterProxyModel::LogFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

void LogFilterProxyModel::setLevelFilter(const QString& level)
{
    m_levelFilter = level;
    invalidateFilter();
}

void LogFilterProxyModel::setModuleFilter(const QString& module)
{
    m_moduleFilter = module;
    invalidateFilter();
}

void LogFilterProxyModel::setSearchText(const QString& searchText)
{
    m_searchText = searchText.trimmed();
    invalidateFilter();
}

bool LogFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
{
    QModelIndex levelIndex = sourceModel()->index(sourceRow, LogTableModel::LevelColumn, sourceParent);
    QModelIndex moduleIndex = sourceModel()->index(sourceRow, LogTableModel::ModuleColumn, sourceParent);

    QString level = sourceModel()->data(levelIndex, Qt::DisplayRole).toString();
    QString module = sourceModel()->data(moduleIndex, Qt::DisplayRole).toString();

    bool levelMatches = (m_levelFilter == "ALL") || (level == m_levelFilter);
    bool moduleMatches = (m_moduleFilter == "ALL") || (module == m_moduleFilter);

    bool searchMatches = true;

    if (!m_searchText.isEmpty()) {
        searchMatches = false;

        for (int column = 0; column < LogTableModel::ColumnCount; ++column) {
            QModelIndex idx = sourceModel()->index(sourceRow, column, sourceParent);
            QString value = sourceModel()->data(idx, Qt::DisplayRole).toString();

            if (value.contains(m_searchText, Qt::CaseInsensitive)) {
                searchMatches = true;
                break;
            }
        }
    }

    return levelMatches && moduleMatches && searchMatches;
}
