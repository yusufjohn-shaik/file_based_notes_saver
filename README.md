# File-Based Notes Saver (C++)

A robust, modular, terminal-based C++ application designed to help users create, store, manage, search, organize, sort, and safeguard personal notes directly from the command line.

The system uses C++ file streams (`std::ifstream`, `std::ofstream`) to permanently persist notes across sessions on the local filesystem.

---

## 📑 Table of Contents
- [Architecture & Major Modules](#architecture--major-modules)
- [Directory Structure](#directory-structure)
- [Storage Format (`notes.txt`)](#storage-format-notestxt)
- [Requirements & Toolchain](#requirements--toolchain)
- [Building & Running](#building--running)
- [Running Automated Tests](#running-automated-tests)
- [Menu & Feature Walkthrough](#menu--feature-walkthrough)
  - [1. Create Note](#1-create-note)
  - [2. View All Notes](#2-view-all-notes)
  - [3. View Note by ID](#3-view-note-by-id)
  - [4. Edit Note](#4-edit-note)
  - [5. Delete Note](#5-delete-note)
  - [6. Search Notes](#6-search-notes)
  - [7. Categories & Filtering](#7-categories--filtering)
  - [8. Sort Notes](#8-sort-notes)
  - [9. Backup Notes](#9-backup-notes)
  - [10. Restore Notes](#10-restore-notes)
- [Input Validation & Error Handling](#input-validation--error-handling)

---

## 🏛️ Architecture & Major Modules

The application is structured into the 8 major modules specified by the project requirements:

| Module | Files | Description |
| :--- | :--- | :--- |
| **Module 1 — User Interface (TUI)** | `UI.h`, `UI.cpp` | Interactive terminal menus, banners, screen transitions, and ANSI colors. |
| **Module 2 — Note Management** | `NoteManager.h`, `NoteManager.cpp` | In-memory CRUD coordination, auto-ID generation, and state tracking. |
| **Module 3 — File Management** | `FileManager.h`, `FileManager.cpp` | File stream operations (`ifstream`/`ofstream`), persistence, and file status checks. |
| **Module 4 — Search & Organization** | `SearchEngine.h`, `SearchEngine.cpp` | Multi-field keyword searching and category management with note counts. |
| **Module 5 — Sorting** | `NoteSorter.h`, `NoteSorter.cpp` | Custom `std::sort` lambdas for Title, Date, Category, and ID in Asc/Desc order. |
| **Module 6 — Input Validation & Error Handling** | `InputValidator.h`, `InputValidator.cpp` | Buffer clearing, type validation, range checking, and safe error recovery. |
| **Module 7 — Backup & Restore** | `BackupManager.h`, `BackupManager.cpp` | One-click snapshot backups and confirmation-protected file restoration. |
| **Module 8 — Data Model** | `Note.h`, `Note.cpp` | Core `Note` class encapsulating ID, Title, Content, Category, Date, and serialization. |

---

## 📁 Directory Structure

```
file based notes saver/
├── bin/                       # Output binaries
├── data/                      # Dedicated data directory
├── include/                   # Header files (.h)
│   ├── BackupManager.h
│   ├── FileManager.h
│   ├── InputValidator.h
│   ├── Note.h
│   ├── NoteManager.h
│   ├── NoteSorter.h
│   ├── SearchEngine.h
│   ├── UI.h
│   └── Utils.h
├── src/                       # Implementation files (.cpp)
│   ├── BackupManager.cpp
│   ├── FileManager.cpp
│   ├── InputValidator.cpp
│   ├── Note.cpp
│   ├── NoteManager.cpp
│   ├── NoteSorter.cpp
│   ├── SearchEngine.cpp
│   ├── UI.cpp
│   ├── Utils.cpp
│   └── main.cpp
├── tests/                     # Unit & integration test suite
│   └── test_runner.cpp
├── CMakeLists.txt             # CMake build configuration
├── Makefile                   # GNU Make automation
├── notes.txt                  # Permanent file storage
├── notes_backup.txt           # Safety backup file
└── README.md                  # Complete documentation
```

---

## 💾 Storage Format (`notes.txt`)

Notes are stored in a human-readable, tag-delimited block format that supports multiline content without data corruption:

```text
# File-Based Notes Saver Storage File
[NOTE_START]
ID: 1024
TITLE: C++ File Handling
CATEGORY: Programming
CREATED: 26-09-2026
CONTENT_START
Today I learned about ifstream and ofstream.
Streams provide a clean, object-oriented way to perform file I/O operations in C++.
CONTENT_END
[NOTE_END]
```

---

## ⚙️ Requirements & Toolchain

- **OS**: Linux / Unix / macOS / Windows (WSL/MinGW)
- **Compiler**: `g++` or `clang++` with C++17 support
- **Build System**: GNU Make 4.0+ or CMake 3.10+

---

## 🔨 Building & Running

### 🪟 On Windows

You can build and run on Windows using any of the following methods:

#### Method 1: Automated Batch Script (Easiest)
Simply double-click [`run.bat`](file:///home/shaikyusufjohn/file%20based%20notes%20saver/run.bat) or execute it from Command Prompt / PowerShell:
```cmd
run.bat
```
*(This automatically detects MinGW `g++`, Visual Studio `cl.exe`, or CMake, compiles `notes_saver.exe`, and starts the app).*

#### Method 2: Using MinGW / GCC (`g++`)
From Command Prompt or PowerShell in the project directory:
```cmd
g++ -std=c++17 -Wall -Wextra -Iinclude src\*.cpp -o notes_saver.exe
.\notes_saver.exe
```

#### Method 3: Using Microsoft Visual C++ (MSVC / Developer Command Prompt)
Open "x64 Native Tools Command Prompt for VS" and run:
```cmd
cl /EHsc /std:c++17 /Iinclude src\*.cpp /Fe:notes_saver.exe
.\notes_saver.exe
```

#### Method 4: Using CMake on Windows
```cmd
cmake -B build
cmake --build build --config Release
.\build\Release\notes_saver.exe
```

---

### 🐧 On Linux / macOS

#### Using GNU Make

```bash
# Build the application
make

# Run the application
make run
# or directly:
./notes_saver
```

### Using CMake

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
./notes_saver
```

---

## 🧪 Running Automated Tests

A dedicated test runner tests all 8 modules (data model serialization, file persistence, CRUD operations, searching, sorting, and backup/restore):

```bash
make test
```

Expected Output:
```text
=========================================
  RUNNING FILE-BASED NOTES SAVER TESTS   
=========================================

[RUNNING] testNoteModel ... [PASSED]
[RUNNING] testFileManager ... [PASSED]
[RUNNING] testNoteManagerCRUD ... [PASSED]
[RUNNING] testSearchEngine ... [PASSED]
[RUNNING] testNoteSorter ... [PASSED]
[RUNNING] testBackupAndRestore ... [PASSED]

=========================================
Results: 6 Passed, 0 Failed
=========================================
```

---

## 📋 Menu & Feature Walkthrough

When launched, the interactive terminal menu appears:

```text
=================================
       FILE-BASED NOTES SAVER    
=================================

1. Create Note
2. View All Notes
3. View Note
4. Edit Note
5. Delete Note
6. Search Notes
7. Categories
8. Sort Notes
9. Backup Notes
10. Restore Notes
11. Exit

Enter your choice:
```

### 1. Create Note
- Prompts for Note Title, Multiline Content (finish by typing `END` on a new line), and Category.
- Automatically generates a unique sequential ID (starting at 1024).
- Saves directly to `notes.txt`.

### 2. View All Notes
- Displays a clean list of all notes with ID, Title, Category, and Creation Date.
- Allows viewing the full content of any note by typing its ID.

### 3. View Note by ID
- Displays formatted card view with ID, Title, Category, Date, and full Content.
- Validates note existence and handles invalid inputs gracefully.

### 4. Edit Note
- Submenu allowing modifications to:
  1. Title
  2. Content
  3. Category
  4. All Fields
  5. Cancel
- Changes are immediately saved to disk.

### 5. Delete Note
- Confirms deletion with a safety prompt: `[Y/N]`.
- Permanently removes the note from memory and rewrites `notes.txt`.

### 6. Search Notes
- Case-insensitive keyword search across **Title**, **Content**, and **Category**.
- Displays matching results in `[ID] Title` format with quick-view access.

### 7. Categories & Filtering
- Displays all categories with note count metrics.
- Allows selecting any category to filter and view notes belonging exclusively to that category.

### 8. Sort Notes
- Sorting criteria:
  1. Title (Alphabetical)
  2. Date (Chronological)
  3. Category
  4. Note ID
- Order: Ascending or Descending.
- Option to view temporarily or save the sorted order permanently to file.

### 9. Backup Notes
- Copies `notes.txt` to `notes_backup.txt`.
- Logs timestamp and confirmation.

### 10. Restore Notes
- Validates backup file existence.
- Prompts for confirmation before overwriting current data.
- Automatically synchronizes in-memory notes upon restoration.

---

## 🛡️ Input Validation & Error Handling

- **Non-blocking Integer Parsing**: Handles non-numeric inputs (e.g., `abc`) without infinite loops or crashes using `std::stoi` and input buffer sanitization.
- **Empty String Prevention**: Disallows blank note titles or empty required fields.
- **Bounds Checking**: Enforces menu limits (1-11) and valid ID ranges.
- **File Safety**: Handles missing data files gracefully on startup by initializing clean storage.
- **EOF & Signal Protection**: Gracefully exits without hanging when EOF (`Ctrl+D`) is encountered.
