#pragma once

#include <QString>

class Actions {
public:
    static void paste();
private:
    static void copyDirectory(QString oldPath, QString newPath);
};
