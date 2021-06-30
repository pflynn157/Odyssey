//
// Copyright 2021 Patrick Flynn
// This file is part of uds-explorer.
// uds-explorer is licensed under the BSD-3 license. See the COPYING file for more information.
//
#include <QIcon>
#include <QApplication>

#include <menubar/helpmenu.hpp>
#include <dialogs/helpdialog.hpp>
#include <dialogs/keyboardshortcutsdialog.hpp>

HelpMenu::HelpMenu() {
    this->setTitle("Help");

    keyboardShortcuts = new QAction("Keyboard Shortcuts", this);
    aboutQt = new QAction("About Qt", this);
    about = new QAction(QPixmap(":/icons/help-about.svg"), "About", this);

    connect(keyboardShortcuts, &QAction::triggered, this, &HelpMenu::onKeyboardShortcutsClicked);
    connect(aboutQt, &QAction::triggered, qApp, &QApplication::aboutQt);
    connect(about, &QAction::triggered, this, &HelpMenu::onAboutClicked);

    this->addAction(keyboardShortcuts);
    this->addSeparator();
    this->addAction(aboutQt);
    this->addAction(about);
}

HelpMenu::~HelpMenu() {
    delete keyboardShortcuts;
    delete aboutQt;
    delete about;
}

void HelpMenu::onKeyboardShortcutsClicked() {
    KeyboardShortcutsDialog().exec();
}

void HelpMenu::onAboutClicked() {
    HelpDialog().exec();
}

