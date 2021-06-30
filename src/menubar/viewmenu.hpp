//
// Copyright 2021 Patrick Flynn
// This file is part of uds-explorer.
// uds-explorer is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QMenu>
#include <QAction>

class ViewMenu : public QMenu {
    Q_OBJECT
public:
    ViewMenu();
    ~ViewMenu();
private:
    QAction *reload, *hidden;
private slots:
    void onReloadClicked();
    void onHiddenClicked();
};

