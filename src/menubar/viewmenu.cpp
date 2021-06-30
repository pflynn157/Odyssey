//
// Copyright 2021 Patrick Flynn
// This file is part of Odyssey file explorer.
// Odyssey is licensed under the BSD-3 license. See the COPYING file for more information.
//
#include <QIcon>
#include <QKeySequence>

#include <menubar/viewmenu.hpp>
#include <tabwidget.hpp>

ViewMenu::ViewMenu() {
    this->setTitle("View");

    reload = new QAction(QPixmap(":/icons/view-refresh.svg"), "Reload", this);
    hidden = new QAction("View Hidden Files", this);

    hidden->setCheckable(true);
#ifdef _WIN32
    hidden->setChecked(false);
#else
    //hidden->setChecked(QVariant(Settings::getSetting("view/hidden","false")).toBool());
#endif

    reload->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_R));
    hidden->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_H));

    connect(reload, &QAction::triggered, this, &ViewMenu::onReloadClicked);
    connect(hidden, &QAction::triggered, this, &ViewMenu::onHiddenClicked);

    this->addAction(reload);
    this->addAction(hidden);
}

ViewMenu::~ViewMenu() {
    delete reload;
    delete hidden;
}

void ViewMenu::onReloadClicked() {
    TabWidget::currentWidget()->reload();
}

void ViewMenu::onHiddenClicked() {
#ifdef _WIN32
    //Windows: Use the registry
#else
    //Settings::writeSetting("view/hidden",QVariant(hidden->isChecked()).toString());
#endif
    TabWidget::currentWidget()->reload();
}
