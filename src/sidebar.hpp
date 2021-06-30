//
// Copyright 2021 Patrick Flynn
// This file is part of uds-explorer.
// uds-explorer is licensed under the BSD-3 license. See the COPYING file for more information.
//
#pragma once

#include <QDockWidget>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QTimer>

class PlacesList;
class DeviceList;

class SideBar : public QDockWidget {
    Q_OBJECT
public:
    SideBar();
    ~SideBar();
private:
    QWidget *mainWidget;
    QVBoxLayout *layout;
    PlacesList *placeslist;
    DeviceList *deviceslist;
};

class PlacesList : public QTreeWidget {
    Q_OBJECT
public:
    PlacesList();
    ~PlacesList();
private:
    QTreeWidgetItem *home, *docs, *pics, *downloads,
        *music, *videos, *templates, *trash;
private slots:
    void onItemClicked(QTreeWidgetItem *item);
};

class DeviceList : public QTreeWidget {
    Q_OBJECT
public:
    DeviceList();
    ~DeviceList();
private:
    QTimer *timer;
private slots:
    void loadDrives();
    void onItemClicked(QTreeWidgetItem *item);
};
