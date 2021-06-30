//
// Copyright 2021 Patrick Flynn
// This file is part of Odyssey file explorer.
// Odyssey is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QMenu>
#include <QAction>

#include <window.hpp>

class Window;

class FileMenu : public QMenu {
    Q_OBJECT
public:
    FileMenu(Window *p);
    ~FileMenu();
private:
    Window *parent;
    QAction *newTab, *closeTab, *newFile, *newFolder, *quit;
private slots:
    void onNewTabClicked();
    void onCloseTabClicked();
    void onNewFileClicked();
    void onNewFolderClicked();
    void onQuitClicked();
};
