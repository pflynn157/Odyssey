//
// Copyright 2021 Patrick Flynn
// This file is part of Odyssey file explorer.
// Odyssey is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QMenu>
#include <QAction>

#include <browserwidget.hpp>

class FolderContextMenu : public QMenu {
    Q_OBJECT
public:
    explicit FolderContextMenu(BrowserWidget *b);
    ~FolderContextMenu();
private:
    BrowserWidget *bWidget;
    QAction *openTab, *cut, *copy, *rename, *trash, *restore, *deleteFolder;
private slots:
    void onOpenTabClicked();
    void onCutClicked();
    void onCopyClicked();
    void onRenameClicked();
    void onTrashFolderClicked();
    void onRestoreFolderClicked();
    void onDeleteFolderClicked();
};
