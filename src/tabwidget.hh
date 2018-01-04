#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTabWidget>

#include "browserwidget.hh"
#include "navbar.hh"
#include "addressbar_text.hh"

class TabWidget : public QWidget {
    Q_OBJECT
public:
    explicit TabWidget(NavBar *navbar, AddressBarText *addrTextBar);
    ~TabWidget();
    static QTabWidget *tabs;
    static void addNewTab(QString path);
    static void addNewTab();
    static BrowserWidget *currentWidget();
    static void updateTabName();
private:
    static NavBar *navigationBar;
    static AddressBarText *addrText;
    QVBoxLayout *layout;
private slots:
    void onTabsChanged();
    void onTabClosed(int index);
};
