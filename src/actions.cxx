#include <QFile>
#include <QDir>
#include <QMessageBox>

#include "actions.hh"
#include "clipboard.hh"

void Actions::paste() {
    if (!clipboard.oldPath.endsWith("/")) {
        clipboard.oldPath+="/";
    }
    if (!clipboard.newPath.endsWith("/")) {
        clipboard.newPath+="/";
    }

    QString oldAddr = clipboard.oldPath;
    QString newAddr = clipboard.newPath;

    oldAddr += clipboard.fileName;
    newAddr += clipboard.fileName;

    if (clipboard.action==Clipboard_Actions::CUT) {
        bool ret = QFile(oldAddr).rename(newAddr);
        if (ret==false) {
            if (QFileInfo(newAddr).exists()) {
                newAddr = handleDuplicate(newAddr);
                ret = QFile(oldAddr).rename(newAddr);
                if (ret==false) {
                    QMessageBox msg;
                    msg.setWindowTitle("Fatal Error");
                    msg.setText("An unknown critical error has occurred.");
                    msg.setIcon(QMessageBox::Critical);
                    msg.exec();
                }
            } else {
                QMessageBox msg;
                msg.setWindowTitle("Error");
                msg.setIcon(QMessageBox::Critical);
                msg.setText("There was an error moving this file!");
                msg.setDetailedText("This could mean that the file is read-only, "
                                    "or that you do not have the proper permissions "
                                    "to access it.");
                msg.exec();
            }
        }
    } else {
        bool ret;
        if (clipboard.filetype==Clipboard_FileType::TYPE_FILE) {
            ret = QFile(oldAddr).copy(newAddr);
        } else {
            ret = copyDirectory(oldAddr,newAddr);
        }
        if (ret==false) {
            if (QFileInfo(newAddr).exists()) {
                newAddr = handleDuplicate(newAddr);
                if (clipboard.filetype==Clipboard_FileType::TYPE_FILE) {
                    ret = QFile(oldAddr).copy(newAddr);
                } else {
                    ret = copyDirectory(oldAddr,newAddr);
                }
                if (ret==false) {
                    QMessageBox msg;
                    msg.setWindowTitle("Fatal Error");
                    msg.setText("An unknown critical error has occurred.");
                    msg.setIcon(QMessageBox::Critical);
                    msg.exec();
                }
            } else {
                QMessageBox msg;
                msg.setWindowTitle("Error");
                msg.setIcon(QMessageBox::Critical);
                msg.setText("There was an error moving this file!");
                msg.setDetailedText("This could mean that the file is read-only, "
                                    "or that you do not have the proper permissions "
                                    "to access it.");
                msg.exec();
            }
        }
    }

    if (clipboard.action==Clipboard_Actions::CUT) {
        clipboard.action = Clipboard_Actions::NONE;
    }
}

QString Actions::handleDuplicate(QString newAddr) {
    QMessageBox msg;
    msg.setWindowTitle("Warning");
    msg.setText("A file with the same name already exists. "
                "Do you wish to overwrite it?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msg.setIcon(QMessageBox::Question);
    int ret = msg.exec();
    if (ret==QMessageBox::Yes) {
        if (QFileInfo(newAddr).isDir()) {
            QDir(newAddr).removeRecursively();
        } else {
            QFile(newAddr).remove();
        }
    } else {
        newAddr = clipboard.newPath+"(copy) "+clipboard.fileName;
    }
    return newAddr;
}

bool Actions::copyDirectory(QString oldPath, QString newPath) {
    if (!oldPath.endsWith("/")) {
        oldPath+="/";
    }
    if (!newPath.endsWith("/")) {
        newPath+="/";
    }
    if (QDir(newPath).exists()) {
        return false;
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
    return true;
}
