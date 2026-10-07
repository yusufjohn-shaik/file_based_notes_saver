#include "SearchEngine.h"
#include "Utils.h"
#include <set>

std::vector<Note> SearchEngine::searchByKeyword(const std::vector<Note>& notes, const std::string& keyword) {
    std::vector<Note> results;
    std::string key = Utils::trim(keyword);
    if (key.empty()) return results;

    for (const auto& note : notes) {
        if (Utils::caseInsensitiveFind(note.getTitle(), key) ||
            Utils::caseInsensitiveFind(note.getContent(), key) ||
            Utils::caseInsensitiveFind(note.getCategory(), key)) {
            results.push_back(note);
        }
    }
    return results;
}

std::vector<Note> SearchEngine::searchByTitle(const std::vector<Note>& notes, const std::string& titleQuery) {
    std::vector<Note> results;
    std::string q = Utils::trim(titleQuery);
    if (q.empty()) return results;

    for (const auto& note : notes) {
        if (Utils::caseInsensitiveFind(note.getTitle(), q)) {
            results.push_back(note);
        }
    }
    return results;
}

std::vector<Note> SearchEngine::searchByContent(const std::vector<Note>& notes, const std::string& contentQuery) {
    std::vector<Note> results;
    std::string q = Utils::trim(contentQuery);
    if (q.empty()) return results;

    for (const auto& note : notes) {
        if (Utils::caseInsensitiveFind(note.getContent(), q)) {
            results.push_back(note);
        }
    }
    return results;
}

std::vector<Note> SearchEngine::searchByCategory(const std::vector<Note>& notes, const std::string& categoryQuery) {
    std::vector<Note> results;
    std::string q = Utils::trim(categoryQuery);
    if (q.empty()) return results;

    for (const auto& note : notes) {
        if (Utils::caseInsensitiveFind(note.getCategory(), q)) {
            results.push_back(note);
        }
    }
    return results;
}

std::vector<std::string> SearchEngine::getAllCategories(const std::vector<Note>& notes) {
    std::set<std::string> uniqueCats;
    // Default recommended categories
    std::vector<std::string> defaultCats = {
        "Programming", "College", "Projects", "Ideas", "Personal", "Research"
    };
    for (const auto& c : defaultCats) {
        uniqueCats.insert(c);
    }

    // Add categories from existing notes
    for (const auto& note : notes) {
        if (!note.getCategory().empty()) {
            uniqueCats.insert(note.getCategory());
        }
    }

    return std::vector<std::string>(uniqueCats.begin(), uniqueCats.end());
}

std::map<std::string, int> SearchEngine::getCategoryCounts(const std::vector<Note>& notes) {
    std::map<std::string, int> counts;
    for (const auto& note : notes) {
        std::string cat = note.getCategory();
        if (cat.empty()) cat = "General";
        counts[cat]++;
    }
    return counts;
}
