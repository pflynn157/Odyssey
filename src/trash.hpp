//
// Copyright 2021 Patrick Flynn
// This file is part of uds-explorer.
// uds-explorer is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QString>

class Trash {
public:
    static void initPaths();
    static void trashFile(QString path);
    static void restoreFile(QString filename);
    static void deleteCurrentFile();
    static void emptyTrash();
    static QString folderPath;
private:
    static QString filePath;
    static void genTrashInfo();
};
