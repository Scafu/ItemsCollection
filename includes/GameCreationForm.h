/*
    CLASSE CONCRETA GAMECREATIONFORM
*/

#ifndef GAMECREATIONFORM_H
#define GAMECREATIONFORM_H

#include "ItemCreationForm.h"

class GameCreationForm : public ItemCreationForm
{
    Q_OBJECT

public:
    explicit GameCreationForm(QWidget *parent = nullptr);

    // Funzioni getter testuali
    QString getPublisher() const;
    QString getPlatform() const;
    QString getGenre() const;
    QMap<QString, QVariant> getNotDefaultFields() const override;

    // Relative funzioni setter
    void setPublisher(const QString &newPublisher);
    void setPlatform(const QString &newPlatform);
    void setGenre(const QString &newGenre);
    void setNotDefaultFields(const QMap<QString, QVariant> &fieldsToAdd) override;

    // Funzioni di servizio
    void clearFields() override;
    static QSharedPointer<AbstractItem> createDerivedItem(const QString &typeChosen);

    // Funzioni di visitor
    void accept(FormVisitor &Visitor) override;
    void accept(FormConstVisitor &constVisitor) const override;

private:
    QLineEdit *publisherInput;
    QLineEdit *platformInput;
    QLineEdit *genreInput;
};

#endif