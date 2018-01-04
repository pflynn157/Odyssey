#pragma once

#include <QToolBar>
#include <QLineEdit>

#include "browserwidget.hh"

class AddressBarText : public QToolBar {
    Q_OBJECT
public:
    AddressBarText();
    ~AddressBarText();
    void setBrowserWidget(BrowserWidget *b);
private:
    BrowserWidget *bWidget;
    QLineEdit *addressEntry;
private slots:
    void onAddrEntryReturnPressed();
};
