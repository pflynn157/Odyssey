//
// Copyright 2021 Patrick Flynn
// This file is part of uds-explorer.
// uds-explorer is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QToolBar>
#include <QToolButton>

#include <browserwidget.hpp>

class NavBar : public QToolBar {
    Q_OBJECT
public:
    NavBar();
    ~NavBar();
    void setBrowserWidget(BrowserWidget *b);
private:
    BrowserWidget *bWidget;
    QToolButton *goBack, *goUp, *refresh, *home;
private slots:
    void onGoUpClicked();
    void onGoBackClicked();
    void onRefreshClicked();
    void onHomeClicked();
    void onDirChanged(QString path);
    void onHistoryChanged();
};
