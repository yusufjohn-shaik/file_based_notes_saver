#ifndef UI_H
#define UI_H

#include "NoteManager.h"

class UI {
private:
    NoteManager& manager;

    void displayHeader(const std::string& title) const;
    void pause() const;

    // Sub-operation handlers
    void handleCreateNote();
    void handleViewAllNotes();
    void handleViewNote();
    void handleEditNote();
    void handleDeleteNote();
    void handleSearchNotes();
    void handleCategories();
    void handleSortNotes();
    void handleBackupNotes();
    void handleRestoreNotes();

public:
    explicit UI(NoteManager& noteManager);

    void displayMainMenu() const;
    void run();
};

#endif // UI_H
