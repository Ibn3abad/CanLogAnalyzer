# CMakeLists.txt
# 
# Copyright (c) 2024 A. Khouk
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.16)

project(CanLogAnalyzer VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Concurrent)

qt_standard_project_setup()

set(CMAKE_AUTOUIC_SEARCH_PATHS Forms)

qt_add_executable(CanLogAnalyzer
    main.cpp
    MainWindow.h
    MainWindow.cpp
    LogEntry.h
    LogParser.h
    LogParser.cpp
    LogTableModel.h
    LogTableModel.cpp
    LogFilterProxyModel.h
    LogFilterProxyModel.cpp
    CsvExporter.h
    CsvExporter.cpp
    LogStatistics.h
    LogStatistics.cpp
    AppTranslator.h
    AppTranslator.cpp
    Forms/MainWindow.ui
)

target_link_libraries(CanLogAnalyzer
    PRIVATE
        Qt6::Widgets
        Qt6::Concurrent
)
