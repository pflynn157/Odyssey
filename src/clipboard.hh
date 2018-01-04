#pragma once

#include <QString>

enum Clipboard_Actions {
    CUT,
    COPY,
    NONE
};

enum Clipboard_FileType {
    TYPE_FILE,
    TYPE_FOLDER
};

struct Clipboard {
    QString fileName;
    QString oldPath;
    QString newPath;
    Clipboard_Actions action;
    Clipboard_FileType filetype;
};

extern Clipboard clipboard;
