#-------------------------------------------------
#
# Project created by QtCreator 2018-01-04T09:36:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CppExplorer
TEMPLATE = app
CONFIG += c++11
LIBS += -lsettings

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cxx \
        window.cxx \
    tabwidget.cxx \
    browserwidget.cxx \
    navbar.cxx \
    addressbar_text.cxx \
    endtoolbar.cxx \
    menu/folder_contextmenu.cxx \
    menu/file_contextmenu.cxx \
    menu/background_contextmenu.cxx \
    actions.cxx \
    tinyxml2.cpp \
    trash.cxx \
    trashbar.cxx \
    menu/multi_contextmenu.cxx \
    searchbar.cxx \
    menubar/filemenu.cxx

HEADERS += \
        window.hh \
    tabwidget.hh \
    browserwidget.hh \
    navbar.hh \
    addressbar_text.hh \
    endtoolbar.hh \
    menu/folder_contextmenu.hh \
    clipboard.hh \
    menu/file_contextmenu.hh \
    menu/background_contextmenu.hh \
    actions.hh \
    tinyxml2.h \
    trash.hh \
    trashbar.hh \
    menu/multi_contextmenu.hh \
    searchbar.hh \
    menubar/filemenu.hh

RESOURCES += \
    rsc.qrc
