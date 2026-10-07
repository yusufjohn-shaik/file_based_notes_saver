#ifndef NOTE_H
#define NOTE_H

#include <string>
#include <iostream>

class Note {
private:
    int id;
    std::string title;
    std::string content;
    std::string category;
    std::string createdDate;

public:
    // Constructors
    Note();
    Note(int id, const std::string& title, const std::string& content,
         const std::string& category, const std::string& createdDate);

    // Getters
    int getId() const;
    const std::string& getTitle() const;
    const std::string& getContent() const;
    const std::string& getCategory() const;
    const std::string& getCreatedDate() const;

    // Setters
    void setId(int newId);
    void setTitle(const std::string& newTitle);
    void setContent(const std::string& newContent);
    void setCategory(const std::string& newCategory);
    void setCreatedDate(const std::string& newDate);

    // Display functions
    void displaySummary() const;
    void displayFull() const;

    // Serialization for File Management
    void serialize(std::ostream& os) const;
    static bool deserialize(std::istream& is, Note& note);
};

#endif // NOTE_H
