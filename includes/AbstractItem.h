/*
    CLASSE BASE DEGLI ITEM ASTRATTA PRINCIPALE
*/
#ifndef ABSTRACTITEM_H
#define ABSTRACTITEM_H

#include "AbstractVisitor.h"
#include "AbstractConstVisitor.h"
#include <QString>
#include <QSharedPointer>
#include <QJsonObject>

class AbstractItem
{

protected:
    AbstractItem(const QString newImage = "Non disponibile", const QString newTitle = "Non disponibile", const QString newDescription = "Non disponibile", const int newYear = 0);

public:
    virtual ~AbstractItem();

    // Funzioni getter testuali
    QString getCoverImage() const;
    QString getTitle() const;
    QString getDescription() const;
    virtual QString getType() const = 0;
    int getYear() const;

    // Relative funzioni setter
    AbstractItem &setCoverImage(const QString &newImage);
    AbstractItem &setTitle(const QString &newTitle);
    AbstractItem &setDescription(const QString &newDescription);
    AbstractItem &setYear(const int &newYear);

    // Funzioni di visitor
    virtual void accept(AbstractVisitor &visitor) = 0;
    virtual void accept(AbstractConstVisitor &constVisitor) const = 0;

    // Funzioni relative al JSON
    virtual void itemToFileJSON(QJsonObject &jObject) const = 0;
    virtual void itemFromFileJSON(const QJsonObject &jObject) = 0;

private:
    QString coverImage;
    QString title;
    QString description;
    int year;
};

#endif
