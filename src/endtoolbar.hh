#pragma once

#include <QToolBar>
#include <QToolButton>

#include "browserwidget.hh"

class EndToolbar : public QToolBar {
    Q_OBJECT
public:
    EndToolbar();
    ~EndToolbar();
    void setBrowserWidget(BrowserWidget *b);
private:
    BrowserWidget *bWidget;
    QToolButton *iconView, *listView;
private slots:
    void onIconViewClicked();
    void onListViewClicked();
};
