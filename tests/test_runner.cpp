#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>
#include <string>
#include <cstdio>
#include "Note.h"
#include "FileManager.h"
#include "NoteManager.h"
#include "SearchEngine.h"
#include "NoteSorter.h"
#include "BackupManager.h"
#include "Utils.h"

#define ASSERT_TRUE(condition, message) \
    do { \
        if (!(condition)) { \
            std::cerr << "\033[31m[FAILED]\033[0m " << message << " at line " << __LINE__ << std::endl; \
            return false; \
        } \
    } while (0)

#define RUN_TEST(testFunc) \
    do { \
        std::cout << "\033[36m[RUNNING]\033[0m " #testFunc " ... "; \
        if (testFunc()) { \
            std::cout << "\033[32m[PASSED]\033[0m\n"; \
            passedCount++; \
        } else { \
            failedCount++; \
        } \
    } while (0)

bool testNoteModel() {
    Note n1(1024, "C++ File Handling", "Today I learned about ifstream and ofstream.", "Programming", "26-09-2026");
    ASSERT_TRUE(n1.getId() == 1024, "Note ID must be 1024");
    ASSERT_TRUE(n1.getTitle() == "C++ File Handling", "Title match");
    ASSERT_TRUE(n1.getContent() == "Today I learned about ifstream and ofstream.", "Content match");
    ASSERT_TRUE(n1.getCategory() == "Programming", "Category match");
    ASSERT_TRUE(n1.getCreatedDate() == "26-09-2026", "CreatedDate match");

    std::stringstream ss;
    n1.serialize(ss);

    Note n2;
    bool success = Note::deserialize(ss, n2);
    ASSERT_TRUE(success, "Deserialization should succeed");
    ASSERT_TRUE(n2.getId() == 1024, "Deserialized ID must match");
    ASSERT_TRUE(n2.getTitle() == n1.getTitle(), "Deserialized Title must match");
    ASSERT_TRUE(n2.getContent() == n1.getContent(), "Deserialized Content must match");
    ASSERT_TRUE(n2.getCategory() == n1.getCategory(), "Deserialized Category must match");
    ASSERT_TRUE(n2.getCreatedDate() == n1.getCreatedDate(), "Deserialized CreatedDate must match");

    return true;
}

bool testFileManager() {
    const std::string testFile = "test_notes.txt";
    std::remove(testFile.c_str());

    std::vector<Note> notes;
    notes.emplace_back(1024, "Note 1", "Content 1\nMultiline", "Tech", "26-09-2026");
    notes.emplace_back(1025, "Note 2", "Content 2", "Personal", "27-09-2026");

    std::string err;
    bool saveOk = FileManager::saveNotes(testFile, notes, err);
    ASSERT_TRUE(saveOk, "FileManager::saveNotes should succeed: " + err);
    ASSERT_TRUE(FileManager::fileExists(testFile), "Test file must exist on disk");

    std::vector<Note> loadedNotes;
    bool loadOk = FileManager::loadNotes(testFile, loadedNotes, err);
    ASSERT_TRUE(loadOk, "FileManager::loadNotes should succeed: " + err);
    ASSERT_TRUE(loadedNotes.size() == 2, "Loaded notes count must be 2");
    ASSERT_TRUE(loadedNotes[0].getId() == 1024, "Loaded note 1 ID match");
    ASSERT_TRUE(loadedNotes[0].getContent() == "Content 1\nMultiline", "Multiline content preservation match");
    ASSERT_TRUE(loadedNotes[1].getId() == 1025, "Loaded note 2 ID match");

    std::remove(testFile.c_str());
    return true;
}

