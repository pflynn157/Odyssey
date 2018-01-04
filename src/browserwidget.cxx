#include <QDir>
#include <QVector>
#include <QIcon>
#include <iostream>

#include "browserwidget.hh"
#include "tabwidget.hh"

BrowserWidget::BrowserWidget() {
    defaultGridSize = this->gridSize();
    setIconView();
    connect(this,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(onItemDoubleClicked(QListWidgetItem*)));
}

void BrowserWidget::setIconView() {
    this->setViewMode(QListWidget::IconMode);
    this->setFlow(QListWidget::LeftToRight);
    this->setWrapping(true);
    this->setMovement(QListWidget::Snap);
    this->setResizeMode(QListWidget::Adjust);
    this->setGridSize(QSize(80,80));
    this->setWordWrap(true);
}

void BrowserWidget::setListView() {
    this->setViewMode(QListWidget::ListMode);
    this->setFlow(QListWidget::TopToBottom);
    this->setWrapping(true);
    this->setMovement(QListWidget::Snap);
    this->setResizeMode(QListWidget::Adjust);
    this->setGridSize(defaultGridSize);
    this->setWordWrap(true);
}

void BrowserWidget::loadDir(QString path, bool recordHistory, bool firstLoad) {
    if (recordHistory) {
        emit dirChanged(path);
        if (!currentPath.isEmpty()) {
            historyList.push_front(currentPath);
            emit historyChanged();
        }
    }
    currentPath = path;
    this->clear();
    QDir dir(path);

    QStringList folders = dir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::Name | QDir::IgnoreCase);
    QStringList files = dir.entryList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name | QDir::IgnoreCase);

    QVector<QListWidgetItem *> folderItems, fileItems;

    for (int i = 0; i<folders.size(); i++) {
        QListWidgetItem *item = new QListWidgetItem(folders.at(i));
        item->setIcon(QIcon::fromTheme("folder"));
        folderItems.push_back(item);
    }

    for (int i = 0; i<files.size(); i++) {
        QListWidgetItem *item = new QListWidgetItem(files.at(i));
        item->setIcon(QIcon::fromTheme("text-plain"));
        fileItems.push_back(item);
    }

    for (int i = 0; i<folderItems.size(); i++) {
        this->addItem(folderItems.at(i));
    }

    for (int i = 0; i<fileItems.size(); i++) {
        this->addItem(fileItems.at(i));
    }

    if (firstLoad==false) {
        TabWidget::updateTabName();
    }
}

void BrowserWidget::loadDir(QString path, bool recordHistory) {
    loadDir(path,recordHistory,false);
}

void BrowserWidget::loadDir(QString path) {
    loadDir(path,true);
}

void BrowserWidget::loadDir() {
    loadDir(QDir::homePath());
}

QStringList BrowserWidget::history() {
    return historyList;
}

void BrowserWidget::reload() {
    QList<QListWidgetItem *> items = this->selectedItems();
    QStringList oldNames;
    for (int i = 0; i<items.size(); i++) {
        oldNames.push_back(items.at(i)->text());
    }
    loadDir(currentPath,false);

    for (int i = 0; i<this->count(); i++) {
        QListWidgetItem *item = this->item(i);
        for (int j = 0; j<oldNames.size(); j++) {
            if (item->text()==oldNames.at(j)) {
                item->setSelected(true);
            }
        }
    }
}

QString BrowserWidget::fsCurrentPath() {
    return currentPath;
}

QString BrowserWidget::currentDirName() {
    QDir dir(currentPath);
    QString name = dir.dirName();
    if (name=="") {
        name = "/";
    }
    return name;
}

void BrowserWidget::startRefresh() {
    thread = new FileSystemWatcher(this);
    thread->start(2000);
}

void BrowserWidget::stopRefresh() {
    thread->stop();
}

void BrowserWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button()==Qt::LeftButton) {
        QListWidgetItem *item = this->itemAt(event->x(),event->y());
        if (item==nullptr) {
            QList<QListWidgetItem *> selectedItems = this->selectedItems();
            for (int i = 0; i<selectedItems.size(); i++) {
                selectedItems.at(i)->setSelected(false);
            }
        }
    }
    QListWidget::mousePressEvent(event);
}

void BrowserWidget::onItemDoubleClicked(QListWidgetItem *item) {
    QString path = currentPath;
    if (!path.endsWith("/")) {
        path+="/";
    }
    path+=item->text();
    if (QFileInfo(path).isDir()) {
        loadDir(path);
    }
}

//FileSystemWatcher class
//This is class is an extended QTimer.
//Its purpose is to refresh the BrowserWidget every second so that files/folders created outside
//the program are included in our view.
FileSystemWatcher::FileSystemWatcher(BrowserWidget *widget) {
    bWidget = widget;
    connect(this,&QTimer::timeout,this,&FileSystemWatcher::onRefresh);
}

void FileSystemWatcher::onRefresh() {
    bWidget->reload();
}
