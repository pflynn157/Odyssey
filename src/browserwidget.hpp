//
// Copyright 2021 Patrick Flynn
// This file is part of Odyssey file explorer.
// Odyssey is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QSize>
#include <QString>
#include <QStringList>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>

#include <trashbar.hpp>
#include <searchbar.hpp>

class TrashBar;
class SearchBar;
class ListWidget;
class FileSystemWatcher;

class BrowserWidget : public QWidget {
    Q_OBJECT
    friend class ListWidget;
    friend class SearchBar;
public:
    BrowserWidget();
    ~BrowserWidget();
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
    QStringList currentItemNames();
    void selectAll();
private:
    QVBoxLayout *layout;
    QListWidget *listWidget;
    QSize defaultGridSize;
    QString currentPath;
    QStringList historyList;
    FileSystemWatcher *thread;
    QString currentItemTxt;
    TrashBar *trashbar;
    SearchBar *searchbar;
    QStringList searchPatterns;
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
    void keyPressEvent(QKeyEvent *event);
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
