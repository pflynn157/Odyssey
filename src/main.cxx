#include <QApplication>
#include <cpplib/settings.hh>

#include "window.hh"

using namespace CppLib;

int main(int argc, char *argv[]) {
    Settings::registerApp("cpp-explorer");
    Settings::setDefaultSettingsFile(":/rsc/settings.xml");
    Settings::initPaths();

    QApplication a(argc, argv);

    Window w;
    w.show();

    return a.exec();
}
