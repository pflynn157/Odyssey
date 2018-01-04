#include <QDir>
#include <QMessageBox>

#include "addressbar_text.hh"
#include "endtoolbar.hh"

AddressBarText::AddressBarText()
    : addressEntry(new QLineEdit)
{
    this->setMovable(false);

    addressEntry->setClearButtonEnabled(true);
    connect(addressEntry,&QLineEdit::returnPressed,this,&AddressBarText::onAddrEntryReturnPressed);

    this->addWidget(addressEntry);

    endtoolbar = new EndToolbar;
    this->addWidget(endtoolbar);
}

AddressBarText::~AddressBarText() {
    delete addressEntry;
    delete endtoolbar;
}

void AddressBarText::setBrowserWidget(BrowserWidget *b) {
    bWidget = b;
    addressEntry->setText(bWidget->fsCurrentPath());
    endtoolbar->setBrowserWidget(bWidget);
    connect(bWidget,SIGNAL(dirChanged(QString)),this,SLOT(onDirChanged(QString)));
}

void AddressBarText::onAddrEntryReturnPressed() {
    if (bWidget==nullptr) {
        return;
    }
    QString path = addressEntry->text();
    if (QDir(path).exists()) {
        bWidget->loadDir(path);
    } else {
        QMessageBox msg;
        msg.setWindowTitle("Error");
        msg.setText("Unknown file path");
        msg.setIcon(QMessageBox::Warning);
        msg.exec();
        addressEntry->setText(bWidget->fsCurrentPath());
    }
}

void AddressBarText::onDirChanged(QString path) {
    addressEntry->setText(path);
}
