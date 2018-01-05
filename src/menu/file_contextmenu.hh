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
    QAction *open, *cut, *copy, *rename, *deleteFile;
private slots:
    void onOpenClicked();
    void onCutClicked();
    void onCopyClicked();
    void onRenameClicked();
    void onDeleteClicked();
};
