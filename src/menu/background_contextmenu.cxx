#include <QIcon>

#include "background_contextmenu.hh"
#include "clipboard.hh"
#include "actions.hh"

BackgroundContextMenu::BackgroundContextMenu(BrowserWidget *b) {
    bWidget = b;

    newFolder = new QAction(QIcon::fromTheme("folder-new"),"New Folder",this);
    newFile = new QAction(QIcon::fromTheme("document-new"),"New File",this);
    paste = new QAction(QIcon::fromTheme("edit-paste"),"Paste",this);

    connect(newFolder,&QAction::triggered,this,&BackgroundContextMenu::onNewFolderClicked);
    connect(newFile,&QAction::triggered,this,&BackgroundContextMenu::onNewFileClicked);
    connect(paste,&QAction::triggered,this,&BackgroundContextMenu::onPasteClicked);

    this->addAction(newFolder);
    this->addAction(newFile);
    this->addSeparator();
    this->addAction(paste);
}

BackgroundContextMenu::~BackgroundContextMenu() {
    delete newFolder;
    delete newFile;
    delete paste;
}

void BackgroundContextMenu::onNewFolderClicked() {
    Actions::newFolder();
}

void BackgroundContextMenu::onNewFileClicked() {
    Actions::newFile();
}

void BackgroundContextMenu::onPasteClicked() {
    clipboard.newPath = bWidget->fsCurrentPath();
    Actions::paste();
}
