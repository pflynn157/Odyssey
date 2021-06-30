//
// Copyright 2021 Patrick Flynn
// This file is part of uds-explorer.
// uds-explorer is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <browserwidget.hpp>

class BrowserWidget;

class SearchBar : public QWidget {
    Q_OBJECT
public:
    explicit SearchBar(BrowserWidget *b);
    ~SearchBar();
private:
    BrowserWidget *bWidget;
    QHBoxLayout *layout;
    QLabel *label;
    QLineEdit *entry;
    QPushButton *close;
private slots:
    void onEnterPressed();
    void onCloseClicked();
};
