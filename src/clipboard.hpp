//
// Copyright 2021 Patrick Flynn
// This file is part of Odyssey file explorer.
// Odyssey is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QString>
#include <QStringList>

enum Clipboard_Actions {
    CUT,
    COPY,
    NONE
};

struct Clipboard {
    QStringList fileName;
    QString oldPath;
    QString newPath;
    Clipboard_Actions action;
};

extern Clipboard clipboard;
