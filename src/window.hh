#pragma once

#include <QMainWindow>
#include <QCloseEvent>

#include "navbar.hh"

class Window : public QMainWindow {
    Q_OBJECT
public:
    Window(QWidget *parent = 0);
    ~Window();
    void closeApp();
protected:
    void closeEvent(QCloseEvent *event);
private:
    NavBar *navbar;
};
