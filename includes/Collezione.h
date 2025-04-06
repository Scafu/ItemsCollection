/*
    CLASSE COLLEZIONE
*/

#ifndef COLLEZIONE_H
#define COLLEZIONE_H

#include "AbstractItem.h"
#include <QList>
#include <QObject>

class Collezione : public QObject
{
    Q_OBJECT

public:
    // Enum per la scelta del filtro
    enum Filters
    {
        ALL,
        BOOKS,
        GAMES,
        MUSIC
    };

    // Pattern Singleton
    Collezione(const Collezione &) = delete;
    Collezione &operator=(const Collezione &) = delete;
    static Collezione &getCollezione()
    {
        static Collezione collection;
        return collection;
    }

    // Funzioni di servizio per gli item
    void addItem(QSharedPointer<AbstractItem> newItem);
    void removeItem(QSharedPointer<AbstractItem> newItem);
    void editItem(QSharedPointer<AbstractItem> newItem, QMap<QString, QVariant> &fieldToEdit);
    void searchTitle(const QString &title);
    QList<QSharedPointer<AbstractItem>> getItemList() const;
    Filters getActiveFilter() const;

    // Funzioni JSON
    void toFileJSON(const QString &filePath) const;
    void fromFileJSON(const QString &filePath);

public slots:
    void filterBooks();
    void filterGames();
    void filterMusic();
    void filterAll();
signals:
    void listFilteredDone();

private:
    Collezione() : activeFilter(ALL) {}
    QList<QSharedPointer<AbstractItem>> itemList;
    QList<QSharedPointer<AbstractItem>> itemFilteredList;

    Filters activeFilter;
};

#endif
