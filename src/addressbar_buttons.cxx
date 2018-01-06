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
#include "addressbar_buttons.hh"

AddressBarButtons::AddressBarButtons() {
    this->setMovable(false);
}

AddressBarButtons::~AddressBarButtons() {
}

void AddressBarButtons::setBrowserWidget(BrowserWidget *b) {
    bWidget = b;
    parsePath(bWidget->fsCurrentPath());
    connect(bWidget,SIGNAL(dirChanged(QString)),this,SLOT(onDirChanged(QString)));
}

void AddressBarButtons::parsePath(QString path) {
    this->clear();

    AddrPushButton *bt1 = new AddrPushButton("/",bWidget);
    bt1->setText("/");
    this->addWidget(bt1);

    QString name = "";
    QString currentPath = "";
    if (!path.endsWith("/")) {
        path+="/";
    }
    for (int i = 0; i<path.size(); i++) {
        currentPath+=path.at(i);
        if (path.at(i)=='/') {
            if (name!="") {
                AddrPushButton *btn = new AddrPushButton(currentPath,bWidget);
                btn->setText(name);
                this->addWidget(btn);
                name = "";
            }
        } else {
            name+=path.at(i);
        }
    }
}

void AddressBarButtons::onDirChanged(QString path) {
    parsePath(path);
}

//AddrPushButton
//This is the button for our button bar

AddrPushButton::AddrPushButton(QString path, BrowserWidget *b) {
    fullpath = path;
    bWidget = b;
    connect(this,&QPushButton::clicked,this,&AddrPushButton::onClicked);
}

void AddrPushButton::onClicked() {
    bWidget->loadDir(fullpath);
}
