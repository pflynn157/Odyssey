//
// Copyright 2021 Patrick Flynn
// This file is part of Odyssey file explorer.
// Odyssey is licensed under the BSD-3 license. See the COPYING file for more information.
//
#include <QApplication>
#include <QString>
#include <QStandardPaths>

#include <window.hpp>
#include <clipboard.hpp>
#include <trash.hpp>
#include <tabwidget.hpp>

Clipboard clipboard;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Trash::initPaths();

    Window w;
    w.show();
    
    if (argc == 2) {
        QString path = QString(argv[1]);
        
        if (path == "trash" || path.startsWith("trash")) {
            TabWidget::currentWidget()->loadDir(Trash::folderPath);
        } else if (path == "computer" || path.startsWith("computer")) {
            // TODO: We should eventually have a computer tab
            TabWidget::currentWidget()->loadDir(QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
        } else {
            TabWidget::currentWidget()->loadDir(path);
        }
    }

    return a.exec();
}

