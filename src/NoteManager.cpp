#include "NoteManager.h"
#include "FileManager.h"
#include "Utils.h"
#include <algorithm>

NoteManager::NoteManager(const std::string& filePath, const std::string& backupPath)
    : dataFilePath(filePath), backupManager(filePath, backupPath) {}

int NoteManager::generateNextId() const {
    int maxId = 1023; // First generated ID will be 1024
    for (const auto& note : notes) {
        if (note.getId() > maxId) {
            maxId = note.getId();
        }
    }
    return maxId + 1;
}

bool NoteManager::loadNotes(std::string& errorMessage) {
    return FileManager::loadNotes(dataFilePath, notes, errorMessage);
}

bool NoteManager::saveNotes(std::string& errorMessage) {
    return FileManager::saveNotes(dataFilePath, notes, errorMessage);
}

Note NoteManager::createNote(const std::string& title, const std::string& content, const std::string& category) {
    int id = generateNextId();
    std::string date = Utils::getCurrentDate();
    std::string cat = category.empty() ? "General" : category;
    
    Note note(id, title, content, cat, date);
    notes.push_back(note);

    std::string err;
    saveNotes(err);
    return note;
}

bool NoteManager::updateNote(int id, const std::string& newTitle, const std::string& newContent,
                             const std::string& newCategory, std::string& errorMessage) {
    for (auto& note : notes) {
        if (note.getId() == id) {
            if (!newTitle.empty()) note.setTitle(newTitle);
            if (!newContent.empty()) note.setContent(newContent);
            if (!newCategory.empty()) note.setCategory(newCategory);
            
            return saveNotes(errorMessage);
        }
    }
    errorMessage = "Note with ID " + std::to_string(id) + " not found.";
    return false;
}

bool NoteManager::deleteNote(int id, std::string& errorMessage) {
    auto it = std::find_if(notes.begin(), notes.end(), [id](const Note& n) {
        return n.getId() == id;
    });

    if (it != notes.end()) {
        notes.erase(it);
        return saveNotes(errorMessage);
    }

    errorMessage = "Note with ID " + std::to_string(id) + " not found.";
    return false;
}

const std::vector<Note>& NoteManager::getAllNotes() const {
    return notes;
}

const Note* NoteManager::getNoteById(int id) const {
    for (const auto& note : notes) {
        if (note.getId() == id) {
            return &note;
        }
    }
    return nullptr;
}

bool NoteManager::noteExists(int id) const {
    return getNoteById(id) != nullptr;
}

size_t NoteManager::getNoteCount() const {
    return notes.size();
}

void NoteManager::setNotes(const std::vector<Note>& newNotes) {
    notes = newNotes;
}

bool NoteManager::performBackup(std::string& statusMessage) {
    return backupManager.createBackup(statusMessage);
}

bool NoteManager::performRestore(std::string& statusMessage) {
    if (!backupManager.restoreBackup(statusMessage)) {
        return false;
    }
    std::string loadErr;
    if (!loadNotes(loadErr)) {
        statusMessage += "\nWarning: Reloading notes after restore encountered an issue: " + loadErr;
    }
    return true;
}

const std::string& NoteManager::getDataFilePath() const {
    return dataFilePath;
}
