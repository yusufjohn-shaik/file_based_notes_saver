#include "FileManager.h"
#include <fstream>
#include <sys/stat.h>

bool FileManager::fileExists(const std::string& filepath) {
    std::ifstream f(filepath.c_str());
    return f.good();
}

size_t FileManager::getFileSize(const std::string& filepath) {
    struct stat stat_buf;
    int rc = stat(filepath.c_str(), &stat_buf);
    return (rc == 0) ? stat_buf.st_size : 0;
}

bool FileManager::createEmptyFileIfNotExists(const std::string& filepath, std::string& errorMessage) {
    if (fileExists(filepath)) {
        return true;
    }
    std::ofstream out(filepath.c_str());
    if (!out.is_open()) {
        errorMessage = "Unable to create file: " + filepath;
        return false;
    }
    out << "# File-Based Notes Saver Storage File\n";
    out.close();
    return true;
}

bool FileManager::loadNotes(const std::string& filepath, std::vector<Note>& notes, std::string& errorMessage) {
    notes.clear();
    if (!fileExists(filepath)) {
        // If file does not exist yet, treat it as empty notes collection
        return true;
    }

    std::ifstream inFile(filepath.c_str());
    if (!inFile.is_open()) {
        errorMessage = "Error: Unable to open notes file '" + filepath + "' for reading.";
        return false;
    }

    Note note;
    while (Note::deserialize(inFile, note)) {
        notes.push_back(note);
    }

    if (inFile.bad()) {
        errorMessage = "Error: Critical I/O failure while reading file '" + filepath + "'.";
        inFile.close();
        return false;
    }

    inFile.close();
    return true;
}

bool FileManager::saveNotes(const std::string& filepath, const std::vector<Note>& notes, std::string& errorMessage) {
    std::ofstream outFile(filepath.c_str(), std::ios::trunc);
    if (!outFile.is_open()) {
        errorMessage = "Error: Unable to open notes file '" + filepath + "' for writing. Check permissions.";
        return false;
    }

    outFile << "# File-Based Notes Saver Storage File\n";
    for (const auto& note : notes) {
        note.serialize(outFile);
    }

    if (!outFile) {
        errorMessage = "Error: Failed writing data to notes file '" + filepath + "'.";
        outFile.close();
        return false;
    }

    outFile.close();
    return true;
}

bool FileManager::copyFile(const std::string& src, const std::string& dest, std::string& errorMessage) {
    if (!fileExists(src)) {
        errorMessage = "Source file does not exist: " + src;
        return false;
    }

    std::ifstream in(src.c_str(), std::ios::binary);
    if (!in.is_open()) {
        errorMessage = "Unable to open source file: " + src;
        return false;
    }

    std::ofstream out(dest.c_str(), std::ios::binary | std::ios::trunc);
    if (!out.is_open()) {
        errorMessage = "Unable to open destination file for writing: " + dest;
        in.close();
        return false;
    }

    out << in.rdbuf();

    if (!out) {
        errorMessage = "Failed writing backup to: " + dest;
        in.close();
        out.close();
        return false;
    }

    in.close();
    out.close();
    return true;
}
