
#include "Collezione.h"
#include "MainWindow.h"

#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Collezione::getCollezione().fromFileJSON(QApplication::applicationDirPath() + "/../JSON/Items.json");
    MainWindow MainWindow;
    MainWindow.show();
    return app.exec();
}