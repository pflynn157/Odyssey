//
// Copyright 2021 Patrick Flynn
// This file is part of Odyssey file explorer.
// Odyssey is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QMenu>
#include <QAction>

#include <browserwidget.hpp>

class BackgroundContextMenu : public QMenu {
    Q_OBJECT
public:
    explicit BackgroundContextMenu(BrowserWidget *b);
    ~BackgroundContextMenu();
private:
    BrowserWidget *bWidget;
    QAction *newFolder, *newFile, *paste, *terminal;
private slots:
    void onNewFolderClicked();
    void onNewFileClicked();
    void onPasteClicked();
    void onTerminalClicked();
};
