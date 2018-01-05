#include "trashbar.hh"
#include "actions.hh"
#include "trash.hh"

TrashBar::TrashBar()
    : layout(new QHBoxLayout),
      subLayout(new QHBoxLayout),
      subWidget(new QWidget),
      restore(new QPushButton("Restore")),
      deleteItem(new QPushButton("Delete")),
      empty(new QPushButton("Empty Trash"))
{
    this->setLayout(layout);

    restore->setEnabled(false);
    deleteItem->setEnabled(false);

    connect(restore,&QPushButton::clicked,this,&TrashBar::onRestoreClicked);
    connect(deleteItem,&QPushButton::clicked,this,&TrashBar::onDeleteClicked);
    connect(empty,&QPushButton::clicked,this,&TrashBar::onEmptyClicked);

    subLayout->setContentsMargins(0,0,0,0);
    subWidget->setLayout(subLayout);
    layout->addWidget(subWidget,0,Qt::AlignLeft);

    subLayout->addWidget(restore);
    subLayout->addWidget(deleteItem);
    subLayout->addWidget(empty);
}

TrashBar::~TrashBar() {
    delete layout;
    delete restore;
    delete deleteItem;
    delete empty;
}

void TrashBar::setBrowserWidget(BrowserWidget *b) {
    bWidget = b;
    connect(bWidget,SIGNAL(selectionState(bool)),this,SLOT(onSelectionStateChanged(bool)));
}

void TrashBar::onSelectionStateChanged(bool state) {
    restore->setEnabled(state);
    deleteItem->setEnabled(state);
}

void TrashBar::onRestoreClicked() {
    Actions::restore();
}

void TrashBar::onDeleteClicked() {
    Trash::deleteCurrentFile();
}

void TrashBar::onEmptyClicked() {
    Trash::emptyTrash();
}
