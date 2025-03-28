/*
    CLASSE CONCRETA MUSICCREATIONFORM
*/

#ifndef MUSICCREATIONFORM_H
#define MUSICCREATIONFORM_H

#include "ItemCreationForm.h"

class MusicCreationForm : public ItemCreationForm
{
    Q_OBJECT

public:
    explicit MusicCreationForm(QWidget *parent = nullptr);

    // Funzioni getter testuali
    QString getArtist() const;
    QString getBand() const;
    QString getAlbum() const;
    QMap<QString, QVariant> getNotDefaultFields() const override;

    // Relative funzioni setter
    void setArtist(const QString &newArtist);
    void setBand(const QString &newBand);
    void setAlbum(const QString &newAlbum);
    void setNotDefaultFields(const QMap<QString, QVariant> &fieldsToAdd) override;

    // Funzioni di servizio
    void clearFields() override;

    // Funzioni di visitor
    void accept(FormVisitor &Visitor) override;
    void accept(FormConstVisitor &constVisitor) const override;

private:
    QLineEdit *artistInput;
    QLineEdit *bandInput;
    QLineEdit *albumInput;
};

#endif