#include <QIcon>

#include "file_contextmenu.hh"
#include "clipboard.hh"
#include "actions.hh"
#include "tabwidget.hh"
#include "trash.hh"

FileContextMenu::FileContextMenu(BrowserWidget *b) {
    bWidget = b;

    open = new QAction(QIcon::fromTheme("document-open"),"Open",this);
    cut = new QAction(QIcon::fromTheme("edit-cut"),"Cut",this);
    copy = new QAction(QIcon::fromTheme("edit-copy"),"Copy",this);
    rename = new QAction(QIcon::fromTheme("edit-rename"),"Rename",this);
    trash = new QAction(QIcon::fromTheme("user-trash"),"Move to Trash",this);
    restore = new QAction(QIcon::fromTheme("view-refresh"),"Restore",this);
    deleteFile = new QAction(QIcon::fromTheme("edit-delete"),"Delete",this);

    connect(open,&QAction::triggered,this,&FileContextMenu::onOpenClicked);
    connect(cut,&QAction::triggered,this,&FileContextMenu::onCutClicked);
    connect(copy,&QAction::triggered,this,&FileContextMenu::onCopyClicked);
    connect(rename,&QAction::triggered,this,&FileContextMenu::onRenameClicked);
    connect(trash,&QAction::triggered,this,&FileContextMenu::onTrashClicked);
    connect(restore,&QAction::triggered,this,&FileContextMenu::onRestoreClicked);
    connect(deleteFile,&QAction::triggered,this,&FileContextMenu::onDeleteClicked);

    this->addAction(open);
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
    this->addAction(deleteFile);
}

FileContextMenu::~FileContextMenu() {
    delete open;
    delete cut;
    delete copy;
    delete rename;
    delete trash;
    delete restore;
    delete deleteFile;
}

void FileContextMenu::onOpenClicked() {
    Actions::openCurrentFile();
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

void FileContextMenu::onTrashClicked() {
    Actions::trash();
}

void FileContextMenu::onRestoreClicked() {
    Actions::restore();
}

void FileContextMenu::onDeleteClicked() {
    Actions::deleteFile();
}
