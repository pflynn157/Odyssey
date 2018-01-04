#include <QVariant>
#include <cpplib/settings.hh>

#include "window.hh"
#include "tabwidget.hh"
#include "navbar.hh"
#include "addressbar_text.hh"
#include "endtoolbar.hh"

using namespace CppLib;

Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("CppExplorer");

    int winX = QVariant(Settings::getSetting("window/x","700")).toInt();
    int winY = QVariant(Settings::getSetting("window/y","500")).toInt();
    this->resize(winX,winY);

    navbar = new NavBar;
    this->addToolBar(navbar);

    AddressBarText *addrTxt = new AddressBarText;
    this->addToolBar(addrTxt);

    TabWidget *tabPane = new TabWidget(navbar,addrTxt);
    this->setCentralWidget(tabPane);
}

Window::~Window() {
}

void Window::closeApp() {
    Settings::writeSetting("window/x",QVariant(this->width()).toString());
    Settings::writeSetting("window/y",QVariant(this->height()).toString());
}

void Window::closeEvent(QCloseEvent *event) {
    closeApp();
    event->accept();
}
