/*
    VISITOR CHE LEGGE L'ITEM CREATO E RACCOGLIE I SUOI CAMPI
*/
#ifndef VISITORREADITEM_H
#define VISITORREADITEM_H

#include "AbstractConstVisitor.h"
#include "ItemCreationForm.h"
#include <QMap>
#include <QVariant>

class VisitorReadItem : public AbstractConstVisitor
{
public:
    VisitorReadItem();
    QMap<QString, QVariant> getFields() const;
    void visitBook(const Book &book) override;
    void visitGame(const Game &game) override;
    void visitMusic(const Music &music) override;

private:
    QMap<QString, QVariant> fieldToSet;
};

#endif