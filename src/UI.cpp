#include "UI.h"
#include "InputValidator.h"
#include "SearchEngine.h"
#include "NoteSorter.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>

UI::UI(NoteManager& noteManager) : manager(noteManager) {}

void UI::displayHeader(const std::string& title) const {
    std::cout << "\n" << Utils::Colors::CYAN << "=================================\n"
              << "       " << title << "\n"
              << "=================================" << Utils::Colors::RESET << "\n\n";
}

void UI::pause() const {
    if (std::cin.eof()) {
        std::exit(0);
    }
    std::cout << "\n" << Utils::Colors::DIM << "Press Enter to continue..." 
              << Utils::Colors::RESET;
    std::string dummy;
    if (!std::getline(std::cin, dummy)) {
        if (std::cin.eof()) {
            std::cout << "\nExiting application.\n";
            std::exit(0);
        }
    }
}

void UI::displayMainMenu() const {
    std::cout << "\n" << Utils::Colors::CYAN
              << "=================================\n"
              << "       FILE-BASED NOTES SAVER    \n"
              << "=================================" << Utils::Colors::RESET << "\n\n"
              << "1. Create Note\n"
              << "2. View All Notes\n"
              << "3. View Note\n"
              << "4. Edit Note\n"
              << "5. Delete Note\n"
              << "6. Search Notes\n"
              << "7. Categories\n"
              << "8. Sort Notes\n"
              << "9. Backup Notes\n"
              << "10. Restore Notes\n"
              << "11. Exit\n\n";
}

void UI::handleCreateNote() {
    displayHeader("CREATE NOTE");

    std::string title = InputValidator::getString("Enter Note Title: ");
    
    std::cout << "\nEnter Note Content:\n";
    std::string content = InputValidator::getMultilineContent("");

    // Show available categories as a quick suggestion
    auto allNotes = manager.getAllNotes();
    auto categories = SearchEngine::getAllCategories(allNotes);
    std::cout << "\nSuggested Categories: ";
    for (size_t i = 0; i < categories.size(); ++i) {
        std::cout << categories[i] << (i + 1 < categories.size() ? ", " : "");
    }
    std::cout << "\n";

    std::string category = InputValidator::getString("Enter Category: ");
    if (category.empty()) {
        category = "General";
    }

    Note note = manager.createNote(title, content, category);
    std::cout << "\n" << Utils::Colors::BOLD << Utils::Colors::GREEN 
              << "Note created successfully!" << Utils::Colors::RESET << "\n";
    std::cout << Utils::Colors::BOLD << "Note ID: " << Utils::Colors::RESET 
              << note.getId() << "\n";

    pause();
}

void UI::handleViewAllNotes() {
    displayHeader("VIEW ALL NOTES");

    const auto& notes = manager.getAllNotes();
    if (notes.empty()) {
        InputValidator::printInfo("No notes found. Create your first note!");
        pause();
        return;
    }

    std::cout << Utils::Colors::BOLD << "Total Notes: " << notes.size() 
              << Utils::Colors::RESET << "\n\n";

    for (const auto& note : notes) {
        note.displaySummary();
    }

    std::cout << "\n";
    int choice = InputValidator::getInt("Enter Note ID to view full content (or 0 to return): ", 0, 2000000000);
    if (choice > 0) {
        const Note* n = manager.getNoteById(choice);
        if (n) {
            std::cout << "\n";
            n->displayFull();
        } else {
            InputValidator::printError("Note ID " + std::to_string(choice) + " not found.");
        }
    }
    pause();
}

void UI::handleViewNote() {
    displayHeader("VIEW NOTE");

    if (manager.getNoteCount() == 0) {
        InputValidator::printInfo("No notes available in the database.");
        pause();
        return;
    }

    int id = InputValidator::getId("Enter Note ID: ");
    const Note* note = manager.getNoteById(id);

    if (note) {
        std::cout << "\n";
        note->displayFull();
    } else {
        InputValidator::printError("Note with ID " + std::to_string(id) + " does not exist.");
    }
    pause();
}

