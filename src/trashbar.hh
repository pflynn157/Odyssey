#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

#include "browserwidget.hh"

class TrashBar : public QWidget {
    Q_OBJECT
public:
    TrashBar();
    ~TrashBar();
    void setBrowserWidget(BrowserWidget *b);
private:
    BrowserWidget *bWidget;
    QHBoxLayout *layout, *subLayout;
    QWidget *subWidget;
    QPushButton *restore, *deleteItem, *empty;
private slots:
    void onSelectionStateChanged(bool state);
    void onDeleteClicked();
    void onRestoreClicked();
    void onEmptyClicked();
};
