#pragma once

#include <QToolBar>
#include <QToolButton>

#include "browserwidget.hh"

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
