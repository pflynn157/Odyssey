#pragma once

#include <QMenu>
#include <QAction>

#include "browserwidget.hh"

class MultiContextMenu: public QMenu {
    Q_OBJECT
public:
    explicit MultiContextMenu(BrowserWidget *b);
    ~MultiContextMenu();
private:
    BrowserWidget *bWidget;
    QAction *cut, *copy, *trash, *restore, *deleteAll;
private slots:
    void onCutClicked();
    void onCopyClicked();
    void onTrashClicked();
    void onRestoreClicked();
    void onDeleteAllClicked();
};
