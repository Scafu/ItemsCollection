/*
    CLASSE MAINWINDOW
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "AbstractItem.h"
#include "ItemPageUI.h"
#include "ItemPageEditUI.h"
#include <QMainWindow>
#include <QStackedWidget>
#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QFont>
#include <QLineEdit>

class Collezione;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QStackedWidget *getPila() const;
    void updateAreaItem();
    void updateColorButtonFilters();

    // Funzioni legate con la Toolbar
    void showHome();
    void showAbout();
    void showCrea();

    // Funzioni legate con gli Items
    void itemCliccato(QSharedPointer<AbstractItem> itemClicked);
    void showTypedForm(const QString &typeChosen);

private:
    QFont customFont;
    QWidget *homePage;
    QWidget *aboutPage;
    QLineEdit *searchBar;
    QScrollArea *itemsArea;
    QStackedWidget *stack;
    QToolBar *toolBar;
    QPushButton *gameButtonFilter;
    QPushButton *bookButtonFilter;
    QPushButton *musicButtonFilter;
    QPushButton *allButtonFilter;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *buttonFilterLayout;
    QHBoxLayout *searchBarLayout;
};

#endif