#include "NoteManager.h"
#include "UI.h"
#include "Utils.h"
#include "InputValidator.h"
#include <iostream>
#include <exception>

int main() {
    try {
        const std::string notesFile = "notes.txt";
        const std::string backupFile = "notes_backup.txt";

        NoteManager manager(notesFile, backupFile);

        // Load existing notes from file upon startup
        std::string loadError;
        if (!manager.loadNotes(loadError)) {
            InputValidator::printWarning("Could not load notes: " + loadError);
        } else {
            if (manager.getNoteCount() > 0) {
                std::cout << Utils::Colors::CYAN << "[System] Loaded " 
                          << manager.getNoteCount() << " note(s) from " 
                          << notesFile << Utils::Colors::RESET << "\n";
            }
        }
        
        UI ui(manager);
        ui.run();

    } catch (const std::exception& ex) {
        InputValidator::printError(std::string("Fatal runtime exception encountered: ") + ex.what());
        return 1;
    } catch (...) {
        InputValidator::printError("Unknown fatal error occurred. Application terminated safely.");
        return 1;
    }

    return 0;
}
