/*
 * CsvExporter.cpp
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

#include "CsvExporter.h"

#include <QFile>
#include <QTextStream>

bool CsvExporter::exportToCsv(const QString& filePath, const QVector<LogEntry>& entries) const
{
    QFile file(filePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&file);
    out << "Timestamp;Level;Module;Message\n";

    for (const LogEntry& entry : entries) {
        out << escapeCsvField(entry.timestamp) << ";"
            << escapeCsvField(entry.level) << ";"
            << escapeCsvField(entry.module) << ";"
            << escapeCsvField(entry.message) << "\n";
    }

    return true;
}

QString CsvExporter::escapeCsvField(const QString& value) const
{
    QString escaped = value;
    escaped.replace("\"", "\"\"");

    if (escaped.contains(';') || escaped.contains('"') || escaped.contains('\n')) {
        escaped = "\"" + escaped + "\"";
    }

    return escaped;
}
