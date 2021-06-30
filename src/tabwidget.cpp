//
// Copyright 2021 Patrick Flynn
// This file is part of uds-explorer.
// uds-explorer is licensed under the BSD-3 license. See the COPYING file for more information.
//
#include <QDir>

#include <tabwidget.hpp>
#include <window.hpp>

QTabWidget *TabWidget::tabs;
NavBar *TabWidget::navigationBar;

TabWidget::TabWidget(NavBar *navbar)
    : layout(new QVBoxLayout)
{
    navigationBar = navbar;

    layout->setContentsMargins(0,0,0,0);
    this->setLayout(layout);

    tabs = new QTabWidget;
    tabs->setTabsClosable(true);
    tabs->setMovable(true);
    tabs->setTabBarAutoHide(true);
    layout->addWidget(tabs);

    connect(tabs,&QTabWidget::currentChanged,this,&TabWidget::onTabsChanged);
    connect(tabs,SIGNAL(tabCloseRequested(int)),this,SLOT(onTabClosed(int)));

    addNewTab();
}

TabWidget::~TabWidget() {
    delete tabs;
    delete layout;
}

void TabWidget::addNewTab(QString path) {
    int count = tabs->count();
    BrowserWidget *b = new BrowserWidget;
    b->loadDir(path,true,true);
    QString name = b->currentDirName();
    if (name=="") {
        name+="/";
    }
    tabs->addTab(b,name);
    tabs->setCurrentIndex(count);
    b->startRefresh();
    navigationBar->setBrowserWidget(b);
}

void TabWidget::addNewTab() {
    addNewTab(QDir::homePath());
}

void TabWidget::closeCurrentTab() {
    int index = tabs->currentIndex();
    if (tabs->count()==1) {
        addNewTab();
    }
    BrowserWidget *b = static_cast<BrowserWidget *>(tabs->widget(index));
    b->stopRefresh();
    delete b;
}

BrowserWidget *TabWidget::currentWidget() {
    BrowserWidget *w = static_cast<BrowserWidget *>(tabs->currentWidget());
    return w;
}

void TabWidget::updateTabName() {
    BrowserWidget *w = currentWidget();
    tabs->setTabText(tabs->currentIndex(),w->currentDirName());
}

QVector<BrowserWidget *> TabWidget::allWidgets() {
    QVector<BrowserWidget *> widgets;
    for (int i = 0; i<tabs->count(); i++) {
        BrowserWidget *current = static_cast<BrowserWidget *>(tabs->widget(i));
        widgets.push_back(current);
    }
    return widgets;
}

void TabWidget::onTabsChanged() {
    navigationBar->setBrowserWidget(currentWidget());
    Window::addrTxt->setBrowserWidget(currentWidget());
    Window::addrButtons->setBrowserWidget(currentWidget());
}

void TabWidget::onTabClosed(int index) {
    BrowserWidget *b = static_cast<BrowserWidget *>(tabs->widget(index));
    b->stopRefresh();
    delete b;
}
