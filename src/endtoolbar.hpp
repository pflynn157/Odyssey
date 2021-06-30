//
// Copyright 2021 Patrick Flynn
// This file is part of Odyssey file explorer.
// Odyssey is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QToolBar>
#include <QToolButton>

#include <browserwidget.hpp>

class EndToolbar : public QToolBar {
    Q_OBJECT
public:
    EndToolbar();
    ~EndToolbar();
    void setBrowserWidget(BrowserWidget *b);
private:
    BrowserWidget *bWidget;
    QToolButton *showTxtAddr, *iconView, *listView;
private slots:
    void onShowTxtAddr();
    void onIconViewClicked();
    void onListViewClicked();
};
