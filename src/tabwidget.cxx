#include <QDir>
#include <iostream>

#include "tabwidget.hh"

QTabWidget *TabWidget::tabs;
NavBar *TabWidget::navigationBar;
AddressBarText *TabWidget::addrText;

TabWidget::TabWidget(NavBar *navbar, AddressBarText *addrTextBar)
    : layout(new QVBoxLayout)
{
    navigationBar = navbar;
    addrText = addrTextBar;

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

BrowserWidget *TabWidget::currentWidget() {
    BrowserWidget *w = static_cast<BrowserWidget *>(tabs->currentWidget());
    return w;
}

void TabWidget::updateTabName() {
    BrowserWidget *w = currentWidget();
    tabs->setTabText(tabs->currentIndex(),w->currentDirName());
}

void TabWidget::onTabsChanged() {
    navigationBar->setBrowserWidget(currentWidget());
    addrText->setBrowserWidget(currentWidget());
}

void TabWidget::onTabClosed(int index) {
    BrowserWidget *b = static_cast<BrowserWidget *>(tabs->widget(index));
    b->stopRefresh();
    delete b;
}
