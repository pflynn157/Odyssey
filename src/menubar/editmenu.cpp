//
// Copyright 2021 Patrick Flynn
// This file is part of Odyssey file explorer.
// Odyssey is licensed under the BSD-3 license. See the COPYING file for more information.
//
#include <QIcon>
#include <QKeySequence>

#include <menubar/editmenu.hpp>
#include <clipboard.hpp>
#include <tabwidget.hpp>
#include <actions.hpp>

EditMenu::EditMenu() {
    this->setTitle("Edit");

    selectAll = new QAction(QPixmap(":/icons/edit-select-all.svg"), "Select All", this);
    cut = new QAction(QPixmap(":/icons/edit-cut.svg"), "Cut", this);
    copy = new QAction(QPixmap(":/icons/edit-copy.svg"), "Copy", this);
    paste = new QAction(QPixmap(":/icons/edit-paste.svg"), "Paste", this);
    trash = new QAction(QPixmap(":/icons/user-trash.svg"), "Trash", this);
    deleteFile = new QAction(QPixmap(":/icons/edit-delete.svg"), "Delete", this);

    selectAll->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_A));
    cut->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_X));
    copy->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_C));
    paste->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_V));
    trash->setShortcut(QKeySequence(Qt::Key_Delete));
    deleteFile->setShortcut(QKeySequence(Qt::CTRL+Qt::SHIFT+Qt::Key_D));

    connect(selectAll, &QAction::triggered, this, &EditMenu::onSelectAllClicked);
    connect(cut, &QAction::triggered, this, &EditMenu::onCutClicked);
    connect(copy, &QAction::triggered, this, &EditMenu::onCopyClicked);
    connect(paste, &QAction::triggered, this, &EditMenu::onPasteClicked);
    connect(trash, &QAction::triggered, this, &EditMenu::onTrashClicked);
    connect(deleteFile, &QAction::triggered, this, &EditMenu::onDeleteFileClicked);

    this->addAction(selectAll);
    this->addSeparator();
    this->addAction(cut);
    this->addAction(copy);
    this->addAction(paste);
    this->addSeparator();
    this->addAction(trash);
    this->addAction(deleteFile);
}

EditMenu::~EditMenu() {
    delete selectAll;
    delete cut;
    delete copy;
    delete paste;
    delete trash;
    delete deleteFile;
}

void EditMenu::onSelectAllClicked() {
    TabWidget::currentWidget()->selectAll();
}

void EditMenu::onCutClicked() {
    clipboard.fileName = TabWidget::currentWidget()->currentItemNames();
    clipboard.oldPath = TabWidget::currentWidget()->fsCurrentPath();
    clipboard.action = Clipboard_Actions::CUT;
}

void EditMenu::onCopyClicked() {
    clipboard.fileName = TabWidget::currentWidget()->currentItemNames();
    clipboard.oldPath = TabWidget::currentWidget()->fsCurrentPath();
    clipboard.action = Clipboard_Actions::COPY;
}

void EditMenu::onPasteClicked() {
    clipboard.newPath = TabWidget::currentWidget()->fsCurrentPath();
    Actions::paste();
}

void EditMenu::onTrashClicked() {
    Actions::trash();
}

void EditMenu::onDeleteFileClicked() {
    Actions::deleteFile();
}

