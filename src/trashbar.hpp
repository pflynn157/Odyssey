//
// Copyright 2021 Patrick Flynn
// This file is part of uds-explorer.
// uds-explorer is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

#include <browserwidget.hpp>

class BrowserWidget;

class TrashBar : public QWidget {
    Q_OBJECT
public:
    TrashBar();
    ~TrashBar();
    void setBrowserWidget(BrowserWidget *b);
private:
    BrowserWidget *bWidget;
    QHBoxLayout *layout, *subLayout;
    QWidget *subWidget;
    QPushButton *restore, *deleteItem, *empty;
private slots:
    void onSelectionStateChanged(bool state);
    void onDeleteClicked();
    void onRestoreClicked();
    void onEmptyClicked();
};
