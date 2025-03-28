/*
    CLASSE CONCRETA BOOK
*/

#ifndef BOOK_H
#define BOOK_H

#include "AbstractItem.h"

class Book : public AbstractItem
{

public:
    Book(const QString newImage = "Non disponibile", const QString newTitle = "Non disponibile", const QString newDescription = "Non disponibile", const int newYear = 0, const QString newAuthor = "Non disponibile", const QString newLanguage = "Non disponibile", const int newNumPages = 0, const int newNumChapters = 0);

    // Funzioni getter testuali
    QString getAuthor() const;
    QString getLanguage() const;
    QString getType() const;
    int getNumPages() const;
    int getNumChapters() const;

    // Funzioni setter relative
    Book &setAuthor(const QString &newAuthor);
    Book &setLanguage(const QString &newLanguage);
    Book &setNumPages(const int &newNumPages);
    Book &setNumChapters(const int &newNumChapters);

    // Funzioni visitor
    void accept(AbstractVisitor &visitor) override;
    void accept(AbstractConstVisitor &constVisitor) const override;

    // Funzioni JSON
    void itemToFileJSON(QJsonObject &jObject) const override;
    void itemFromFileJSON(const QJsonObject &jObject) override;

private:
    QString author;
    QString language;
    int numPages;
    int numChapters;
};

#endif