bool testNoteManagerCRUD() {
    const std::string testFile = "test_notes_crud.txt";
    const std::string testBackup = "test_backup_crud.txt";
    std::remove(testFile.c_str());
    std::remove(testBackup.c_str());

    NoteManager manager(testFile, testBackup);
    std::string err;
    manager.loadNotes(err);
    ASSERT_TRUE(manager.getNoteCount() == 0, "Initial count should be 0");

    // Create Note 1
    Note n1 = manager.createNote("C++ File Handling", "Today I learned about ifstream and ofstream.", "Programming");
    ASSERT_TRUE(n1.getId() == 1024, "First note ID should be 1024");
    ASSERT_TRUE(manager.getNoteCount() == 1, "Count should be 1");

    // Create Note 2
    Note n2 = manager.createNote("DSA Revision", "Binary Trees and Heaps", "College");
    ASSERT_TRUE(n2.getId() == 1025, "Second note ID should be 1025");
    ASSERT_TRUE(manager.getNoteCount() == 2, "Count should be 2");

    // Verify retrieval
    const Note* found = manager.getNoteById(1024);
    ASSERT_TRUE(found != nullptr, "Note 1024 should be found");
    ASSERT_TRUE(found->getTitle() == "C++ File Handling", "Title should match");

    // Update Note 1
    bool updated = manager.updateNote(1024, "Advanced C++ File Handling", "", "", err);
    ASSERT_TRUE(updated, "Update should succeed");
    const Note* updatedNote = manager.getNoteById(1024);
    ASSERT_TRUE(updatedNote->getTitle() == "Advanced C++ File Handling", "Updated title match");
    ASSERT_TRUE(updatedNote->getContent() == "Today I learned about ifstream and ofstream.", "Content should remain");

    // Delete Note 2
    bool deleted = manager.deleteNote(1025, err);
    ASSERT_TRUE(deleted, "Delete should succeed");
    ASSERT_TRUE(manager.getNoteCount() == 1, "Count should be 1 after deletion");
    ASSERT_TRUE(manager.getNoteById(1025) == nullptr, "Deleted note should not be found");

    // Reload from file to ensure persistence
    NoteManager reloadedManager(testFile, testBackup);
    reloadedManager.loadNotes(err);
    ASSERT_TRUE(reloadedManager.getNoteCount() == 1, "Reloaded manager should have 1 note");
    ASSERT_TRUE(reloadedManager.getNoteById(1024) != nullptr, "Reloaded note should exist");

    std::remove(testFile.c_str());
    std::remove(testBackup.c_str());
    return true;
}

bool testSearchEngine() {
    std::vector<Note> notes;
    notes.emplace_back(1024, "C++ File Handling", "Today I learned about ifstream and ofstream.", "Programming", "26-09-2026");
    notes.emplace_back(1027, "C++ OOP Concepts", "Inheritance, Polymorphism, Encapsulation", "Programming", "26-09-2026");
    notes.emplace_back(1031, "C++ DSA Practice", "Graphs and Dynamic Programming", "College", "27-09-2026");
    notes.emplace_back(1035, "Shopping List", "Apples, Milk, Bread", "Personal", "28-09-2026");

    // Search by keyword "C++"
    auto resCpp = SearchEngine::searchByKeyword(notes, "C++");
    ASSERT_TRUE(resCpp.size() == 3, "Keyword 'C++' should match 3 notes");

    // Search by keyword "ifstream" (in content)
    auto resStream = SearchEngine::searchByKeyword(notes, "ifstream");
    ASSERT_TRUE(resStream.size() == 1, "Keyword 'ifstream' should match 1 note");
    ASSERT_TRUE(resStream[0].getId() == 1024, "Matched ID must be 1024");

    // Search by Category "Programming"
    auto resProg = SearchEngine::searchByCategory(notes, "Programming");
    ASSERT_TRUE(resProg.size() == 2, "Category search should match 2 notes");

    // Check categories list
    auto cats = SearchEngine::getAllCategories(notes);
    ASSERT_TRUE(!cats.empty(), "Categories should not be empty");

    auto counts = SearchEngine::getCategoryCounts(notes);
    ASSERT_TRUE(counts["Programming"] == 2, "Programming count should be 2");
    ASSERT_TRUE(counts["College"] == 1, "College count should be 1");
    ASSERT_TRUE(counts["Personal"] == 1, "Personal count should be 1");

    return true;
}

