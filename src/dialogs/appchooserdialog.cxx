// Copyright 2018 Patrick Flynn
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//	this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this
//	list of conditions and the following disclaimer in the documentation and/or
//	other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may
//	be used to endorse or promote products derived from this software
//	without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include <QIcon>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QProcess>

#include "appchooserdialog.hh"
#include "tabwidget.hh"

AppChooserDialog::AppChooserDialog(QString currentFile)
    : layout(new QVBoxLayout),
      treeView(new QTreeWidget)
{
    currentFilePath = currentFile;

    this->setWindowTitle("Choose Application");
    this->resize(300,400);
    this->setLayout(layout);

    treeView->setColumnCount(1);
    treeView->setHeaderLabel("Choose Application...");
    layout->addWidget(treeView);

    allApps = new QTreeWidgetItem(treeView);
    allApps->setText(0,"All Applications");
    allApps->setIcon(0,QIcon::fromTheme("folder"));

    loadAll();

    connect(treeView,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(onItemDoubleClicked(QTreeWidgetItem*)));
}

AppChooserDialog::~AppChooserDialog() {
    delete treeView;
}

void AppChooserDialog::loadAll() {
    QDir dir("/usr/share/applications");
    QStringList files = dir.entryList(QStringList() << "*.desktop",QDir::Files,QDir::Name);
    for (int i = 0; i<files.size(); i++) {
        QString current = files.at(i);
        QString name = current;
        QString exe = "";
        QIcon icon;
        QStringList list = fileContent("/usr/share/applications/"+current);
        for (int j = 0; j<list.size(); j++) {
            if (QString(list.at(j)).startsWith("Name=")) {
                name = secondHalf(list.at(j));
            } else if (QString(list.at(j)).startsWith("Icon")) {
                QString iconName = secondHalf(list.at(j));
                if (QFile(iconName).exists()) {
                    icon = QPixmap(iconName);
                } else {
                    icon = QIcon::fromTheme(iconName);
                }
            } else if (QString(list.at(j)).startsWith("Exec")) {
                QString exeTmp = secondHalf(list.at(j));
                for (int k = 0; k<exeTmp.size(); k++) {
                    if (exeTmp.at(k)=='%') {
                        break;
                    }
                    exe+=exeTmp.at(k);
                }
            }
        }

        QTreeWidgetItem *item = new QTreeWidgetItem(allApps);
        item->setText(0,name);
        item->setIcon(0,icon);
        item->setText(1,exe);
        allApps->addChild(item);
    }
}

QStringList AppChooserDialog::fileContent(QString file) {
    QFile f(file);
    QStringList content;
    if (f.open(QFile::ReadOnly)) {
        QTextStream reader(&f);
        while (!reader.atEnd()) {
            content.push_back(reader.readLine());
        }
    }
    return content;
}

QString AppChooserDialog::secondHalf(QString line) {
    QString content = "";
    for (int i = 0; i<line.size(); i++) {
        if (line.at(i)=="=") {
            for (int j = i; j<line.size(); j++) {
                if (line.at(j)=='=') {
                    continue;
                }
                content+=line.at(j);
            }
        }
    }
    return content;
}

void AppChooserDialog::onItemDoubleClicked(QTreeWidgetItem *item) {
    QString name = item->text(0);
    if (name=="All Applications") {
        return;
    }
    QString exe = item->text(1);
    this->close();
    QString path = TabWidget::currentWidget()->fsCurrentPath();
    path+=currentFilePath;
    QStringList args;
    args.push_back("-c");
    args.push_back(exe+" "+path);
    QProcess::execute("/bin/bash",args);
}
