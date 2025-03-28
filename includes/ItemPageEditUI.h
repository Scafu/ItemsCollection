/*
    PAGINA DELL'ITEM QUANDO VIENE SELEZIONATO IN VERSIONE EDITING
*/
#ifndef ITEMPAGEEDITUI_H
#define ITEMPAGEEDITUI_H

#include "AbstractItem.h"
#include <QLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizePolicy>

class ItemPageEditUI : public QWidget
{
    Q_OBJECT

public:
    ItemPageEditUI(QSharedPointer<AbstractItem> itemChosen, QWidget *parent = nullptr);
    QLayout *showPage(QSharedPointer<AbstractItem> item);
    void updateFields();
    QString selectImage();
signals:
    void backClicked();
    void confirmClicked();
    void removeClicked();

private:
    QSharedPointer<AbstractItem> item;
    QMap<QString, QVariant> fieldsEdited;

    QLineEdit *title;
    QLineEdit *year;
    QLineEdit *cover;
    QLineEdit *description;
    QLineEdit *publisher;
    QLineEdit *platform;
    QLineEdit *genre;
    QLineEdit *author;
    QLineEdit *numPages;
    QLineEdit *numChapters;
    QLineEdit *language;
    QLineEdit *artist;
    QLineEdit *band;
    QLineEdit *album;

    QFont customFont;
    QSizePolicy *customSizePolicy;
    QWidget *containerWidget;

    QPushButton *confirmButton;
    QPushButton *backButton;
    QPushButton *deleteButton;

    QLayout *detailsLayout;
    QFormLayout *detailsLayoutEdit;
    QVBoxLayout *pageLayout;
    QVBoxLayout *containerLayout;
    QHBoxLayout *layoutAusiliare;
    QHBoxLayout *buttonsLayout;
};

#endif