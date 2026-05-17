/*
 * LogTableModel.cpp
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

#include "LogTableModel.h"

LogTableModel::LogTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int LogTableModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return m_entries.size();
}

int LogTableModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid()) {
        return 0;
    }

    return ColumnCount;
}

QVariant LogTableModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid()) {
        return {};
    }

    if (index.row() < 0 || index.row() >= m_entries.size()) {
        return {};
    }

    const LogEntry& entry = m_entries[index.row()];

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case TimestampColumn:
            return entry.timestamp;
        case LevelColumn:
            return entry.level;
        case ModuleColumn:
            return entry.module;
        case MessageColumn:
            return entry.message;
        default:
            return {};
        }
    }

    if (role == Qt::BackgroundRole) {
        if (entry.level == "ERROR") {
            return QColor(120, 30, 30);   // dunkles Rot, gut für Dark Mode
        }

        if (entry.level == "WARN") {
            return QColor(120, 95, 20);   // dunkles Gelb/Braun
        }

        if (entry.level == "INFO") {
            return QColor(35, 55, 75);    // dezentes Blau
        }
    }

    if (role == Qt::ForegroundRole) {
        if (entry.level == "ERROR" || entry.level == "WARN" || entry.level == "INFO") {
            return QColor(245, 245, 245); // helle Schrift
        }
    }


    return {};
}

QVariant LogTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) {
        return {};
    }

    switch (section) {
    case TimestampColumn:
        return "Timestamp";
    case LevelColumn:
        return "Level";
    case ModuleColumn:
        return "Module";
    case MessageColumn:
        return "Message";
    default:
        return {};
    }
}

void LogTableModel::setEntries(const QVector<LogEntry>& entries)
{
    beginResetModel();
    m_entries = entries;
    endResetModel();
}

const QVector<LogEntry>& LogTableModel::entries() const
{
    return m_entries;
}

LogEntry LogTableModel::entryAt(int row) const
{
    if (row < 0 || row >= m_entries.size()) {
        return {};
    }

    return m_entries[row];
}