void UI::handleEditNote() {
    displayHeader("EDIT NOTE");

    if (manager.getNoteCount() == 0) {
        InputValidator::printInfo("No notes available to edit.");
        pause();
        return;
    }

    int id = InputValidator::getId("Enter Note ID: ");
    const Note* note = manager.getNoteById(id);

    if (!note) {
        InputValidator::printError("Note with ID " + std::to_string(id) + " does not exist.");
        pause();
        return;
    }

    std::cout << "\n" << Utils::Colors::BOLD << "Current Note Information:" 
              << Utils::Colors::RESET << "\n";
    note->displayFull();

    std::cout << "\n1. Edit Title\n"
              << "2. Edit Content\n"
              << "3. Edit Category\n"
              << "4. Edit All\n"
              << "5. Cancel\n\n";

    int choice = InputValidator::getInt("Choose: ", 1, 5);

    std::string newTitle = note->getTitle();
    std::string newContent = note->getContent();
    std::string newCategory = note->getCategory();

    if (choice == 1) {
        newTitle = InputValidator::getString("Enter New Title: ");
    } else if (choice == 2) {
        std::cout << "Enter New Content:\n";
        newContent = InputValidator::getMultilineContent("");
    } else if (choice == 3) {
        newCategory = InputValidator::getString("Enter New Category: ");
    } else if (choice == 4) {
        newTitle = InputValidator::getString("Enter New Title: ");
        std::cout << "Enter New Content:\n";
        newContent = InputValidator::getMultilineContent("");
        newCategory = InputValidator::getString("Enter New Category: ");
    } else if (choice == 5) {
        InputValidator::printInfo("Edit operation cancelled.");
        pause();
        return;
    }

    std::string err;
    if (manager.updateNote(id, newTitle, newContent, newCategory, err)) {
        InputValidator::printSuccess("Note updated successfully!");
    } else {
        InputValidator::printError("Failed to update note: " + err);
    }
    pause();
}

void UI::handleDeleteNote() {
    displayHeader("DELETE NOTE");

    if (manager.getNoteCount() == 0) {
        InputValidator::printInfo("No notes available to delete.");
        pause();
        return;
    }

    int id = InputValidator::getId("Enter Note ID: ");
    const Note* note = manager.getNoteById(id);

    if (!note) {
        InputValidator::printError("Note with ID " + std::to_string(id) + " does not exist.");
        pause();
        return;
    }

    std::cout << "\nNote to delete:\n";
    note->displaySummary();

    bool confirmed = InputValidator::getConfirmation("\nAre you sure you want to delete this note? [Y/N]: ");
    if (confirmed) {
        std::string err;
        if (manager.deleteNote(id, err)) {
            InputValidator::printSuccess("Note deleted successfully.");
        } else {
            InputValidator::printError("Deletion failed: " + err);
        }
    } else {
        InputValidator::printInfo("Deletion cancelled.");
    }
    pause();
}

void UI::handleSearchNotes() {
    displayHeader("SEARCH NOTES");

    if (manager.getNoteCount() == 0) {
        InputValidator::printInfo("No notes available to search.");
        pause();
        return;
    }

    std::string keyword = InputValidator::getString("Enter search keyword: ");
    auto results = SearchEngine::searchByKeyword(manager.getAllNotes(), keyword);

    std::cout << "\n" << Utils::Colors::BOLD << "Search Results:" << Utils::Colors::RESET << "\n\n";

    if (results.empty()) {
        InputValidator::printInfo("No matching notes found for '" + keyword + "'.");
    } else {
        for (const auto& note : results) {
            std::cout << Utils::Colors::BOLD << "[" << note.getId() << "] " 
                      << Utils::Colors::RESET << note.getTitle() << "\n";
        }

        std::cout << "\n";
        int choice = InputValidator::getInt("Enter Note ID to view full details (or 0 to return): ", 0, 2000000000);
        if (choice > 0) {
            const Note* n = manager.getNoteById(choice);
            if (n) {
                std::cout << "\n";
                n->displayFull();
            } else {
                InputValidator::printError("Note ID " + std::to_string(choice) + " not found.");
            }
        }
    }
    pause();
}

void UI::handleCategories() {
    displayHeader("NOTE CATEGORIES");

    const auto& notes = manager.getAllNotes();
    auto counts = SearchEngine::getCategoryCounts(notes);

    if (counts.empty()) {
        InputValidator::printInfo("No categories found. Notes created will appear here.");
        pause();
        return;
    }

    std::cout << Utils::Colors::BOLD << "Categories:" << Utils::Colors::RESET << "\n\n";
    std::vector<std::string> catList;
    int index = 1;
    for (const auto& pair : counts) {
        std::cout << "  " << index++ << ". " << pair.first << " (" << pair.second 
                  << (pair.second == 1 ? " note" : " notes") << ")\n";
        catList.push_back(pair.first);
    }

    std::cout << "\n";
    int choice = InputValidator::getInt("Select a category number to view its notes (or 0 to return): ", 0, (int)catList.size());
    if (choice > 0 && choice <= (int)catList.size()) {
        std::string selectedCategory = catList[choice - 1];
        auto filtered = SearchEngine::searchByCategory(notes, selectedCategory);

        std::cout << "\n" << Utils::Colors::BOLD << "Notes in Category '" 
                  << selectedCategory << "':" << Utils::Colors::RESET << "\n\n";

        for (const auto& note : filtered) {
            note.displaySummary();
        }

        std::cout << "\n";
        int noteChoice = InputValidator::getInt("Enter Note ID to view full details (or 0 to return): ", 0, 2000000000);
        if (noteChoice > 0) {
            const Note* n = manager.getNoteById(noteChoice);
            if (n) {
                std::cout << "\n";
                n->displayFull();
            } else {
                InputValidator::printError("Note ID " + std::to_string(noteChoice) + " not found.");
            }
        }
    }
    pause();
}

