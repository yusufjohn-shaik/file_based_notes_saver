#include "NoteSorter.h"
#include "Utils.h"
#include <algorithm>

void NoteSorter::sortByTitle(std::vector<Note>& notes, bool ascending) {
    std::sort(notes.begin(), notes.end(), [ascending](const Note& a, const Note& b) {
        std::string ta = Utils::toLower(a.getTitle());
        std::string tb = Utils::toLower(b.getTitle());
        if (ta != tb) {
            return ascending ? (ta < tb) : (ta > tb);
        }
        return ascending ? (a.getId() < b.getId()) : (a.getId() > b.getId());
    });
}

void NoteSorter::sortByDate(std::vector<Note>& notes, bool ascending) {
    std::sort(notes.begin(), notes.end(), [ascending](const Note& a, const Note& b) {
        std::time_t da = Utils::parseDate(a.getCreatedDate());
        std::time_t db = Utils::parseDate(b.getCreatedDate());
        if (da != db) {
            return ascending ? (da < db) : (da > db);
        }
        return ascending ? (a.getId() < b.getId()) : (a.getId() > b.getId());
    });
}

void NoteSorter::sortByCategory(std::vector<Note>& notes, bool ascending) {
    std::sort(notes.begin(), notes.end(), [ascending](const Note& a, const Note& b) {
        std::string ca = Utils::toLower(a.getCategory());
        std::string cb = Utils::toLower(b.getCategory());
        if (ca != cb) {
            return ascending ? (ca < cb) : (ca > cb);
        }
        return ascending ? (a.getId() < b.getId()) : (a.getId() > b.getId());
    });
}

void NoteSorter::sortById(std::vector<Note>& notes, bool ascending) {
    std::sort(notes.begin(), notes.end(), [ascending](const Note& a, const Note& b) {
        return ascending ? (a.getId() < b.getId()) : (a.getId() > b.getId());
    });
}

void NoteSorter::sortNotes(std::vector<Note>& notes, SortField field, bool ascending) {
    switch (field) {
        case SortField::Title:
            sortByTitle(notes, ascending);
            break;
        case SortField::Date:
            sortByDate(notes, ascending);
            break;
        case SortField::Category:
            sortByCategory(notes, ascending);
            break;
        case SortField::Id:
            sortById(notes, ascending);
            break;
    }
}
