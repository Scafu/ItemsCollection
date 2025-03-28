#include "Book.h"

Book::Book(const QString newImage, const QString newTitle, const QString newDescription, const int newYear, const QString newAuthor, const QString newLanguage, const int newNumPages, const int newNumChapters) : AbstractItem(newImage, newTitle, newDescription, newYear), author(newAuthor), language(newLanguage), numPages(newNumPages), numChapters(newNumChapters) {}

// Funzioni getter testuali
QString Book::getAuthor() const { return author; };
QString Book::getLanguage() const { return language; };
QString Book::getType() const { return "Book"; }
int Book::getNumPages() const { return numPages; }
int Book::getNumChapters() const
{
    if (numPages <= 0)
        return 0;
    return numChapters;
}

// Funzioni setter relative
Book &Book::setAuthor(const QString &newAuthor)
{

    this->author = newAuthor;
    return *this;
}
Book &Book::setLanguage(const QString &newLanguage)
{
    this->language = newLanguage;
    return *this;
}
Book &Book::setNumPages(const int &newNumPages)
{
    this->numPages = newNumPages;
    return *this;
}
Book &Book::setNumChapters(const int &newNumChapters)
{
    this->numChapters = newNumChapters;
    return *this;
}

// Funzioni visitor
void Book::accept(AbstractVisitor &visitor) { visitor.visitBook(*this); }
void Book::accept(AbstractConstVisitor &constVisitor) const { constVisitor.visitBook(*this); }

// Funzioni JSON
void Book::itemToFileJSON(QJsonObject &jObject) const
{
    jObject["Tipo"] = getType();
    jObject["Titolo"] = getTitle();
    jObject["Anno"] = getYear();
    jObject["Immagine di Copertina"] = getCoverImage();
    jObject["Descrizione"] = getDescription();
    jObject["Autore"] = getAuthor();
    jObject["Lingua"] = getLanguage();
    jObject["Numero di Pagine"] = getNumPages();
    jObject["Numero di Capitoli"] = getNumChapters();
}
void Book::itemFromFileJSON(const QJsonObject &jObject)
{
    setTitle(jObject["Titolo"].toString());
    setYear(jObject["Anno"].toInt());
    setCoverImage(jObject["Immagine di Copertina"].toString());
    setDescription(jObject["Descrizione"].toString());
    setAuthor(jObject["Autore"].toString());
    setLanguage(jObject["Lingua"].toString());
    setNumPages(jObject["Numero di Pagine"].toInt());
    setNumChapters(jObject["Numero di Capitoli"].toInt());
}
