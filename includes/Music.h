/*
    CLASSE CONCRETA MUSIC
*/

#ifndef MUSIC_H
#define MUSIC_H

#include "AbstractItem.h"

class Music : public AbstractItem
{

public:
    Music(const QString newImage = "Non disponibile", const QString newTitle = "Non disponibile", const QString newDescription = "Non disponibile", const int newYear = 0, const QString newArtist = "Non disponibile", const QString newBand = "Non disponibile", const QString newAlbum = "Non disponibile");

    // Funzione getter testuali
    QString getArtist() const;
    QString getBand() const;
    QString getAlbum() const;
    QString getType() const;

    // Funzioni setter relative
    Music &setArtist(const QString &newArtist);
    Music &setBand(const QString &newBand);
    Music &setAlbum(const QString &newAlbum);

    // Funzioni visitor
    void accept(AbstractVisitor &visitor) override;
    void accept(AbstractConstVisitor &constVisitor) const override;

    // Funzioni JSON
    void itemToFileJSON(QJsonObject &jObject) const;
    void itemFromFileJSON(const QJsonObject &jObject);

private:
    QString artist;
    QString band;
    QString album;
};

#endif