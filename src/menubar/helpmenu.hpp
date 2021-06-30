//
// Copyright 2021 Patrick Flynn
// This file is part of Odyssey file explorer.
// Odyssey is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QMenu>
#include <QAction>

class HelpMenu : public QMenu {
    Q_OBJECT
public:
    HelpMenu();
    ~HelpMenu();
private:
    QAction *keyboardShortcuts, *aboutQt, *about;
private slots:
    void onKeyboardShortcutsClicked();
    void onAboutClicked();
};
