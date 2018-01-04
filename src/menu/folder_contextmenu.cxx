#include <QIcon>

#include "folder_contextmenu.hh"
#include "tabwidget.hh"
#include "clipboard.hh"

FolderContextMenu::FolderContextMenu(BrowserWidget *b) {
    bWidget = b;

    openTab = new QAction(QIcon::fromTheme("tab-new"),"Open in New Tab",this);
    cut = new QAction(QIcon::fromTheme("edit-cut"),"Cut",this);
    copy = new QAction(QIcon::fromTheme("edit-copy"),"Copy",this);

    connect(openTab,&QAction::triggered,this,&FolderContextMenu::onOpenTabClicked);
    connect(cut,&QAction::triggered,this,&FolderContextMenu::onCutClicked);
    connect(copy,&QAction::triggered,this,&FolderContextMenu::onCopyClicked);

    this->addAction(openTab);
    this->addSeparator();
    this->addAction(cut);
    this->addAction(copy);
}

FolderContextMenu::~FolderContextMenu() {
    delete openTab;
    delete cut;
    delete copy;
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
    clipboard.fileName = bWidget->currentItemName();
    clipboard.oldPath = bWidget->fsCurrentPath();
    clipboard.action = Clipboard_Actions::CUT;
    clipboard.filetype = Clipboard_FileType::TYPE_FOLDER;
}

void FolderContextMenu::onCopyClicked() {
    clipboard.fileName = bWidget->currentItemName();
    clipboard.oldPath = bWidget->fsCurrentPath();
    clipboard.action = Clipboard_Actions::COPY;
    clipboard.filetype = Clipboard_FileType::TYPE_FOLDER;
}
