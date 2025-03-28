#include "VisitorReadItem.h"
#include "Book.h"
#include "Game.h"
#include "Music.h"

VisitorReadItem::VisitorReadItem() {}

void VisitorReadItem::visitBook(const Book &book)
{
    fieldToSet["Titolo"] = book.getTitle();
    fieldToSet["Anno"] = book.getYear();
    fieldToSet["Immagine di Copertina"] = book.getCoverImage();
    fieldToSet["Descrizione"] = book.getDescription();
    fieldToSet["Autore"] = book.getAuthor();
    fieldToSet["Lingua"] = book.getLanguage();
    fieldToSet["Numero di Pagine"] = book.getNumPages();
    fieldToSet["Numero di Capitoli"] = book.getNumChapters();
}
void VisitorReadItem::visitGame(const Game &game)
{
    fieldToSet["Titolo"] = game.getTitle();
    fieldToSet["Anno"] = game.getYear();
    fieldToSet["Immagine di Copertina"] = game.getCoverImage();
    fieldToSet["Descrizione"] = game.getDescription();
    fieldToSet["Publisher"] = game.getPublisher();
    fieldToSet["Piattaforma"] = game.getPlatform();
    fieldToSet["Genere"] = game.getGenre();
}
void VisitorReadItem::visitMusic(const Music &music)
{
    fieldToSet["Titolo"] = music.getTitle();
    fieldToSet["Anno"] = music.getYear();
    fieldToSet["Immagine di Copertina"] = music.getCoverImage();
    fieldToSet["Descrizione"] = music.getDescription();
    fieldToSet["Artista"] = music.getArtist();
    fieldToSet["Band"] = music.getBand();
    fieldToSet["Album"] = music.getAlbum();
}

QMap<QString, QVariant> VisitorReadItem::getFields() const { return fieldToSet; }