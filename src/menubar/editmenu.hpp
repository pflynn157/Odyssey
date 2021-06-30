//
// Copyright 2021 Patrick Flynn
// This file is part of uds-explorer.
// uds-explorer is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QMenu>
#include <QAction>

class EditMenu : public QMenu{
public:
    EditMenu();
    ~EditMenu();
private:
    QAction *selectAll;
    QAction *cut, *copy, *paste;
    QAction *trash, *deleteFile;
private slots:
    void onSelectAllClicked();
    void onCutClicked();
    void onCopyClicked();
    void onPasteClicked();
    void onTrashClicked();
    void onDeleteFileClicked();
};
