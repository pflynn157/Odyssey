//
// Copyright 2021 Patrick Flynn
// This file is part of uds-explorer.
// uds-explorer is licensed under the BSD-3 license. See the COPYING file for more information.
//
#include <dialogs/keyboardshortcutsdialog.hpp>

#include "ui_keyboardshortcutsdialog.h"

KeyboardShortcutsDialog::KeyboardShortcutsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyboardShortcutsDialog)
{
    ui->setupUi(this);
}

KeyboardShortcutsDialog::~KeyboardShortcutsDialog() {
    delete ui;
}

void KeyboardShortcutsDialog::on_closeButton_clicked() {
    this->close();
}
