//
// Copyright 2021 Patrick Flynn
// This file is part of uds-explorer.
// uds-explorer is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QMenu>
#include <QAction>

#include <browserwidget.hpp>

class FileContextMenu : public QMenu {
    Q_OBJECT
public:
    explicit FileContextMenu(BrowserWidget *b);
    ~FileContextMenu();
private:
    BrowserWidget *bWidget;
    QAction *open, *openWith, *cut, *copy, *rename, *trash, *restore, *deleteFile;
private slots:
    void onOpenClicked();
    void onOpenWithClicked();
    void onCutClicked();
    void onCopyClicked();
    void onRenameClicked();
    void onTrashClicked();
    void onRestoreClicked();
    void onDeleteClicked();
};
