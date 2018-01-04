#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QTabWidget>

#include "browserwidget.hh"
#include "navbar.hh"

class TabWidget : public QWidget {
    Q_OBJECT
public:
    explicit TabWidget(NavBar *navbar);
    ~TabWidget();
    static QTabWidget *tabs;
    static void addNewTab(QString path);
    static void addNewTab();
    static BrowserWidget *currentWidget();
    static void updateTabName();
private:
    static NavBar *navigationBar;
    QVBoxLayout *layout;
private slots:
    void onTabsChanged();
    void onTabClosed(int index);
};
