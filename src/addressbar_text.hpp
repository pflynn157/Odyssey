//
// Copyright 2021 Patrick Flynn
// This file is part of uds-explorer.
// uds-explorer is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QToolBar>
#include <QLineEdit>

#include <browserwidget.hpp>
#include <endtoolbar.hpp>

class AddressBarText : public QToolBar {
    Q_OBJECT
public:
    AddressBarText();
    ~AddressBarText();
    void setBrowserWidget(BrowserWidget *b);
private:
    BrowserWidget *bWidget;
    QLineEdit *addressEntry;
    EndToolbar *endtoolbar;
private slots:
    void onAddrEntryReturnPressed();
    void onDirChanged(QString path);
};
