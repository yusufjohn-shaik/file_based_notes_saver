# How to Run File-Based Notes Saver

This guide provides simple, step-by-step instructions to compile and run the **File-Based Notes Saver** application on **Windows**, **Linux**, and **macOS**.

---

## 🪟 Running on Windows

### Method 1: Automated Script (Easiest)

You can launch the program in one step using the included batch scripts:

1. Open **Command Prompt (`cmd`)** or **PowerShell** in the project folder.
2. Run:
   ```cmd
   run.bat
   ```
   *Tip: You can also simply double-click `run.bat` in File Explorer.*
   
*This script automatically checks for MinGW `g++`, Visual Studio `cl.exe`, or CMake, compiles the code if needed, and starts the program.*

---

### Method 2: Using MinGW-w64 / GCC (`g++`)

If you have MinGW installed:

1. Open **Command Prompt** or **PowerShell** in the project directory:
   ```cmd
   cd "path\to\file based notes saver"
   ```
2. Compile the project:
   ```cmd
   g++ -std=c++17 -Wall -Wextra -Iinclude src\*.cpp -o notes_saver.exe
   ```
3. Run the application:
   ```cmd
   .\notes_saver.exe
   ```

---

### Method 3: Using Microsoft Visual Studio (MSVC)

If you have Visual Studio installed:

1. Open the **x64 Native Tools Command Prompt for VS** from the Windows Start menu.
2. Navigate to the project folder:
   ```cmd
   cd "path\to\file based notes saver"
   ```
3. Compile with the Microsoft C++ compiler:
   ```cmd
   cl /EHsc /std:c++17 /Iinclude src\*.cpp /Fe:notes_saver.exe
   ```
4. Run the executable:
   ```cmd
   .\notes_saver.exe
   ```

---

### Method 4: Using CMake on Windows

If you prefer CMake:

1. Generate build files:
   ```cmd
   cmake -B build
   ```
2. Build the executable:
   ```cmd
   cmake --build build --config Release
   ```
3. Run the program:
   ```cmd
   .\build\Release\notes_saver.exe
   ```

---

### Method 5: In Visual Studio Code (VS Code)

1. Open the project folder in VS Code (`File` → `Open Folder...`).
2. Open the integrated terminal (`Ctrl` + `~`).
3. Run:
   ```cmd
   .\run.bat
   ```
   *(Or compile directly with `g++ -std=c++17 -Iinclude src\*.cpp -o notes_saver.exe`)*

---

### Method 6: Using Windows Subsystem for Linux (WSL)

If you have WSL enabled on Windows:

1. Open your WSL terminal (e.g., Ubuntu).
2. Navigate to the project folder:
   ```bash
   cd "/mnt/c/path/to/file based notes saver"
   ```
3. Build and execute:
   ```bash
   make
   ./notes_saver
   ```

---

## 🐧 Running on Linux & macOS

### Using GNU Make

1. Open your terminal in the project directory:
   ```bash
   cd "/home/shaikyusufjohn/file based notes saver"
   ```
2. Build the project:
   ```bash
   make
   ```
3. Run the application:
   ```bash
   make run
   # or run directly:
   ./notes_saver
   ```
<!--"""cd "/home/john/academic projects/cpp/file based notes saver"
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o /tmp/notes_saver
/tmp/notes_saver"""-->
### Manual Compilation with g++ / clang++

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude src/*.cpp -o notes_saver
./notes_saver
```

### Using CMake on Linux / macOS

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
./notes_saver
```

---

## 🧪 Running the Automated Test Suite

To verify that all 8 modules (CRUD, search, sort, file I/O, backup/restore) pass verification:

### On Linux / macOS:
```bash
make test
```

### On Windows (MinGW):
```cmd
g++ -std=c++17 -Iinclude src\Utils.cpp src\Note.cpp src\FileManager.cpp src\InputValidator.cpp src\SearchEngine.cpp src\NoteSorter.cpp src\BackupManager.cpp src\NoteManager.cpp tests\test_runner.cpp -o run_tests.exe
.\run_tests.exe
```

---

## 💡 Troubleshooting & Tips

- **Compiler not recognized on Windows**: If `g++` is not recognized, ensure MinGW's `bin` folder (e.g., `C:\msys64\mingw64\bin` or `C:\MinGW\bin`) is added to your Windows `PATH` environment variable.
- **Notes Storage**: All notes are permanently saved to `notes.txt` in the same directory. Backups are saved to `notes_backup.txt`.
- **Colors**: Windows Terminal and modern PowerShell/CMD natively display ANSI colors. If running in an older CMD window, standard text is shown without errors.
