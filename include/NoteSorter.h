#ifndef NOTE_SORTER_H
#define NOTE_SORTER_H

#include "Note.h"
#include <vector>

class NoteSorter {
public:
    enum class SortField {
        Title,
        Date,
        Category,
        Id
    };

    static void sortNotes(std::vector<Note>& notes, SortField field, bool ascending = true);

    static void sortByTitle(std::vector<Note>& notes, bool ascending = true);
    static void sortByDate(std::vector<Note>& notes, bool ascending = true);
    static void sortByCategory(std::vector<Note>& notes, bool ascending = true);
    static void sortById(std::vector<Note>& notes, bool ascending = true);
};

#endif // NOTE_SORTER_H
