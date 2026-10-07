#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "Note.h"
#include <vector>
#include <string>

class FileManager {
public:
    static bool fileExists(const std::string& filepath);
    static bool createEmptyFileIfNotExists(const std::string& filepath, std::string& errorMessage);
    
    // Core file I/O operations
    static bool loadNotes(const std::string& filepath, std::vector<Note>& notes, std::string& errorMessage);
    static bool saveNotes(const std::string& filepath, const std::vector<Note>& notes, std::string& errorMessage);
    
    // File utility operations
    static bool copyFile(const std::string& src, const std::string& dest, std::string& errorMessage);
    static size_t getFileSize(const std::string& filepath);
};

#endif // FILE_MANAGER_H
