// Copyright 2018 Patrick Flynn
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//	this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this
//	list of conditions and the following disclaimer in the documentation and/or
//	other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may
//	be used to endorse or promote products derived from this software
//	without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include <QVariant>
#include <QIcon>
#include <cpplib/settings.hh>

#include "window.hh"

using namespace CppLib;

Window::Window(QWidget *parent)
    : QMainWindow(parent),
      menubar(new MenuBar)
{
    this->setWindowTitle("CppExplorer");
    this->setWindowIcon(QIcon::fromTheme("system-file-manager"));
    this->setMenuBar(menubar);

    int winX = QVariant(Settings::getSetting("window/x","700")).toInt();
    int winY = QVariant(Settings::getSetting("window/y","500")).toInt();
    this->resize(winX,winY);

    filemenu = new FileMenu(this);
    menubar->addMenu(filemenu);

    navbar = new NavBar;
    this->addToolBar(navbar);

    addrTxt = new AddressBarText;
    this->addToolBar(addrTxt);

    tabPane = new TabWidget(navbar,addrTxt);
    this->setCentralWidget(tabPane);
}

Window::~Window() {
    delete menubar;
    delete filemenu;
    delete navbar;
    delete addrTxt;
    delete tabPane;
}

void Window::closeApp() {
    Settings::writeSetting("window/x",QVariant(this->width()).toString());
    Settings::writeSetting("window/y",QVariant(this->height()).toString());
}

void Window::closeEvent(QCloseEvent *event) {
    closeApp();
    event->accept();
}

//MenuBar
//This is a custom menubar class. The only reason for its existence is to
//suppress the default Qt context menu that it has
void MenuBar::contextMenuEvent(QContextMenuEvent *) {
}
