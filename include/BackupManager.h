#ifndef BACKUP_MANAGER_H
#define BACKUP_MANAGER_H

#include <string>

class BackupManager {
private:
    std::string defaultSourceFile;
    std::string defaultBackupFile;

public:
    BackupManager(const std::string& sourceFile = "notes.txt",
                  const std::string& backupFile = "notes_backup.txt");

    bool createBackup(std::string& statusMessage);
    bool restoreBackup(std::string& statusMessage);
    bool backupExists() const;
    std::string getBackupFilePath() const;
    std::string getSourceFilePath() const;
};

#endif // BACKUP_MANAGER_H
