/*
 * AppTranslator.cpp
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

#include "AppTranslator.h"

void AppTranslator::setLanguage(AppLanguage language)
{
    m_language = language;
}

AppLanguage AppTranslator::language() const
{
    return m_language;
}

QString AppTranslator::text(const QString& key) const
{
    if (m_language == AppLanguage::English) {
        if (key == "windowTitle") return "Can Log Analyzer";
        if (key == "openLog") return "Open Log File";
        if (key == "exportCsv") return "Export CSV";
        if (key == "statistics") return "Show Statistics";
        if (key == "levelFilter") return "Level Filter:";
        if (key == "moduleFilter") return "Module Filter:";
        if (key == "search") return "Search:";
        if (key == "language") return "Language:";
        if (key == "searchPlaceholder") return "Search logs...";
        if (key == "dropHint") return "Tip: You can drag and drop a .txt/.log/.csv file into this window.";
        if (key == "ready") return "Ready";
        if (key == "loading") return "Loading log file...";
        if (key == "openDialog") return "Open log file";
        if (key == "exportDialog") return "Export CSV";
        if (key == "error") return "Error";
        if (key == "csvCreateError") return "The CSV file could not be created.";
        if (key == "csvSuccess") return "CSV was exported successfully.";
        if (key == "export") return "Export";
        if (key == "noValidLogsTitle") return "No valid logs";
        if (key == "noValidLogsText") return "The file was read, but no valid log lines were found.\n\nExpected format:\nTimestamp;Level;Module;Message";
        if (key == "statisticsTitle") return "Error statistics by module";
        if (key == "noErrors") return "No ERROR entries found.";
        if (key == "visible") return "Visible";
        if (key == "total") return "Total";
        if (key == "about") return "About App";
        if (key == "aboutTitle") return "About CanLogAnalyzer";
        if (key == "aboutText") {
            return "<h2>CanLogAnalyzer</h2>"
                   "<p>A C++/Qt desktop application for loading, filtering, analyzing, "
                   "and exporting automotive-style log files.</p>"
                   "<p><b>Developer:</b> A. Khouk</p>"
                   "<p><b>License:</b> MIT License</p>"
                   "<p><b>GitHub:</b><br>"
                   "<a href='https://github.com/Ibn3abad/CanLogAnalyzer'>"
                   "https://github.com/Ibn3abad/CanLogAnalyzer"
                   "</a></p>"
                   "<p>Copyright (c) 2024 A. Khouk</p>";
        }
    }

    if (m_language == AppLanguage::German) {
        if (key == "windowTitle") return "CAN Log Analyzer";
        if (key == "openLog") return "Logdatei öffnen";
        if (key == "exportCsv") return "CSV exportieren";
        if (key == "statistics") return "Statistik anzeigen";
        if (key == "levelFilter") return "Level Filter:";
        if (key == "moduleFilter") return "Modul Filter:";
        if (key == "search") return "Suche:";
        if (key == "language") return "Sprache:";
        if (key == "searchPlaceholder") return "Logs durchsuchen...";
        if (key == "dropHint") return "Tipp: Du kannst eine .txt/.log/.csv Datei per Drag & Drop in dieses Fenster ziehen.";
        if (key == "ready") return "Bereit";
        if (key == "loading") return "Logdatei wird geladen...";
        if (key == "openDialog") return "Logdatei öffnen";
        if (key == "exportDialog") return "CSV exportieren";
        if (key == "error") return "Fehler";
        if (key == "csvCreateError") return "CSV-Datei konnte nicht erstellt werden.";
        if (key == "csvSuccess") return "CSV wurde erfolgreich exportiert.";
        if (key == "export") return "Export";
        if (key == "noValidLogsTitle") return "Keine gültigen Logs";
        if (key == "noValidLogsText") return "Die Datei konnte gelesen werden, aber es wurden keine gültigen Logzeilen gefunden.\n\nErwartetes Format:\nTimestamp;Level;Module;Message";
        if (key == "statisticsTitle") return "Fehlerstatistik pro Modul";
        if (key == "noErrors") return "Keine ERROR-Einträge gefunden.";
        if (key == "visible") return "Sichtbar";
        if (key == "total") return "Gesamt";
        if (key == "about") return "Über die App";
        if (key == "aboutTitle") return "Über CanLogAnalyzer";
        if (key == "aboutText") {
            return "<h2>CanLogAnalyzer</h2>"
                   "<p>Eine C++/Qt Desktop-Anwendung zum Laden, Filtern, Analysieren "
                   "und Exportieren von Automotive-Logdateien.</p>"
                   "<p><b>Entwickler:</b> A. Khouk</p>"
                   "<p><b>Lizenz:</b> MIT License</p>"
                   "<p><b>GitHub:</b><br>"
                   "<a href='https://github.com/Ibn3abad/CanLogAnalyzer'>"
                   "https://github.com/Ibn3abad/CanLogAnalyzer"
                   "</a></p>"
                   "<p>Copyright (c) 2024 A. Khouk</p>";
        }
    }

    if (m_language == AppLanguage::Arabic) {
        if (key == "windowTitle") return "محلل سجلات CAN";
        if (key == "openLog") return "فتح ملف السجل";
        if (key == "exportCsv") return "تصدير CSV";
        if (key == "statistics") return "عرض الإحصائيات";
        if (key == "levelFilter") return "فلتر المستوى:";
        if (key == "moduleFilter") return "فلتر الوحدة:";
        if (key == "search") return "بحث:";
        if (key == "language") return "اللغة:";
        if (key == "searchPlaceholder") return "البحث في السجلات...";
        if (key == "dropHint") return "ملاحظة: يمكنك سحب ملف .txt أو .log أو .csv وإفلاته داخل هذه النافذة.";
        if (key == "ready") return "جاهز";
        if (key == "loading") return "جاري تحميل ملف السجل...";
        if (key == "openDialog") return "فتح ملف السجل";
        if (key == "exportDialog") return "تصدير CSV";
        if (key == "error") return "خطأ";
        if (key == "csvCreateError") return "تعذر إنشاء ملف CSV.";
        if (key == "csvSuccess") return "تم تصدير ملف CSV بنجاح.";
        if (key == "export") return "تصدير";
        if (key == "noValidLogsTitle") return "لا توجد سجلات صالحة";
        if (key == "noValidLogsText") return "تمت قراءة الملف، ولكن لم يتم العثور على أسطر سجل صالحة.\n\nالصيغة المتوقعة:\nTimestamp;Level;Module;Message";
        if (key == "statisticsTitle") return "إحصائيات الأخطاء حسب الوحدة";
        if (key == "noErrors") return "لم يتم العثور على إدخالات ERROR.";
        if (key == "visible") return "المعروض";
        if (key == "total") return "الإجمالي";
        if (key == "about") return "حول التطبيق";
        if (key == "aboutTitle") return "حول CanLogAnalyzer";
        if (key == "aboutText") {
            return "<h2>CanLogAnalyzer</h2>"
                   "<p>تطبيق سطح مكتب باستخدام C++ و Qt لتحميل سجلات السيارات "
                   "وتصفيتها وتحليلها وتصديرها.</p>"
                   "<p><b>المطور:</b> A. Khouk</p>"
                   "<p><b>الرخصة:</b> MIT License</p>"
                   "<p><b>GitHub:</b><br>"
                   "<a href='https://github.com/Ibn3abad/CanLogAnalyzer'>"
                   "https://github.com/Ibn3abad/CanLogAnalyzer"
                   "</a></p>"
                   "<p>Copyright (c) 2024 A. Khouk</p>";
        }
    }

    return key;
}
