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
    QToolButton *goBack, *goUp;
private slots:
    void onGoUpClicked();
    void onGoBackClicked();
    void onDirChanged(QString path);
    void onHistoryChanged();
};
