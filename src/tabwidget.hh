#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTabWidget>

#include "browserwidget.hh"
#include "navbar.hh"
#include "addressbar_text.hh"
#include "trashbar.hh"

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
    static void displayTrashBar(bool disp);
private:
    static NavBar *navigationBar;
    static AddressBarText *addrText;
    static TrashBar *trashbar;
    QVBoxLayout *layout;
private slots:
    void onTabsChanged();
    void onTabClosed(int index);
};