bool testNoteSorter() {
    std::vector<Note> notes;
    notes.emplace_back(1030, "Zebra Patterns", "Content", "Graphics", "10-09-2026");
    notes.emplace_back(1010, "Algorithm Analysis", "Content", "Algorithms", "05-09-2026");
    notes.emplace_back(1020, "Binary Trees", "Content", "Data Structures", "20-09-2026");

    // Sort by Title Ascending
    NoteSorter::sortNotes(notes, NoteSorter::SortField::Title, true);
    ASSERT_TRUE(notes[0].getTitle() == "Algorithm Analysis", "Title Asc first should be Algorithm Analysis");
    ASSERT_TRUE(notes[2].getTitle() == "Zebra Patterns", "Title Asc last should be Zebra Patterns");

    // Sort by Title Descending
    NoteSorter::sortNotes(notes, NoteSorter::SortField::Title, false);
    ASSERT_TRUE(notes[0].getTitle() == "Zebra Patterns", "Title Desc first should be Zebra Patterns");

    // Sort by ID Ascending
    NoteSorter::sortNotes(notes, NoteSorter::SortField::Id, true);
    ASSERT_TRUE(notes[0].getId() == 1010, "ID Asc first should be 1010");
    ASSERT_TRUE(notes[1].getId() == 1020, "ID Asc middle should be 1020");
    ASSERT_TRUE(notes[2].getId() == 1030, "ID Asc last should be 1030");

    // Sort by Date Ascending
    NoteSorter::sortNotes(notes, NoteSorter::SortField::Date, true);
    ASSERT_TRUE(notes[0].getCreatedDate() == "05-09-2026", "Earliest date first");
    ASSERT_TRUE(notes[2].getCreatedDate() == "20-09-2026", "Latest date last");

    return true;
}

bool testBackupAndRestore() {
    const std::string testFile = "test_src.txt";
    const std::string testBackup = "test_backup.txt";
    std::remove(testFile.c_str());
    std::remove(testBackup.c_str());

    NoteManager manager(testFile, testBackup);
    manager.createNote("Original Note", "Important Content", "Work");

    std::string status;
    bool backedUp = manager.performBackup(status);
    ASSERT_TRUE(backedUp, "Backup creation should succeed: " + status);
    ASSERT_TRUE(FileManager::fileExists(testBackup), "Backup file must exist");

    // Now modify original by adding another note and deleting the original
    manager.createNote("Second Note", "New Content", "Personal");
    ASSERT_TRUE(manager.getNoteCount() == 2, "Count should now be 2");

    // Restore from backup
    bool restored = manager.performRestore(status);
    ASSERT_TRUE(restored, "Restore should succeed: " + status);
    ASSERT_TRUE(manager.getNoteCount() == 1, "Count after restore should be 1");
    ASSERT_TRUE(manager.getAllNotes()[0].getTitle() == "Original Note", "Restored note title should match");

    std::remove(testFile.c_str());
    std::remove(testBackup.c_str());
    return true;
}

int main() {
    std::cout << "\n=========================================\n";
    std::cout << "  RUNNING FILE-BASED NOTES SAVER TESTS   \n";
    std::cout << "=========================================\n\n";

    int passedCount = 0;
    int failedCount = 0;

    RUN_TEST(testNoteModel);
    RUN_TEST(testFileManager);
    RUN_TEST(testNoteManagerCRUD);
    RUN_TEST(testSearchEngine);
    RUN_TEST(testNoteSorter);
    RUN_TEST(testBackupAndRestore);

    std::cout << "\n=========================================\n";
    std::cout << "Results: " << passedCount << " Passed, " << failedCount << " Failed\n";
    std::cout << "=========================================\n\n";

    return (failedCount == 0) ? 0 : 1;
}
