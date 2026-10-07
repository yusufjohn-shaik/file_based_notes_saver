#include "Note.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <sstream>

Note::Note() : id(0), title(""), content(""), category("General"), createdDate("") {}

Note::Note(int id, const std::string& title, const std::string& content,
           const std::string& category, const std::string& createdDate)
    : id(id), title(title), content(content), category(category), createdDate(createdDate) {}

int Note::getId() const { return id; }
const std::string& Note::getTitle() const { return title; }
const std::string& Note::getContent() const { return content; }
const std::string& Note::getCategory() const { return category; }
const std::string& Note::getCreatedDate() const { return createdDate; }

void Note::setId(int newId) { id = newId; }
void Note::setTitle(const std::string& newTitle) { title = newTitle; }
void Note::setContent(const std::string& newContent) { content = newContent; }
void Note::setCategory(const std::string& newCategory) { category = newCategory; }
void Note::setCreatedDate(const std::string& newDate) { createdDate = newDate; }

void Note::displaySummary() const {
    std::cout << Utils::Colors::BOLD << "[" << id << "] " << Utils::Colors::RESET
              << Utils::Colors::CYAN << title << Utils::Colors::RESET
              << " (" << Utils::Colors::YELLOW << category << Utils::Colors::RESET << ")"
              << " - " << Utils::Colors::DIM << createdDate << Utils::Colors::RESET << "\n";
}

void Note::displayFull() const {
    std::cout << "-----------------------------------\n";
    std::cout << Utils::Colors::BOLD << "ID: " << Utils::Colors::RESET << id << "\n";
    std::cout << Utils::Colors::BOLD << "Title: " << Utils::Colors::RESET << title << "\n";
    std::cout << Utils::Colors::BOLD << "Category: " << Utils::Colors::RESET 
              << Utils::Colors::YELLOW << category << Utils::Colors::RESET << "\n";
    std::cout << Utils::Colors::BOLD << "Created: " << Utils::Colors::RESET 
              << Utils::Colors::CYAN << createdDate << Utils::Colors::RESET << "\n\n";
    std::cout << Utils::Colors::BOLD << "Content:" << Utils::Colors::RESET << "\n";
    std::cout << content << "\n";
    std::cout << "-----------------------------------\n";
}

void Note::serialize(std::ostream& os) const {
    os << "[NOTE_START]\n";
    os << "ID: " << id << "\n";
    os << "TITLE: " << title << "\n";
    os << "CATEGORY: " << category << "\n";
    os << "CREATED: " << createdDate << "\n";
    os << "CONTENT_START\n";
    os << content << "\n";
    os << "CONTENT_END\n";
    os << "[NOTE_END]\n";
}

bool Note::deserialize(std::istream& is, Note& note) {
    std::string line;
    bool inNote = false;
    int parsedId = 0;
    std::string parsedTitle;
    std::string parsedCategory;
    std::string parsedCreated;
    std::string parsedContent;

    while (std::getline(is, line)) {
        std::string trimmed = Utils::trim(line);
        if (!inNote) {
            if (trimmed == "[NOTE_START]") {
                inNote = true;
            }
            continue;
        }

        if (trimmed == "[NOTE_END]") {
            note.setId(parsedId);
            note.setTitle(parsedTitle);
            note.setCategory(parsedCategory);
            note.setCreatedDate(parsedCreated);
            note.setContent(parsedContent);
            return true;
        }

        if (trimmed.rfind("ID: ", 0) == 0) {
            try {
                parsedId = std::stoi(Utils::trim(trimmed.substr(4)));
            } catch (...) {
                parsedId = 0;
            }
        } else if (trimmed.rfind("TITLE: ", 0) == 0) {
            parsedTitle = Utils::trim(line.substr(line.find("TITLE: ") + 7));
        } else if (trimmed.rfind("CATEGORY: ", 0) == 0) {
            parsedCategory = Utils::trim(line.substr(line.find("CATEGORY: ") + 10));
        } else if (trimmed.rfind("CREATED: ", 0) == 0) {
            parsedCreated = Utils::trim(line.substr(line.find("CREATED: ") + 9));
        } else if (trimmed == "CONTENT_START") {
            std::string contentLine;
            bool firstLine = true;
            while (std::getline(is, contentLine)) {
                if (Utils::trim(contentLine) == "CONTENT_END") {
                    break;
                }
                if (!firstLine) {
                    parsedContent += "\n";
                }
                parsedContent += contentLine;
                firstLine = false;
            }
        }
    }

    return false;
}
