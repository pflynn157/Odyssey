//
// Copyright 2021 Patrick Flynn
// This file is part of uds-explorer.
// uds-explorer is licensed under the BSD-3 license. See the COPYING file for more information.
//
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
