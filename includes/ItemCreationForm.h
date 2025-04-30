/*
    CLASSE ASTRATTA DEI FORM PER LA CREAZIONE DEGL ITEM
*/
#ifndef ITEMCREATIONFORM_H
#define ITEMCREATIONFORM_H

#include "AbstractItem.h"
#include "FormVisitor.h"
#include "FormConstVisitor.h"
#include <QWidget>
#include <QSharedPointer>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

class ItemCreationForm : public QWidget
{
    Q_OBJECT

public:
    explicit ItemCreationForm(QWidget *parent = nullptr);

    // Funzioni getter testuali
    QString getCoverImage() const;
    QString getTitle() const;
    QString getDescription() const;
    int getYear() const;
    virtual QMap<QString, QVariant> getNotDefaultFields() const = 0;

    // Relative funzioni setter
    void setCoverImage(const QString &newImage);
    void setTitle(const QString &newTitle);
    void setDescription(const QString &newDescription);
    void setYear(const int &newYear);
    virtual void setNotDefaultFields(const QMap<QString, QVariant> &fieldsToAdd) = 0;

    // Funzioni di servizio
    virtual void clearFields() = 0;
    QString selectImage();
    static QSharedPointer<AbstractItem> createDerivedItem(const QString &typeChosen);
    virtual bool isDataValid(); // controlla che i dati che necessitano certe condizioni siano validi

    // Funzioni di visitor
    virtual void accept(FormVisitor &Visitor) = 0;
    virtual void accept(FormConstVisitor &constVisitor) const = 0;

signals:
    void createItem();     // conferma la creazione
    void deleteCreation(); // annulla la creazione

protected:
    QFont customFont;
    QLineEdit *titleInput;
    QLineEdit *yearInput;
    QLineEdit *coverImageInput;
    QLineEdit *descriptionInput;

    QPushButton *imageFolderButton;
    QPushButton *createButton;
    QPushButton *deleteButton;

    QVBoxLayout *layoutParent;
    QHBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QFormLayout *formLayout;
};

#endif