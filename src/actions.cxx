#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <iostream>

#include "actions.hh"
#include "clipboard.hh"

void Actions::paste() {
    QString oldAddr = clipboard.oldPath;
    if (!oldAddr.endsWith("/")) {
        oldAddr+="/";
    }
    QString newAddr = clipboard.newPath;
    if (!newAddr.endsWith("/")) {
        newAddr+="/";
    }

    oldAddr += clipboard.fileName;
    newAddr += clipboard.fileName;

    if (clipboard.action==Clipboard_Actions::CUT) {
        bool ret = QFile(oldAddr).rename(newAddr);
        if (ret==false) {
            QMessageBox msg;
            msg.setWindowTitle("Error");
            if (clipboard.filetype==Clipboard_FileType::TYPE_FILE) {
                msg.setText("There was an error moving this file.");
            } else {
                msg.setText("There was an error moving this folder.");
            }
            msg.setIcon(QMessageBox::Warning);
            msg.exec();
        }
    } else {
        if (clipboard.filetype==Clipboard_FileType::TYPE_FILE) {
            bool ret = QFile(oldAddr).copy(newAddr);
            if (ret==false) {
                QMessageBox msg;
                msg.setWindowTitle("Error");
                msg.setText("There was an error copying this file.");
                msg.setIcon(QMessageBox::Warning);
                msg.exec();
            }
        } else {
            copyDirectory(oldAddr,newAddr);
        }
    }

    clipboard.action = Clipboard_Actions::NONE;
}

void Actions::copyDirectory(QString oldPath, QString newPath) {
    if (!oldPath.endsWith("/")) {
        oldPath+="/";
    }
    if (!newPath.endsWith("/")) {
        newPath+="/";
    }
    QDir().mkpath(newPath);
    QStringList contents = QDir(oldPath).entryList(QDir::AllEntries | QDir::NoDotAndDotDot);
    for (int i = 0; i<contents.size(); i++) {
        QString current = oldPath+contents.at(i);
        if (QFileInfo(current).isDir()) {
            copyDirectory(current,newPath+contents.at(i));
        } else {
            QFile(current).copy(newPath+contents.at(i));
        }
    }
}
