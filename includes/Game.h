/*
    CLASSE CONCRETA GAME
*/

#ifndef GAME_H
#define GAME_H

#include "AbstractItem.h"

class Game : public AbstractItem
{

public:
    Game(const QString newImage = "Non disponibile", const QString newTitle = "Non disponibile", const QString newDescription = "Non disponibile", const int newYear = 0, const QString newPlatform = "Non disponibile", const QString newPublisher = "Non disponibile", const QString newGenre = "Non disponibile");

    // Funzione getter testuali
    QString getPlatform() const;
    QString getPublisher() const;
    QString getGenre() const;
    QString getType() const;

    // Funzioni setter relative
    Game &setPlatform(const QString &newPlatform);
    Game &setPublisher(const QString &newPublisher);
    Game &setGenre(const QString &newGenre);

    // Funzioni visitor
    void accept(AbstractVisitor &visitor) override;
    void accept(AbstractConstVisitor &constVisitor) const override;

    // Funzioni JSON
    void itemToFileJSON(QJsonObject &jObject) const override;
    void itemFromFileJSON(const QJsonObject &jObject) override;

private:
    QString publisher;
    QString platform;
    QString genre;
};

#endif