#pragma once

#include <QString>

class Actions {
public:
    static void openCurrentFile();
    static void newFolder();
    static void newFile();
    static void rename();
    static void trash();
    static void restore();
    static void deleteFile();
    static void deleteFolder();
    static void paste();
private:
    static QString handleDuplicate(QString newAddr, int index);
    static bool copyDirectory(QString oldPath, QString newPath);
};
