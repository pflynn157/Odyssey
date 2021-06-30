//
// Copyright 2021 Patrick Flynn
// This file is part of Odyssey file explorer.
// Odyssey is licensed under the BSD-3 license. See the COPYING file for more information.
//
#include <QPixmap>

#include <menu/multi_contextmenu.hpp>
#include <clipboard.hpp>
#include <actions.hpp>
#include <trash.hpp>
#include <tabwidget.hpp>

MultiContextMenu::MultiContextMenu(BrowserWidget *b) {
    bWidget = b;

    cut = new QAction(QPixmap(":/icons/edit-cut.svg"), "Cut", this);
    copy = new QAction(QPixmap(":/icons/edit-copy.svg"), "Copy", this);
    trash = new QAction(QPixmap(":/icons/user-trash.svg"), "Move to Trash", this);
    restore = new QAction(QPixmap(":/icons/view-refresh.svg"), "Restore", this);
    deleteAll = new QAction(QPixmap(":/icons/edit-delete.svg"), "Delete", this);

    connect(cut, &QAction::triggered, this, &MultiContextMenu::onCutClicked);
    connect(copy, &QAction::triggered, this, &MultiContextMenu::onCopyClicked);
    connect(trash, &QAction::triggered, this, &MultiContextMenu::onTrashClicked);
    connect(restore, &QAction::triggered, this, &MultiContextMenu::onRestoreClicked);
    connect(deleteAll, &QAction::triggered, this, &MultiContextMenu::onDeleteAllClicked);

    this->addAction(cut);
    this->addAction(copy);
    this->addSeparator();
    
    if (TabWidget::currentWidget()->fsCurrentPath()==Trash::folderPath) {
        this->addAction(restore);
    } else {
        this->addAction(trash);
    }
    
    this->addAction(deleteAll);
}

MultiContextMenu::~MultiContextMenu() {
    delete cut;
    delete copy;
    delete trash;
    delete restore;
    delete deleteAll;
}

void MultiContextMenu::onCutClicked() {
    clipboard.fileName = bWidget->currentItemNames();
    clipboard.oldPath = bWidget->fsCurrentPath();
    clipboard.action = Clipboard_Actions::CUT;
}

void MultiContextMenu::onCopyClicked() {
    clipboard.fileName = bWidget->currentItemNames();
    clipboard.oldPath = bWidget->fsCurrentPath();
    clipboard.action = Clipboard_Actions::COPY;
}

void MultiContextMenu::onTrashClicked() {
    Actions::trash();
}

void MultiContextMenu::onRestoreClicked() {
    Actions::restore();
}

void MultiContextMenu::onDeleteAllClicked() {
    Actions::deleteFile();
}
