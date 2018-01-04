#pragma once

#include <QToolBar>
#include <QLineEdit>

#include "browserwidget.hh"
#include "endtoolbar.hh"

class AddressBarText : public QToolBar {
    Q_OBJECT
public:
    AddressBarText();
    ~AddressBarText();
    void setBrowserWidget(BrowserWidget *b);
private:
    BrowserWidget *bWidget;
    QLineEdit *addressEntry;
    EndToolbar *endtoolbar;
private slots:
    void onAddrEntryReturnPressed();
    void onDirChanged(QString path);
};
