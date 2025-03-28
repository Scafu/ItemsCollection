#include "Game.h"

Game::Game(const QString newImage, const QString newTitle, const QString newDescription, const int newYear, const QString newPublisher, const QString newPlatform, const QString newGenre) : AbstractItem(newImage, newTitle, newDescription, newYear), publisher(newPublisher), platform(newPlatform), genre(newGenre) {}

// Funzioni getter testuali
QString Game::getPublisher() const { return publisher; };
QString Game::getPlatform() const { return platform; };
QString Game::getGenre() const { return genre; }
QString Game::getType() const { return "Game"; }

// Funzioni setter relative
Game &Game::setPublisher(const QString &newPublisher)
{
    this->publisher = newPublisher;
    return *this;
}
Game &Game::setPlatform(const QString &newPlatform)
{
    this->platform = newPlatform;
    return *this;
}
Game &Game::setGenre(const QString &newGenre)
{
    this->genre = newGenre;
    return *this;
}

// Funzioni visitor
void Game::accept(AbstractVisitor &visitor) { visitor.visitGame(*this); }
void Game::accept(AbstractConstVisitor &constVisitor) const { constVisitor.visitGame(*this); }

// Funzioni JSON
void Game::itemToFileJSON(QJsonObject &jObject) const
{
    jObject["Tipo"] = getType();
    jObject["Titolo"] = getTitle();
    jObject["Anno"] = getYear();
    jObject["Immagine di Copertina"] = getCoverImage();
    jObject["Descrizione"] = getDescription();
    jObject["Publisher"] = getPublisher();
    jObject["Piattaforma"] = getPlatform();
    jObject["Genere"] = getGenre();
}
void Game::itemFromFileJSON(const QJsonObject &jObject)
{
    setTitle(jObject["Titolo"].toString());
    setYear(jObject["Anno"].toInt());
    setCoverImage(jObject["Immagine di Copertina"].toString());
    setDescription(jObject["Descrizione"].toString());
    setPublisher(jObject["Publisher"].toString());
    setPlatform(jObject["Piattaforma"].toString());
    setGenre(jObject["Genere"].toString());
}