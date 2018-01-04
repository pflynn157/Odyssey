#include <QIcon>

#include "endtoolbar.hh"

EndToolbar::EndToolbar()
    : iconView(new QToolButton),
      listView(new QToolButton)
{
    this->setMovable(false);
    /*this->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Ignored);
    this->adjustSize();*/

    iconView->setIcon(QIcon::fromTheme("view-list-icons"));
    listView->setIcon(QIcon::fromTheme("view-list-details"));

    connect(iconView,&QToolButton::clicked,this,&EndToolbar::onIconViewClicked);
    connect(listView,&QToolButton::clicked,this,&EndToolbar::onListViewClicked);

    this->addWidget(iconView);
    this->addWidget(listView);

    this->resize(this->minimumSize());
}

EndToolbar::~EndToolbar() {
    delete iconView;
    delete listView;
}

void EndToolbar::setBrowserWidget(BrowserWidget *b) {
    bWidget = b;
}

void EndToolbar::onIconViewClicked() {
    if (bWidget==nullptr) {
        return;
    }
    bWidget->setIconView();
}

void EndToolbar::onListViewClicked() {
    if (bWidget==nullptr) {
        return;
    }
    bWidget->setListView();
}
