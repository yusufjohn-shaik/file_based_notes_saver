#ifndef NOTE_MANAGER_H
#define NOTE_MANAGER_H

#include "Note.h"
#include "BackupManager.h"
#include <vector>
#include <string>

class NoteManager {
private:
    std::vector<Note> notes;
    std::string dataFilePath;
    BackupManager backupManager;

    int generateNextId() const;

public:
    NoteManager(const std::string& filePath = "notes.txt",
                const std::string& backupPath = "notes_backup.txt");

    // Initialization and Persistence
    bool loadNotes(std::string& errorMessage);
    bool saveNotes(std::string& errorMessage);

    // Note Operations (CRUD)
    Note createNote(const std::string& title, const std::string& content, const std::string& category);
    bool updateNote(int id, const std::string& newTitle, const std::string& newContent, const std::string& newCategory, std::string& errorMessage);
    bool deleteNote(int id, std::string& errorMessage);

    // Queries
    const std::vector<Note>& getAllNotes() const;
    const Note* getNoteById(int id) const;
    bool noteExists(int id) const;
    size_t getNoteCount() const;

    // Sorting & Ordering
    void setNotes(const std::vector<Note>& newNotes);

    // Backup & Restore
    bool performBackup(std::string& statusMessage);
    bool performRestore(std::string& statusMessage);

    const std::string& getDataFilePath() const;
};

#endif // NOTE_MANAGER_H
