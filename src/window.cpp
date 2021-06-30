//
// Copyright 2021 Patrick Flynn
// This file is part of uds-explorer.
// uds-explorer is licensed under the BSD-3 license. See the COPYING file for more information.
//
#include <QVariant>
#include <QIcon>
#include <QApplication>
#include <QMenuBar>

#include <window.hpp>
#include <actions.hpp>
#include <clipboard.hpp>

AddressBarText *Window::addrTxt;
AddressBarButtons *Window::addrButtons;

Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("File Explorer");
    this->setWindowIcon(QPixmap(":/icons/system-file-manager.svg"));
    this->menuBar()->setContextMenuPolicy(Qt::PreventContextMenu);

//#ifdef _WIN32
    //Windows: Use the registry
    int winX = 900;
    int winY = 500;
/*#else
    int winX = QVariant(Settings::getSetting("window/x","700")).toInt();
    int winY = QVariant(Settings::getSetting("window/y","500")).toInt();
#endif*/
    this->resize(winX,winY);

    filemenu = new FileMenu(this);
    editmenu = new EditMenu;
    viewmenu = new ViewMenu;
    helpmenu = new HelpMenu;

    this->menuBar()->addMenu(filemenu);
    this->menuBar()->addMenu(editmenu);
    this->menuBar()->addMenu(viewmenu);
    this->menuBar()->addMenu(helpmenu);

    navbar = new NavBar;
    this->addToolBar(navbar);

    addrTxt = new AddressBarText;
    addrTxt->hide();
    this->addToolBar(addrTxt);

    addrButtons = new AddressBarButtons;
    this->addToolBar(addrButtons);

    tabPane = new TabWidget(navbar);
    this->setCentralWidget(tabPane);

    sidebar = new SideBar;
    this->addDockWidget(Qt::LeftDockWidgetArea,sidebar);
}

Window::~Window() {
    delete filemenu;
    delete editmenu;
    delete viewmenu;
    delete helpmenu;
    delete navbar;
    delete addrTxt;
    delete addrButtons;
    delete tabPane;
    delete sidebar;
}

void Window::closeApp() {
/*#ifdef _WIN32
    //Windows: Use the registry
#else
    Settings::writeSetting("window/x",QVariant(this->width()).toString());
    Settings::writeSetting("window/y",QVariant(this->height()).toString());
#endif*/
}

void Window::closeEvent(QCloseEvent *event) {
    closeApp();
    event->accept();
}

void Window::keyPressEvent(QKeyEvent *event) {
    if (event->modifiers()==Qt::ControlModifier) {
        switch (event->key()) {
        case Qt::Key_Q: {
            closeApp();
            qApp->exit(0);
        } break;
        case Qt::Key_T: TabWidget::addNewTab(); break;
        case Qt::Key_N: Actions::newFile(); break;
        case Qt::Key_X: {
            clipboard.fileName = TabWidget::currentWidget()->currentItemNames();
            clipboard.oldPath = TabWidget::currentWidget()->fsCurrentPath();
            clipboard.action = Clipboard_Actions::CUT;
        } break;
        case Qt::Key_C: {
            clipboard.fileName = TabWidget::currentWidget()->currentItemNames();
            clipboard.oldPath = TabWidget::currentWidget()->fsCurrentPath();
            clipboard.action = Clipboard_Actions::COPY;
        } break;
        case Qt::Key_V: {
            clipboard.newPath = TabWidget::currentWidget()->fsCurrentPath();
            Actions::paste();
        } break;
        }
    } else if (event->modifiers()==(Qt::ControlModifier | Qt::ShiftModifier)) {
        switch (event->key()) {
        case Qt::Key_N: Actions::newFolder(); break;
        case Qt::Key_T: TabWidget::closeCurrentTab(); break;
        }
    }
    QMainWindow::keyPressEvent(event);
}
