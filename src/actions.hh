#pragma once

#include <QString>

class Actions {
public:
    static void paste();
private:
    static bool copyDirectory(QString oldPath, QString newPath);
};
