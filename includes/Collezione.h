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
    void removeItem(QSharedPointer<AbstractItem> itemToDelete);
    void editItem(QSharedPointer<AbstractItem> newItem, QMap<QString, QVariant> &fieldToEdit);
    void searchTitle(const QString &title);
    QList<QSharedPointer<AbstractItem>> getItemList() const;
    Filters getActiveFilter() const;

    // Funzioni JSON
    void toFileJSON(const QString &filePath) const; // salva l'itemList nella struttura JSON
    void fromFileJSON(const QString &filePath);     // recupera la struttura del JSON e la salva nell'itemList

public slots:
    void filterBooks();
    void filterGames();
    void filterMusic();
    void filterAll();
    void collectionFromFile(); // permette il caricamento del file Items.json dall'utente
    void saveCollection();     // salva il file Items.json inserito dall'utente
    void restoreDefault();     // ripristina la versione di Default del programma

signals:
    void collectionLoaded();
    void listFilteredDone();

private:
    Collezione() : activeFilter(ALL) {}
    QList<QSharedPointer<AbstractItem>> itemList;
    QList<QSharedPointer<AbstractItem>> itemFilteredList;
    QString collectionFileLoaded;
    Filters activeFilter;
};

#endif
