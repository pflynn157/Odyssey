//
// Copyright 2021 Patrick Flynn
// This file is part of uds-explorer.
// uds-explorer is licensed under the BSD-3 license. See the COPYING file for more information.
//
#include <QPixmap>

#include <menu/folder_contextmenu.hpp>
#include <tabwidget.hpp>
#include <clipboard.hpp>
#include <actions.hpp>
#include <trash.hpp>

FolderContextMenu::FolderContextMenu(BrowserWidget *b) {
    bWidget = b;

    openTab = new QAction(QPixmap(":/icons/tab-new.svg"), "Open in New Tab", this);
    cut = new QAction(QPixmap(":/icons/edit-cut.svg"), "Cut", this);
    copy = new QAction(QPixmap(":/icons/edit-copy.svg"), "Copy", this);
    rename = new QAction(QPixmap(":/icons/edit-rename.svg"), "Rename", this);
    trash = new QAction(QPixmap(":/icons/user-trash.svg"), "Move to Trash", this);
    restore = new QAction(QPixmap(":/icons/view-refresh.svg"), "Restore", this);
    deleteFolder = new QAction(QPixmap(":/icons/edit-delete.svg"), "Delete", this);

    connect(openTab, &QAction::triggered, this, &FolderContextMenu::onOpenTabClicked);
    connect(cut, &QAction::triggered, this, &FolderContextMenu::onCutClicked);
    connect(copy, &QAction::triggered, this, &FolderContextMenu::onCopyClicked);
    connect(rename, &QAction::triggered, this, &FolderContextMenu::onRenameClicked);
    connect(trash, &QAction::triggered, this, &FolderContextMenu::onTrashFolderClicked);
    connect(restore, &QAction::triggered, this, &FolderContextMenu::onRestoreFolderClicked);
    connect(deleteFolder, &QAction::triggered, this, &FolderContextMenu::onDeleteFolderClicked);

    this->addAction(openTab);
    this->addSeparator();
    this->addAction(cut);
    this->addAction(copy);
    this->addSeparator();
    this->addAction(rename);
    this->addSeparator();
    
    if (TabWidget::currentWidget()->fsCurrentPath()==Trash::folderPath) {
        this->addAction(restore);
    } else {
        this->addAction(trash);
    }
    
    this->addAction(deleteFolder);
}

FolderContextMenu::~FolderContextMenu() {
    delete openTab;
    delete cut;
    delete copy;
    delete rename;
    delete trash;
    delete restore;
    delete deleteFolder;
}

void FolderContextMenu::onOpenTabClicked() {
    QString addr = bWidget->fsCurrentPath();
    if (!addr.endsWith("/")) {
        addr+="/";
    }
    addr+=bWidget->currentItemName();
    TabWidget::addNewTab(addr);
}

void FolderContextMenu::onCutClicked() {
    clipboard.fileName = bWidget->currentItemNames();
    clipboard.oldPath = bWidget->fsCurrentPath();
    clipboard.action = Clipboard_Actions::CUT;
}

void FolderContextMenu::onCopyClicked() {
    clipboard.fileName = bWidget->currentItemNames();
    clipboard.oldPath = bWidget->fsCurrentPath();
    clipboard.action = Clipboard_Actions::COPY;
}

void FolderContextMenu::onRenameClicked() {
    Actions::rename();
}

void FolderContextMenu::onTrashFolderClicked() {
    Actions::trash();
}

void FolderContextMenu::onRestoreFolderClicked() {
    Actions::restore();
}

void FolderContextMenu::onDeleteFolderClicked() {
    if (TabWidget::currentWidget()->fsCurrentPath()==Trash::folderPath) {
        Trash::deleteCurrentFile();
    } else {
        Actions::deleteFolder();
    }
}

