#pragma once

#include <QMenu>
#include <QAction>

#include "../browserwidget.hh"

class FileContextMenu : public QMenu {
    Q_OBJECT
public:
    explicit FileContextMenu(BrowserWidget *b);
    ~FileContextMenu();
private:
    BrowserWidget *bWidget;
    QAction *cut, *copy;
private slots:
    void onCutClicked();
    void onCopyClicked();
};
