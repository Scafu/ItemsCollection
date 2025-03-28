#include "Music.h"

Music::Music(const QString newImage, const QString newTitle, const QString newDescription, const int newYear, const QString newArtist, const QString newBand, const QString newAlbum) : AbstractItem(newImage, newTitle, newDescription, newYear), artist(newArtist), band(newBand), album(newAlbum) {}

// Funzioni getter testuali
QString Music::getArtist() const { return artist; };
QString Music::getBand() const { return band; };
QString Music::getAlbum() const { return album; }
QString Music::getType() const { return "Music"; }

// Funzioni setter relative
Music &Music::setArtist(const QString &newArtist)
{
    this->artist = newArtist;
    return *this;
}
Music &Music::setBand(const QString &newBand)
{
    this->band = newBand;
    return *this;
}
Music &Music::setAlbum(const QString &newAlbum)
{
    this->album = newAlbum;
    return *this;
}

// Funzioni visitor
void Music::accept(AbstractVisitor &visitor) { visitor.visitMusic(*this); }
void Music::accept(AbstractConstVisitor &constVisitor) const { constVisitor.visitMusic(*this); }

// Funzioni JSON
void Music::itemToFileJSON(QJsonObject &jObject) const
{
    jObject["Tipo"] = getType();
    jObject["Titolo"] = getTitle();
    jObject["Anno"] = getYear();
    jObject["Immagine di Copertina"] = getCoverImage();
    jObject["Descrizione"] = getDescription();
    jObject["Artista"] = getArtist();
    jObject["Band"] = getBand();
    jObject["Album"] = getAlbum();
}
void Music::itemFromFileJSON(const QJsonObject &jObject)
{
    setTitle(jObject["Titolo"].toString());
    setYear(jObject["Anno"].toInt());
    setCoverImage(jObject["Immagine di Copertina"].toString());
    setDescription(jObject["Descrizione"].toString());
    setArtist(jObject["Artista"].toString());
    setBand(jObject["Band"].toString());
    setAlbum(jObject["Album"].toString());
}