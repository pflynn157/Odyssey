#pragma once

#include <QMenu>
#include <QAction>

#include "../browserwidget.hh"

class BackgroundContextMenu : public QMenu {
    Q_OBJECT
public:
    explicit BackgroundContextMenu(BrowserWidget *b);
    ~BackgroundContextMenu();
private:
    BrowserWidget *bWidget;
    QAction *paste;
private slots:
    void onPasteClicked();
};
