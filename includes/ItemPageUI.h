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
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSizePolicy>

class ItemPageUI : public QWidget
{
    Q_OBJECT

public:
    ItemPageUI(QSharedPointer<AbstractItem> itemChosen, QWidget *parent = nullptr);
    QLayout *showPage(bool editMode, QSharedPointer<AbstractItem> item);
    void updateFields();

private:
    QSharedPointer<AbstractItem> item;
    QMap<QString, QVariant> fieldsEdited;

    QLineEdit *title;
    QLineEdit *year;
    QLineEdit *description;
    QLineEdit *publisher;
    QLineEdit *platform;
    QLineEdit *genre;
    QLineEdit *author;
    QLineEdit *numPages;
    QLineEdit *numChapters;
    QLineEdit *language;
    QFont customFont;
    QSizePolicy *customSizePolicy;
    QWidget *containerWidget;
    QPushButton *backButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QLayout *detailsLayout;
    QFormLayout *detailsLayoutEdit;
    QVBoxLayout *pageLayout;
    QVBoxLayout *containerLayout;
    QHBoxLayout *layoutAusiliare;
    QHBoxLayout *buttonsLayout;
};

#endif