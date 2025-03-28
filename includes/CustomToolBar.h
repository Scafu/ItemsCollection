/*
    CLASSE TOOLBAR
*/
#ifndef CUSTOMTOOLBAR_H
#define CUSTOMTOOLBAR_H

#include "MainWindow.h"
#include <QToolBar>
#include <QPushButton>

class CustomToolBar : public QToolBar
{
    Q_OBJECT

public:
    CustomToolBar(MainWindow *mainWindow, QWidget *parent = nullptr);

private:
    QPushButton *home;
    QPushButton *about;
    QPushButton *crea;
    QPushButton *exit;
    MainWindow *mainWindow;
    QWidget *itemType;
};

#endif