/*
    PAGINA DELL'ITEM QUANDO VIENE SELEZIONATO
*/
#ifndef ITEMPAGEUI_H
#define ITEMPAGEUI_H

#include "AbstractItem.h"
#include <QLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizePolicy>

class ItemPageUI : public QWidget
{
    Q_OBJECT

public:
    ItemPageUI(QSharedPointer<AbstractItem> itemChosen, QWidget *parent = nullptr);
    QLayout *showPage(QSharedPointer<AbstractItem> item);

signals:
    void backClicked();
    void editClicked();
    void removeClicked();

private:
    QSharedPointer<AbstractItem> item;

    QLabel *itemTitle;
    QLabel *itemYear;
    QLabel *itemCover;
    QLabel *itemDescription;
    QLabel *itemPublisher;
    QLabel *itemPlatform;
    QLabel *itemGenre;
    QLabel *itemAuthor;
    QLabel *itemNumPages;
    QLabel *itemNumChapters;
    QLabel *itemLanguage;
    QLabel *itemArtist;
    QLabel *itemBand;
    QLabel *itemAlbum;

    QFont customFont;
    QSizePolicy *customSizePolicy;
    QWidget *containerWidget;

    QPushButton *confirmButton;
    QPushButton *backButton;
    QPushButton *editButton;
    QPushButton *deleteButton;

    QLayout *detailsLayout;
    QVBoxLayout *detailsLayoutNoEdit;
    QVBoxLayout *pageLayout;
    QVBoxLayout *containerLayout;
    QHBoxLayout *layoutAusiliare;
    QHBoxLayout *buttonsLayout;
};

#endif