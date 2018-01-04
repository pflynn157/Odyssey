#include <QApplication>
#include <cpplib/settings.hh>

#include "window.hh"
#include "clipboard.hh"

using namespace CppLib;

Clipboard clipboard;

int main(int argc, char *argv[]) {
    Settings::registerApp("cpp-explorer");
    Settings::setDefaultSettingsFile(":/rsc/settings.xml");
    Settings::initPaths();

    QApplication a(argc, argv);

    Window w;
    w.show();

    return a.exec();
}
