/* This is the format for our trash files
 * <trashcan>
 *     <item name="file1.txt">
 *        <restore>/home/user/Documents</restore>
 *     </item>
 *     <item name="story.docx">
 *        <restore>/home/user/Desktop</restore>
 *     </item>
 * </trashcan>
 */
#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QStringList>
#include <QFileInfo>
#include <QMessageBox>

#include "trash.hh"
#include "tinyxml2.h"
#include "tabwidget.hh"
#include "actions.hh"

QString Trash::filePath, Trash::folderPath;

using namespace tinyxml2;

void Trash::initPaths() {
    folderPath = QDir::homePath()+"/.cpp-explorer/trash/";
    if (!QDir(folderPath).exists()) {
        QDir().mkpath(folderPath);
    }
    filePath = QDir::homePath()+"/.cpp-explorer/trashinfo.xml";
    if (!QFile(filePath).exists()) {
        genTrashInfo();
    }
}

void Trash::trashFile(QString path) {
    QString name = QFileInfo(path).fileName();
    QString rstrPath = QFileInfo(path).absolutePath();

    XMLDocument *doc = new XMLDocument;
    doc->LoadFile(filePath.toStdString().c_str());
    XMLElement *root = doc->FirstChildElement("trashcan");
    if (root==nullptr) {
        return;
    }

    XMLElement *newItem = doc->NewElement("item");
    XMLElement *rstrItem = doc->NewElement("restore");
    root->InsertEndChild(newItem);
    newItem->InsertFirstChild(rstrItem);

    newItem->SetAttribute("name",name.toStdString().c_str());
    rstrItem->SetText(rstrPath.toStdString().c_str());

    doc->SaveFile(filePath.toStdString().c_str());
    QFile(path).rename(folderPath+name);
}

void Trash::restoreFile(QString filename) {
    XMLDocument *doc = new XMLDocument;
    doc->LoadFile(filePath.toStdString().c_str());
    XMLElement *root = doc->FirstChildElement("trashcan");
    if (root==nullptr) {
        return;
    }
    XMLElement *child, *old;
    child = root->FirstChildElement("item");
    while (child!=nullptr) {
        QString attr = QString(child->Attribute("name"));
        if (attr==filename) {
            break;
        }
        old = child;
        child = old->NextSiblingElement("item");
    }
    if (child==nullptr) {
        return;
    }
    XMLElement *restoreElement = child->FirstChildElement("restore");
    if (restoreElement==nullptr) {
        return;
    }
    QString loco = QString(restoreElement->GetText());
    if (!loco.endsWith("/")) {
        loco+="/";
    }
    loco+=filename;
    QString trashLoco = folderPath+filename;
    QFile(trashLoco).rename(loco);
    root->DeleteChild(child);
    doc->SaveFile(filePath.toStdString().c_str());
}

void Trash::deleteCurrentFile() {
    auto list = TabWidget::currentWidget()->currentItemNames();
    Actions::deleteFile();

    XMLDocument *doc = new XMLDocument;
    doc->LoadFile(filePath.toStdString().c_str());
    XMLElement *root = doc->FirstChildElement("trashcan");
    if (root==nullptr) {
        return;
    }
    for (int i = 0; i<list.size(); i++) {
        QString filename = list.at(i);
        XMLElement *child, *old;
        child = root->FirstChildElement("item");
        while (child!=nullptr) {
            QString attr = QString(child->Attribute("name"));
            if (attr==filename) {
                break;
            }
            old = child;
            child = old->NextSiblingElement("item");
        }
        if (child==nullptr) {
            continue;
        }
        root->DeleteChild(child);
    }
    doc->SaveFile(filePath.toStdString().c_str());
}

void Trash::emptyTrash() {
    QMessageBox msg;
    msg.setWindowTitle("Warning");
    msg.setIcon(QMessageBox::Warning);
    msg.setText("This will permanently delete all files in the trash. "
                "This action CANNOT be undone. Do you wish to continue?");
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int ret = msg.exec();
    if (ret==QMessageBox::Yes) {
        QStringList contents = QDir(folderPath).entryList(QDir::AllEntries | QDir::NoDotAndDotDot);
        for (int i = 0; i<contents.size(); i++) {
            QString current = folderPath+contents.at(i);
            if (QFileInfo(current).isDir()) {
                QDir(current).removeRecursively();
            } else {
                QFile(current).remove();
            }
        }
        QFile(filePath).remove();
        genTrashInfo();
    }
}

void Trash::genTrashInfo() {
    QFile file(filePath);
    if (file.open(QFile::ReadWrite)) {
        QTextStream writer(&file);
        writer << "<?xml version=\"1.0\"?>\n";
        writer << "<trashcan>\n";
        writer << "</trashcan>";
        writer.flush();
        file.close();
    }
}
