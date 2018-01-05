#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QSize>
#include <QString>
#include <QStringList>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QTimer>

#include "trashbar.hh"

class TrashBar;
class ListWidget;
class FileSystemWatcher;

class BrowserWidget : public QWidget {
    Q_OBJECT
    friend class ListWidget;
public:
    BrowserWidget();
    void setIconView();
    void setListView();
    void loadDir(QString path, bool recordHistory, bool firstLoad);
    void loadDir(QString path, bool recordHistory);
    void loadDir(QString path);
    void loadDir();
    QStringList history();
    void reload();
    QString fsCurrentPath();
    QString currentDirName();
    void startRefresh();
    void stopRefresh();
    QString currentItemName();
private:
    QVBoxLayout *layout;
    QListWidget *listWidget;
    QSize defaultGridSize;
    QString currentPath;
    QStringList historyList;
    FileSystemWatcher *thread;
    QString currentItemTxt;
    TrashBar *trashbar;
private slots:
    void onItemDoubleClicked(QListWidgetItem *item);
    void onItemClicked(QListWidgetItem *item);
signals:
    void dirChanged(QString path);
    void historyChanged();
    void selectionState(bool anySelected);
};

class ListWidget : public QListWidget {
    Q_OBJECT
public:
    explicit ListWidget(BrowserWidget *b);
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    BrowserWidget *bWidget;
};

class FileSystemWatcher : public QTimer {
    Q_OBJECT
public:
    FileSystemWatcher(BrowserWidget *widget);
private:
    BrowserWidget *bWidget;
private slots:
    void onRefresh();
};
