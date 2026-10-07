#include "BackupManager.h"
#include "FileManager.h"
#include "Utils.h"

BackupManager::BackupManager(const std::string& sourceFile, const std::string& backupFile)
    : defaultSourceFile(sourceFile), defaultBackupFile(backupFile) {}

bool BackupManager::createBackup(std::string& statusMessage) {
    if (!FileManager::fileExists(defaultSourceFile)) {
        statusMessage = "Source file '" + defaultSourceFile + "' does not exist. Nothing to backup.";
        return false;
    }

    std::string err;
    if (!FileManager::copyFile(defaultSourceFile, defaultBackupFile, err)) {
        statusMessage = "Backup creation failed: " + err;
        return false;
    }

    statusMessage = "Backup created successfully!\nBackup Location: " + defaultBackupFile +
                    "\nTimestamp: " + Utils::getCurrentDateTime();
    return true;
}

bool BackupManager::restoreBackup(std::string& statusMessage) {
    if (!backupExists()) {
        statusMessage = "Backup file '" + defaultBackupFile + "' not found. Cannot restore.";
        return false;
    }

    std::string err;
    if (!FileManager::copyFile(defaultBackupFile, defaultSourceFile, err)) {
        statusMessage = "Restore failed: " + err;
        return false;
    }

    statusMessage = "Notes restored successfully from backup '" + defaultBackupFile + "'!";
    return true;
}

bool BackupManager::backupExists() const {
    return FileManager::fileExists(defaultBackupFile);
}

std::string BackupManager::getBackupFilePath() const {
    return defaultBackupFile;
}

std::string BackupManager::getSourceFilePath() const {
    return defaultSourceFile;
}