void UI::handleSortNotes() {
    displayHeader("SORT NOTES");

    if (manager.getNoteCount() == 0) {
        InputValidator::printInfo("No notes available to sort.");
        pause();
        return;
    }

    std::cout << "Sort Notes By:\n\n"
              << "1. Title\n"
              << "2. Date\n"
              << "3. Category\n"
              << "4. Note ID\n"
              << "5. Cancel\n\n";

    int choice = InputValidator::getInt("Choose: ", 1, 5);
    if (choice == 5) {
        return;
    }

    std::cout << "\nSort Order:\n"
              << "1. Ascending (A-Z / Oldest First / Smallest ID)\n"
              << "2. Descending (Z-A / Newest First / Largest ID)\n\n";

    int orderChoice = InputValidator::getInt("Choose: ", 1, 2);
    bool ascending = (orderChoice == 1);

    std::vector<Note> sortedNotes = manager.getAllNotes();

    switch (choice) {
        case 1:
            NoteSorter::sortNotes(sortedNotes, NoteSorter::SortField::Title, ascending);
            break;
        case 2:
            NoteSorter::sortNotes(sortedNotes, NoteSorter::SortField::Date, ascending);
            break;
        case 3:
            NoteSorter::sortNotes(sortedNotes, NoteSorter::SortField::Category, ascending);
            break;
        case 4:
            NoteSorter::sortNotes(sortedNotes, NoteSorter::SortField::Id, ascending);
            break;
    }

    std::cout << "\n" << Utils::Colors::BOLD << "Sorted Notes:" << Utils::Colors::RESET << "\n\n";
    for (const auto& note : sortedNotes) {
        note.displaySummary();
    }

    std::cout << "\n";
    bool savePermanently = InputValidator::getConfirmation("Would you like to save this sorted order permanently? [Y/N]: ");
    if (savePermanently) {
        manager.setNotes(sortedNotes);
        std::string err;
        if (manager.saveNotes(err)) {
            InputValidator::printSuccess("Sorted order saved permanently to file.");
        } else {
            InputValidator::printError("Failed to save sorted order: " + err);
        }
    } else {
        InputValidator::printInfo("Sorted view displayed. Original file order preserved.");
    }

    pause();
}

void UI::handleBackupNotes() {
    displayHeader("BACKUP NOTES");

    if (manager.getNoteCount() == 0) {
        InputValidator::printWarning("No notes currently exist to backup.");
    }

    bool confirm = InputValidator::getConfirmation("Are you sure you want to create a backup of your notes? [Y/N]: ");
    if (!confirm) {
        InputValidator::printInfo("Backup cancelled.");
        pause();
        return;
    }

    std::string status;
    if (manager.performBackup(status)) {
        InputValidator::printSuccess(status);
    } else {
        InputValidator::printError(status);
    }
    pause();
}

void UI::handleRestoreNotes() {
    displayHeader("RESTORE NOTES");

    InputValidator::printWarning("Restoring will overwrite current notes with the backup file!");
    bool confirm = InputValidator::getConfirmation("Are you sure you want to restore from backup? [Y/N]: ");
    if (!confirm) {
        InputValidator::printInfo("Restore cancelled.");
        pause();
        return;
    }

    std::string status;
    if (manager.performRestore(status)) {
        InputValidator::printSuccess(status);
        std::cout << "Loaded " << manager.getNoteCount() << " notes from backup.\n";
    } else {
        InputValidator::printError(status);
    }
    pause();
}

void UI::run() {
    while (true) {
        displayMainMenu();
        int choice = InputValidator::getInt("Enter your choice: ", 1, 11);

        switch (choice) {
            case 1:
                handleCreateNote();
                break;
            case 2:
                handleViewAllNotes();
                break;
            case 3:
                handleViewNote();
                break;
            case 4:
                handleEditNote();
                break;
            case 5:
                handleDeleteNote();
                break;
            case 6:
                handleSearchNotes();
                break;
            case 7:
                handleCategories();
                break;
            case 8:
                handleSortNotes();
                break;
            case 9:
                handleBackupNotes();
                break;
            case 10:
                handleRestoreNotes();
                break;
            case 11:
                std::cout << "\n" << Utils::Colors::BOLD << Utils::Colors::GREEN
                          << "Thank you for using File-Based Notes Saver! Goodbye." 
                          << Utils::Colors::RESET << "\n\n";
                return;
        }
    }
}
