#include <QIcon>

#include "file_contextmenu.hh"
#include "clipboard.hh"

FileContextMenu::FileContextMenu(BrowserWidget *b) {
    bWidget = b;

    cut = new QAction(QIcon::fromTheme("edit-cut"),"Cut",this);
    copy = new QAction(QIcon::fromTheme("edit-copy"),"Copy",this);

    connect(cut,&QAction::triggered,this,&FileContextMenu::onCutClicked);
    connect(copy,&QAction::triggered,this,&FileContextMenu::onCopyClicked);

    this->addAction(cut);
    this->addAction(copy);
}

FileContextMenu::~FileContextMenu() {
    delete cut;
    delete copy;
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
