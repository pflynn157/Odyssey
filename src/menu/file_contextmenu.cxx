#include <QIcon>

#include "file_contextmenu.hh"
#include "clipboard.hh"
#include "actions.hh"

FileContextMenu::FileContextMenu(BrowserWidget *b) {
    bWidget = b;

    cut = new QAction(QIcon::fromTheme("edit-cut"),"Cut",this);
    copy = new QAction(QIcon::fromTheme("edit-copy"),"Copy",this);
    rename = new QAction(QIcon::fromTheme("edit-rename"),"Rename",this);
    deleteFile = new QAction(QIcon::fromTheme("edit-delete"),"Delete",this);

    connect(cut,&QAction::triggered,this,&FileContextMenu::onCutClicked);
    connect(copy,&QAction::triggered,this,&FileContextMenu::onCopyClicked);
    connect(rename,&QAction::triggered,this,&FileContextMenu::onRenameClicked);
    connect(deleteFile,&QAction::triggered,this,&FileContextMenu::onDeleteClicked);

    this->addAction(cut);
    this->addAction(copy);
    this->addSeparator();
    this->addAction(rename);
    this->addSeparator();
    this->addAction(deleteFile);
}

FileContextMenu::~FileContextMenu() {
    delete cut;
    delete copy;
    delete rename;
    delete deleteFile;
}

void FileContextMenu::onCutClicked() {
    clipboard.fileName = bWidget->currentItemName();
    clipboard.oldPath = bWidget->fsCurrentPath();
    clipboard.action = Clipboard_Actions::CUT;
    clipboard.filetype = Clipboard_FileType::TYPE_FILE;
}

void FileContextMenu::onCopyClicked() {
    clipboard.fileName = bWidget->currentItemName();
    clipboard.oldPath = bWidget->fsCurrentPath();
    clipboard.action = Clipboard_Actions::COPY;
    clipboard.filetype = Clipboard_FileType::TYPE_FILE;
}

void FileContextMenu::onRenameClicked() {
    Actions::rename();
}

void FileContextMenu::onDeleteClicked() {
    Actions::deleteFile();
}
