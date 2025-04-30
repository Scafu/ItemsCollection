#include "VisitorReadForm.h"
#include "BookCreationForm.h"
#include "GameCreationForm.h"
#include "MusicCreationForm.h"
#include "Book.h"
#include "Game.h"
#include "Music.h"

VisitorReadForm::VisitorReadForm(ItemCreationForm *form) : form(form) {}

QSharedPointer<AbstractItem> VisitorReadForm::getCompleteItem()
{
    return item;
}

void VisitorReadForm::visitBookForm(const BookCreationForm &bookForm)
{
    Book *emptyBook = new Book();
    (*emptyBook).setTitle(bookForm.getTitle());
    (*emptyBook).setYear(bookForm.getYear());
    (*emptyBook).setCoverImage(bookForm.getCoverImage());
    (*emptyBook).setDescription(bookForm.getDescription());
    (*emptyBook).setAuthor(bookForm.getAuthor());
    (*emptyBook).setLanguage(bookForm.getLanguage());
    (*emptyBook).setNumPages(bookForm.getNumPages());
    (*emptyBook).setNumChapters(bookForm.getNumChapters());
    item = QSharedPointer<AbstractItem>(emptyBook);
}

void VisitorReadForm::visitGameForm(const GameCreationForm &gameForm)
{
    Game *emptyGame = new Game();
    (*emptyGame).setTitle(gameForm.getTitle());
    (*emptyGame).setYear(gameForm.getYear());
    (*emptyGame).setCoverImage(gameForm.getCoverImage());
    (*emptyGame).setDescription(gameForm.getDescription());
    (*emptyGame).setPublisher(gameForm.getPublisher());
    (*emptyGame).setPlatform(gameForm.getPlatform());
    (*emptyGame).setGenre(gameForm.getGenre());
    item = QSharedPointer<AbstractItem>(emptyGame);
}

void VisitorReadForm::visitMusicForm(const MusicCreationForm &musicForm)
{
    Music *emptyMusic = new Music();
    (*emptyMusic).setTitle(musicForm.getTitle());
    (*emptyMusic).setYear(musicForm.getYear());
    (*emptyMusic).setCoverImage(musicForm.getCoverImage());
    (*emptyMusic).setDescription(musicForm.getDescription());
    (*emptyMusic).setArtist(musicForm.getArtist());
    (*emptyMusic).setBand(musicForm.getBand());
    (*emptyMusic).setAlbum(musicForm.getAlbum());
    item = QSharedPointer<AbstractItem>(emptyMusic);
}