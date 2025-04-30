#include "CustomToolBar.h"
#include <QMessageBox>
CustomToolBar::CustomToolBar(MainWindow *mainWindow, QWidget *parent) : QToolBar(parent), mainWindow(mainWindow)
{

    home = new QPushButton("Home");
    home->setFixedSize(100, 40);
    collezione = new QPushButton("Collezione");
    collezione->setFixedSize(100, 40);
    crea = new QPushButton("Crea");
    crea->setFixedSize(100, 40);
    about = new QPushButton("About");
    about->setFixedSize(100, 40);
    exit = new QPushButton("Exit");
    exit->setFixedSize(100, 40);

    addWidget(home);
    addWidget(collezione);
    addWidget(crea);
    addWidget(about);
    addWidget(exit);

    connect(home, &QPushButton::clicked, mainWindow, &MainWindow::showHome);
    connect(about, &QPushButton::clicked, mainWindow, &MainWindow::showAbout);
    connect(collezione, &QPushButton::clicked, &Collezione::getCollezione(), &Collezione::collectionFromFile);
    connect(crea, &QPushButton::clicked, mainWindow, &MainWindow::showCrea);
    connect(exit, &QPushButton::clicked, mainWindow, [mainWindow]
            {
        auto risposta = QMessageBox::question(mainWindow, "Conferma", "Sei sicuro di voler annullare la modifica?", QMessageBox::Yes | QMessageBox::No);
        if (risposta == QMessageBox::Yes)
            mainWindow->close(); });

    setFixedHeight(50);
    setStyleSheet("QToolBar{border: 2px solid rgba(255, 255, 255, 0.2);}");
}
