#include "VisitorCreateForm.h"

VisitorCreateForm::VisitorCreateForm(QSharedPointer<AbstractItem> item) : item(item), form(nullptr) {}

QSharedPointer<ItemCreationForm> VisitorCreateForm::getFormItem() { return QSharedPointer<ItemCreationForm>(form); }

void VisitorCreateForm::visitBook(Book &)
{
    BookCreationForm *bookForm = new BookCreationForm;
    form = bookForm;
}
void VisitorCreateForm::visitGame(Game &)
{
    GameCreationForm *gameForm = new GameCreationForm;
    form = gameForm;
}
void VisitorCreateForm::visitMusic(Music &)
{
    MusicCreationForm *musicForm = new MusicCreationForm;
    form = musicForm;
}