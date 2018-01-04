#include <QIcon>

#include "background_contextmenu.hh"
#include "clipboard.hh"
#include "actions.hh"

BackgroundContextMenu::BackgroundContextMenu(BrowserWidget *b) {
    bWidget = b;

    paste = new QAction(QIcon::fromTheme("edit-paste"),"Paste",this);

    connect(paste,&QAction::triggered,this,&BackgroundContextMenu::onPasteClicked);

    this->addAction(paste);
}

BackgroundContextMenu::~BackgroundContextMenu() {
    delete paste;
}

void BackgroundContextMenu::onPasteClicked() {
    clipboard.newPath = bWidget->fsCurrentPath();
    Actions::paste();
}
