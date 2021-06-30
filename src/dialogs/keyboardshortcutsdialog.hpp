//
// Copyright 2021 Patrick Flynn
// This file is part of Odyssey file explorer.
// Odyssey is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QDialog>

namespace Ui {
class KeyboardShortcutsDialog;
}

class KeyboardShortcutsDialog : public QDialog {
    Q_OBJECT
public:
    explicit KeyboardShortcutsDialog(QWidget *parent = 0);
    ~KeyboardShortcutsDialog();
private slots:
    void on_closeButton_clicked();
private:
    Ui::KeyboardShortcutsDialog *ui;
};
