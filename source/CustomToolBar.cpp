#include "CustomToolBar.h"

CustomToolBar::CustomToolBar(MainWindow *mainWindow, QWidget *parent) : QToolBar(parent), mainWindow(mainWindow)
{

    home = new QPushButton("Home");
    home->setFixedSize(100, 40);
    crea = new QPushButton("Crea");
    crea->setFixedSize(100, 40);
    about = new QPushButton("About");
    about->setFixedSize(100, 40);
    exit = new QPushButton("Exit");
    exit->setFixedSize(100, 40);

    addWidget(home);
    addWidget(crea);
    addWidget(about);
    addWidget(exit);

    connect(home, &QPushButton::clicked, mainWindow, &MainWindow::showHome);
    connect(about, &QPushButton::clicked, mainWindow, &MainWindow::close);
    connect(crea, &QPushButton::clicked, mainWindow, &MainWindow::showCrea);
    connect(exit, &QPushButton::clicked, mainWindow, &MainWindow::close);

    setFixedHeight(50);
    setStyleSheet("QToolBar{border: 2px solid rgba(255, 255, 255, 0.2);}");
}