//
// Copyright 2021 Patrick Flynn
// This file is part of Odyssey file explorer.
// Odyssey is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QMenu>
#include <QAction>

#include <browserwidget.hpp>

class MultiContextMenu: public QMenu {
    Q_OBJECT
public:
    explicit MultiContextMenu(BrowserWidget *b);
    ~MultiContextMenu();
private:
    BrowserWidget *bWidget;
    QAction *cut, *copy, *trash, *restore, *deleteAll;
private slots:
    void onCutClicked();
    void onCopyClicked();
    void onTrashClicked();
    void onRestoreClicked();
    void onDeleteAllClicked();
};

