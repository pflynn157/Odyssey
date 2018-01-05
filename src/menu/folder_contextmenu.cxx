#include <QIcon>

#include "folder_contextmenu.hh"
#include "tabwidget.hh"
#include "clipboard.hh"
#include "actions.hh"
#include "trash.hh"

FolderContextMenu::FolderContextMenu(BrowserWidget *b) {
    bWidget = b;

    openTab = new QAction(QIcon::fromTheme("tab-new"),"Open in New Tab",this);
    cut = new QAction(QIcon::fromTheme("edit-cut"),"Cut",this);
    copy = new QAction(QIcon::fromTheme("edit-copy"),"Copy",this);
    rename = new QAction(QIcon::fromTheme("edit-rename"),"Rename",this);
    trash = new QAction(QIcon::fromTheme("user-trash"),"Move to Trash",this);
    restore = new QAction(QIcon::fromTheme("view-refresh"),"Restore",this);
    deleteFolder = new QAction(QIcon::fromTheme("edit-delete"),"Delete",this);

    connect(openTab,&QAction::triggered,this,&FolderContextMenu::onOpenTabClicked);
    connect(cut,&QAction::triggered,this,&FolderContextMenu::onCutClicked);
    connect(copy,&QAction::triggered,this,&FolderContextMenu::onCopyClicked);
    connect(rename,&QAction::triggered,this,&FolderContextMenu::onRenameClicked);
    connect(trash,&QAction::triggered,this,&FolderContextMenu::onTrashFolderClicked);
    connect(restore,&QAction::triggered,this,&FolderContextMenu::onRestoreFolderClicked);
    connect(deleteFolder,&QAction::triggered,this,&FolderContextMenu::onDeleteFolderClicked);

    this->addAction(openTab);
    this->addSeparator();
    this->addAction(cut);
    this->addAction(copy);
    this->addSeparator();
    this->addAction(rename);
    this->addSeparator();
    if (TabWidget::currentWidget()->fsCurrentPath()==Trash::folderPath) {
        this->addAction(restore);
    } else {
        this->addAction(trash);
    }
    this->addAction(deleteFolder);
}

FolderContextMenu::~FolderContextMenu() {
    delete openTab;
    delete cut;
    delete copy;
    delete rename;
    delete trash;
    delete restore;
    delete deleteFolder;
}

void FolderContextMenu::onOpenTabClicked() {
    QString addr = bWidget->fsCurrentPath();
    if (!addr.endsWith("/")) {
        addr+="/";
    }
    addr+=bWidget->currentItemName();
    TabWidget::addNewTab(addr);
}

void FolderContextMenu::onCutClicked() {
    clipboard.fileName = bWidget->currentItemNames();
    clipboard.oldPath = bWidget->fsCurrentPath();
    clipboard.action = Clipboard_Actions::CUT;
}

void FolderContextMenu::onCopyClicked() {
    clipboard.fileName = bWidget->currentItemNames();
    clipboard.oldPath = bWidget->fsCurrentPath();
    clipboard.action = Clipboard_Actions::COPY;
}

void FolderContextMenu::onRenameClicked() {
    Actions::rename();
}

void FolderContextMenu::onTrashFolderClicked() {
    Actions::trash();
}

void FolderContextMenu::onRestoreFolderClicked() {
    Actions::restore();
}

void FolderContextMenu::onDeleteFolderClicked() {
    if (TabWidget::currentWidget()->fsCurrentPath()==Trash::folderPath) {
        Trash::deleteCurrentFile();
    } else {
        Actions::deleteFolder();
    }
}
