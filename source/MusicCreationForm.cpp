#include "MusicCreationForm.h"

MusicCreationForm::MusicCreationForm(QWidget *parent) : ItemCreationForm(parent)
{
    artistInput = new QLineEdit();
    bandInput = new QLineEdit();
    albumInput = new QLineEdit();

    formLayout->addRow("Artista", artistInput);
    formLayout->addRow("Band", bandInput);
    formLayout->addRow("Album", albumInput);
}

QString MusicCreationForm::getArtist() const { return artistInput->text(); }
QString MusicCreationForm::getBand() const { return bandInput->text(); }
QString MusicCreationForm::getAlbum() const { return albumInput->text(); }
QMap<QString, QVariant> MusicCreationForm::getNotDefaultFields() const
{
    QMap<QString, QVariant> fieldToRead;
    fieldToRead["Artista"] = getArtist();
    fieldToRead["Band"] = getBand();
    fieldToRead["Album"] = getAlbum();
    return fieldToRead;
}

void MusicCreationForm::setArtist(const QString &newArtist) { artistInput->setText(newArtist); }
void MusicCreationForm::setBand(const QString &newBand) { bandInput->setText(newBand); }
void MusicCreationForm::setAlbum(const QString &newAlbum) { albumInput->setText(newAlbum); }
void MusicCreationForm::setNotDefaultFields(const QMap<QString, QVariant> &fieldsToAdd)
{
    if (fieldsToAdd.contains("Artista"))
        setArtist(fieldsToAdd["Artista"].toString());
    if (fieldsToAdd.contains("Band"))
        setBand(fieldsToAdd["Band"].toString());
    if (fieldsToAdd.contains("Album"))
        setAlbum(fieldsToAdd["Album"].toString());
}

void MusicCreationForm::clearFields()
{
    titleInput->clear();
    yearInput->clear();
    coverImageInput->clear();
    artistInput->clear();
    bandInput->clear();
    albumInput->clear();
}

void MusicCreationForm::accept(FormVisitor &visitor)
{
    visitor.visitMusicForm(*this);
}

void MusicCreationForm::accept(FormConstVisitor &constVisitor) const
{
    constVisitor.visitMusicForm(*this);
}