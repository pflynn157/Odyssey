#include <QIcon>
#include <QDir>
#include <iostream>

#include "navbar.hh"

NavBar::NavBar()
    : goBack(new QToolButton),
      goUp(new QToolButton)
{
    this->setMovable(false);

    goBack->setIcon(QIcon::fromTheme("go-previous"));
    goUp->setIcon(QIcon::fromTheme("go-up"));

    goBack->setEnabled(false);
    goUp->setEnabled(false);

    connect(goBack,&QToolButton::clicked,this,&NavBar::onGoBackClicked);
    connect(goUp,&QToolButton::clicked,this,&NavBar::onGoUpClicked);

    this->addWidget(goBack);
    this->addWidget(goUp);
}

NavBar::~NavBar() {
    delete goBack;
    delete goUp;
}

void NavBar::setBrowserWidget(BrowserWidget *b) {
    bWidget = b;
    if (bWidget->fsCurrentPath()=="/") {
        goUp->setEnabled(false);
    } else {
        goUp->setEnabled(true);
    }
    if (b->history().isEmpty()) {
        goBack->setEnabled(false);
    } else {
        goBack->setEnabled(true);
    }
    connect(bWidget,SIGNAL(dirChanged(QString)),this,SLOT(onDirChanged(QString)));
    connect(bWidget,&BrowserWidget::historyChanged,this,&NavBar::onHistoryChanged);
}

void NavBar::onGoUpClicked() {
    if (bWidget==nullptr) {
        return;
    }
    QString currentPath = bWidget->fsCurrentPath();
    QDir dir(currentPath);
    dir.cdUp();
    QString newPath = dir.path();
    std::cout << newPath.toStdString() << std::endl;
    bWidget->loadDir(newPath);
}

void NavBar::onGoBackClicked() {
    QString path = bWidget->history().first();
    bWidget->loadDir(path);
}

void NavBar::onDirChanged(QString path) {
    if (path=="/") {
        goUp->setEnabled(false);
    } else {
        goUp->setEnabled(true);
    }
}

void NavBar::onHistoryChanged() {
    if (bWidget->history().isEmpty()) {
        goBack->setEnabled(false);
    } else {
        goBack->setEnabled(true);
    }
}
