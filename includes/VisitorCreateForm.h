/*
    VISITOR CHE PERMETTE LA CREAZIONE DEL FORM IN BASE AL TIPO DATO
*/
#ifndef VISITORCREATEFORM_H
#define VISITORCREATEFORM_H

#include "ItemCreationForm.h"
#include "BookCreationForm.h"
#include "GameCreationForm.h"
#include "MusicCreationForm.h"
#include "AbstractVisitor.h"
#include "AbstractItem.h"

class VisitorCreateForm : public AbstractVisitor
{
public:
    explicit VisitorCreateForm(QSharedPointer<AbstractItem> item);
    QSharedPointer<ItemCreationForm> getFormItem();
    void visitBook(Book &libro) override;
    void visitGame(Game &game) override;
    void visitMusic(Music &music) override;

private:
    QSharedPointer<AbstractItem> item;
    ItemCreationForm *form;
};

#endif