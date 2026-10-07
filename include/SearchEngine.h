#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "Note.h"
#include <vector>
#include <string>
#include <map>

class SearchEngine {
public:
    // Keyword search across title, content, category
    static std::vector<Note> searchByKeyword(const std::vector<Note>& notes, const std::string& keyword);
    
    // Search specific fields
    static std::vector<Note> searchByTitle(const std::vector<Note>& notes, const std::string& titleQuery);
    static std::vector<Note> searchByContent(const std::vector<Note>& notes, const std::string& contentQuery);
    static std::vector<Note> searchByCategory(const std::vector<Note>& notes, const std::string& categoryQuery);

    // Organization / Categories
    static std::vector<std::string> getAllCategories(const std::vector<Note>& notes);
    static std::map<std::string, int> getCategoryCounts(const std::vector<Note>& notes);
};

#endif // SEARCH_ENGINE_H
