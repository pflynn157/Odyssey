#pragma once

#include <QListWidget>
#include <QSize>
#include <QString>
#include <QStringList>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QTimer>

class FileSystemWatcher;

class BrowserWidget : public QListWidget {
    Q_OBJECT
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
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    QSize defaultGridSize;
    QString currentPath;
    QStringList historyList;
    FileSystemWatcher *thread;
    QString currentItemTxt;
private slots:
    void onItemDoubleClicked(QListWidgetItem *item);
    void onItemClicked(QListWidgetItem *item);
signals:
    void dirChanged(QString path);
    void historyChanged();
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
