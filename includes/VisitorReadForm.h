/*
    VISITOR CHE LEGGE IL FORM E CREA L'ITEM
*/
#ifndef VISITORREADFORM_H
#define VISITORREADFORM_H

#include "FormVisitor.h"
#include "ItemCreationForm.h"
#include <QMap>
#include <QVariant>

class VisitorReadForm : public FormVisitor
{
public:
    explicit VisitorReadForm(ItemCreationForm *form);
    QSharedPointer<AbstractItem> getCompleteItem();
    void visitBookForm(BookCreationForm &bookForm) override;
    void visitGameForm(GameCreationForm &gameForm) override;
    void visitMusicForm(MusicCreationForm &musicForm) override;

private:
    ItemCreationForm *form;
    QSharedPointer<AbstractItem> item;
};

#endif