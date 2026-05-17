# CanLogAnalyzer

A powerful Qt-based application for analyzing and visualizing CAN (Controller Area Network) bus logs. CanLogAnalyzer provides an intuitive interface for parsing, filtering, and exporting CAN log data for automotive and industrial applications.

## Features

- **CAN Log Parsing**: Fast and reliable parsing of CAN log files
- **Interactive Data Visualization**: Display CAN messages in an organized table format with real-time filtering
- **Advanced Filtering**: Filter logs by message ID, data content, and other parameters
- **Statistical Analysis**: Generate detailed statistics from log data
- **CSV Export**: Export filtered or complete logs to CSV format for further analysis
- **Multi-language Support**: Built-in translator support for international users
- **Cross-platform**: Built with Qt for Windows, Linux, and macOS compatibility

## Project Structure

```
CanLogAnalyzer/
├── Forms/                      # Qt Designer UI files
├── sample_logs/                # Example CAN log files for testing
├── MainWindow.h/cpp            # Main application window
├── LogParser.h/cpp             # CAN log file parser
├── LogEntry.h                  # Log entry data structure
├── LogTableModel.h/cpp         # Table model for displaying logs
├── LogFilterProxyModel.h/cpp   # Filtering and proxy model
├── LogStatistics.h/cpp         # Statistical analysis module
├── CsvExporter.h/cpp           # CSV export functionality
├── AppTranslator.h/cpp         # Translation/localization support
├── CMakeLists.txt              # CMake build configuration
├── main.cpp                    # Application entry point
└── README.md                   # This file
```

## Requirements

- **Qt Framework**: Qt 5.x or Qt 6.x
- **C++ Compiler**: C++11 or later (GCC, Clang, MSVC)
- **CMake**: Version 3.10 or higher
- **Operating System**: Linux, Windows, or macOS

## Building from Source

### Prerequisites

On **Ubuntu/Debian**:
```bash
sudo apt-get install qt5-qmake qt5-default libqt5core5a libqt5gui5 cmake build-essential
```

On **Fedora/RHEL**:
```bash
sudo dnf install qt5-qtbase qt5-qtbase-devel cmake gcc-c++
```

On **macOS** (with Homebrew):
```bash
brew install qt cmake
```

On **Windows**:
- Install Qt from https://www.qt.io/download
- Install Visual Studio Build Tools or MinGW
- Install CMake from https://cmake.org/download/

### Build Steps

1. Clone the repository:
```bash
git clone https://github.com/Ibn3abad/CanLogAnalyzer.git
cd CanLogAnalyzer
```

2. Create a build directory:
```bash
mkdir build
cd build
```

3. Configure with CMake:
```bash
cmake ..
```

4. Build the project:
```bash
cmake --build .
```

5. Run the application:
```bash
./CanLogAnalyzer
```

## Usage

### Opening a CAN Log File

1. Launch CanLogAnalyzer
2. Click **File → Open** or use `Ctrl+O`
3. Select a CAN log file (supported formats: .log, .txt, .csv)
4. The log data will be loaded and displayed in the main table

### Filtering Log Data

- Use the **Filter Panel** to search by:
  - **Message ID**: Filter by CAN identifier (decimal or hexadecimal)
  - **Data Content**: Search within payload data
  - **Timestamp Range**: Narrow down by time window
- Click **Apply Filter** to update the display
- Click **Clear Filter** to reset

### Analyzing Statistics

1. Select a log file or filtered data
2. Go to **Tools → Statistics**
3. View insights including:
   - Message frequency distribution
   - Data payload analysis
   - Timestamp statistics
   - Error rate analysis

### Exporting Data

1. After filtering or analyzing data
2. Click **File → Export as CSV**
3. Choose destination file and format options
4. The filtered log will be saved in CSV format for use in Excel, MATLAB, or other tools

### Sample Logs

Example CAN log files are provided in the `sample_logs/` directory for testing and demonstration purposes.

## Architecture

### Core Components

- **LogParser**: Reads and parses various CAN log formats into internal data structures
- **LogEntry**: Represents a single CAN message with timestamp, ID, and data payload
- **LogTableModel**: Qt table model providing efficient data display and sorting
- **LogFilterProxyModel**: Implements filtering without modifying original data
- **LogStatistics**: Performs statistical calculations on log data
- **CsvExporter**: Handles exporting filtered logs to CSV format
- **AppTranslator**: Manages multi-language support

## Configuration

The application can be configured through:
- **Settings Menu**: Application preferences and display options
- **Config Files**: Default settings stored in user directory (platform-dependent)

## Troubleshooting

### Application won't start
- Verify Qt libraries are properly installed: `qmake --version`
- Check that all dependencies are available on your system

### Log file not recognized
- Ensure the file format is supported (typically .log or .txt)
- Check that the file is a valid CAN log with proper format
- Review sample logs for format reference

### Performance issues with large files
- Consider filtering logs before opening to reduce memory usage
- Export to CSV and analyze in smaller chunks
- Check available RAM for files larger than 1GB

## Contributing

Contributions are welcome! Please:

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/YourFeature`
3. Commit changes: `git commit -am 'Add new feature'`
4. Push to branch: `git push origin feature/YourFeature`
5. Submit a Pull Request

## License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

## Author

**Ibn3abad** - https://github.com/Ibn3abad

## Support

For issues, feature requests, or questions:
- Open an [Issue](https://github.com/Ibn3abad/CanLogAnalyzer/issues) on GitHub
- Check existing issues for similar problems
- Provide detailed information including OS, Qt version, and error messages

## Related Resources

- [Qt Documentation](https://doc.qt.io/)
- [CAN Bus Overview](https://en.wikipedia.org/wiki/CAN_bus)
- [CMake Documentation](https://cmake.org/documentation/)

## Changelog

### Version 1.0.0 (Initial Release)
- CAN log file parsing and display
- Interactive filtering and search
- CSV export functionality
- Statistical analysis tools
- Multi-language support
- Cross-platform compatibility

---

**Last Updated**: May 2026  
**Status**: Active Development
