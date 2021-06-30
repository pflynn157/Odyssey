//
// Copyright 2021 Patrick Flynn
// This file is part of uds-explorer.
// uds-explorer is licensed under the BSD-3 license. See the COPYING file for more information.
//
#include <QPixmap>

#include <menu/file_contextmenu.hpp>
#include <dialogs/appchooserdialog.hpp>
#include <clipboard.hpp>
#include <actions.hpp>
#include <tabwidget.hpp>
#include <trash.hpp>

FileContextMenu::FileContextMenu(BrowserWidget *b) {
    bWidget = b;

    open = new QAction(QPixmap(":/icons/document-open.svg"), "Open", this);
    openWith = new QAction("Open With", this);
    cut = new QAction(QPixmap(":/icons/edit-cut.svg"), "Cut", this);
    copy = new QAction(QPixmap(":/icons/edit-copy.svg"), "Copy", this);
    rename = new QAction(QPixmap(":/icons/edit-rename.svg"), "Rename", this);
    trash = new QAction(QPixmap(":/icons/user-trash.svg"), "Move to Trash", this);
    restore = new QAction(QPixmap(":/icons/view-refresh.svg"), "Restore", this);
    deleteFile = new QAction(QPixmap(":/icons/edit-delete.svg"), "Delete", this);

    connect(open, &QAction::triggered, this, &FileContextMenu::onOpenClicked);
    connect(openWith, &QAction::triggered, this, &FileContextMenu::onOpenWithClicked);
    connect(cut, &QAction::triggered, this, &FileContextMenu::onCutClicked);
    connect(copy, &QAction::triggered, this, &FileContextMenu::onCopyClicked);
    connect(rename, &QAction::triggered, this, &FileContextMenu::onRenameClicked);
    connect(trash, &QAction::triggered, this, &FileContextMenu::onTrashClicked);
    connect(restore, &QAction::triggered, this, &FileContextMenu::onRestoreClicked);
    connect(deleteFile, &QAction::triggered, this, &FileContextMenu::onDeleteClicked);

    this->addAction(open);
    this->addAction(openWith);
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
    
    this->addAction(deleteFile);
}

FileContextMenu::~FileContextMenu() {
    delete open;
    delete openWith;
    delete cut;
    delete copy;
    delete rename;
    delete trash;
    delete restore;
    delete deleteFile;
}

void FileContextMenu::onOpenClicked() {
    Actions::openCurrentFile();
}

void FileContextMenu::onOpenWithClicked() {
    AppChooserDialog dialog(bWidget->currentItemName());
    dialog.exec();
}

void FileContextMenu::onCutClicked() {
    clipboard.fileName = bWidget->currentItemNames();
    clipboard.oldPath = bWidget->fsCurrentPath();
    clipboard.action = Clipboard_Actions::CUT;
}

void FileContextMenu::onCopyClicked() {
    clipboard.fileName = bWidget->currentItemNames();
    clipboard.oldPath = bWidget->fsCurrentPath();
    clipboard.action = Clipboard_Actions::COPY;
}

void FileContextMenu::onRenameClicked() {
    Actions::rename();
}

void FileContextMenu::onTrashClicked() {
    Actions::trash();
}

void FileContextMenu::onRestoreClicked() {
    Actions::restore();
}

void FileContextMenu::onDeleteClicked() {
    if (TabWidget::currentWidget()->fsCurrentPath()==Trash::folderPath) {
        Trash::deleteCurrentFile();
    } else {
        Actions::deleteFolder();
    }
}
