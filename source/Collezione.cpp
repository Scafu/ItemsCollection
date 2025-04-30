#include <QApplication>
#include <QFile>
#include <QByteArray>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileDialog>
#include <QMessageBox>
#include "Collezione.h"
#include "Book.h"
#include "Game.h"
#include "Music.h"

void Collezione::addItem(QSharedPointer<AbstractItem> newItem)
{
    itemList.append(newItem);
}

void Collezione::editItem(QSharedPointer<AbstractItem> newItem, QMap<QString, QVariant> &fieldToEdit)
{
    for (auto &it : itemList)
    {
        auto editedBook = qSharedPointerDynamicCast<Book>(it);
        if (editedBook && editedBook->getTitle() == newItem->getTitle())
        {
            editedBook->setTitle(fieldToEdit.value("Titolo", QVariant(editedBook->getTitle())).toString());
            editedBook->setYear(fieldToEdit.value("Anno", QVariant(editedBook->getYear())).toInt());
            editedBook->setCoverImage(fieldToEdit.value("Immagine di Copertina", QVariant(editedBook->getCoverImage())).toString());
            editedBook->setDescription(fieldToEdit.value("Descrizione", QVariant(editedBook->getDescription())).toString());
            editedBook->setAuthor(fieldToEdit.value("Autore", QVariant(editedBook->getAuthor())).toString());
            editedBook->setLanguage(fieldToEdit.value("Lingua", QVariant(editedBook->getLanguage())).toString());
            editedBook->setNumPages(fieldToEdit.value("Numero di Pagine", QVariant(editedBook->getNumPages())).toInt());
            editedBook->setNumChapters(fieldToEdit.value("Numero di Capitoli", QVariant(editedBook->getNumChapters())).toInt());
        }
        auto editedGame = qSharedPointerDynamicCast<Game>(it);
        if (editedGame && editedGame->getTitle() == newItem->getTitle())
        {
            editedGame->setTitle(fieldToEdit.value("Titolo", QVariant(editedGame->getTitle())).toString());
            editedGame->setYear(fieldToEdit.value("Anno", QVariant(editedGame->getYear())).toInt());
            editedGame->setCoverImage(fieldToEdit.value("Immagine di Copertina", QVariant(editedGame->getCoverImage())).toString());
            editedGame->setDescription(fieldToEdit.value("Descrizione", QVariant(editedGame->getDescription())).toString());
            editedGame->setPublisher(fieldToEdit.value("Publisher", QVariant(editedGame->getPublisher())).toString());
            editedGame->setPlatform(fieldToEdit.value("Piattaforma", QVariant(editedGame->getPlatform())).toString());
            editedGame->setGenre(fieldToEdit.value("Genere", QVariant(editedGame->getGenre())).toString());
        }
        auto editedMusic = qSharedPointerDynamicCast<Music>(it);
        if (editedMusic && editedMusic->getTitle() == newItem->getTitle())
        {
            editedMusic->setTitle(fieldToEdit.value("Titolo", QVariant(editedMusic->getTitle())).toString());
            editedMusic->setYear(fieldToEdit.value("Anno", QVariant(editedMusic->getYear())).toInt());
            editedMusic->setCoverImage(fieldToEdit.value("Immagine di Copertina", QVariant(editedMusic->getCoverImage())).toString());
            editedMusic->setDescription(fieldToEdit.value("Descrizione", QVariant(editedMusic->getDescription())).toString());
            editedMusic->setArtist(fieldToEdit.value("Artista", QVariant(editedMusic->getArtist())).toString());
            editedMusic->setBand(fieldToEdit.value("Band", QVariant(editedMusic->getBand())).toString());
            editedMusic->setAlbum(fieldToEdit.value("Album", QVariant(editedMusic->getAlbum())).toString());
        }
    }
    toFileJSON(QApplication::applicationDirPath() + "/../JSON/Items.json");
}

void Collezione::removeItem(QSharedPointer<AbstractItem> item)
{
    for (auto it = itemList.begin(); it != itemList.end();)
    {
        if (it->data()->getTitle() == item->getTitle() && it->data()->getYear() == item->getYear())
        {
            it = itemList.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Collezione::searchTitle(const QString &title)
{
    itemFilteredList.clear();
    for (const auto &it : itemList)
    {
        if (it->getTitle().startsWith(title, Qt::CaseInsensitive))
            itemFilteredList.append(it);
    }
    emit listFilteredDone();
}

QList<QSharedPointer<AbstractItem>> Collezione::getItemList() const
{
    if (activeFilter == ALL && itemFilteredList.isEmpty())
        return itemList;
    return itemFilteredList;
}
Collezione::Filters Collezione::getActiveFilter() const
{
    return activeFilter;
}

void Collezione::toFileJSON(const QString &filePath) const
{
    QJsonArray arrayJSON;
    for (const auto &it : itemList)
    {
        QJsonObject item;
        it->itemToFileJSON(item);
        arrayJSON.append(item);
    }
    QJsonDocument document(arrayJSON);
    QFile fileToOpen(filePath);
    if (!fileToOpen.open(QIODevice::WriteOnly))
    {
        return;
    }
    fileToOpen.write(document.toJson());
    fileToOpen.close();
    return;
}

void Collezione::fromFileJSON(const QString &filePath)
{
    QFile fileToOpen(filePath);
    if (!fileToOpen.open(QIODevice::ReadOnly))
        return;
    QByteArray data = fileToOpen.readAll();
    fileToOpen.close();

    QJsonDocument document = QJsonDocument::fromJson(data);
    if (!document.isArray() || document.isNull())
    {
        return;
    }
    QJsonArray jsonArray = document.array();
    itemList.clear();

    for (const auto &it : jsonArray)
    {
        QJsonObject jObject = it.toObject();
        QString type = jObject["Tipo"].toString();
        QSharedPointer<AbstractItem> itemToCreate;
        if (type == "Book")
        {
            itemToCreate = QSharedPointer<AbstractItem>(new Book("", "", "", 0, "", "", 0, 0));
        }
        else if (type == "Game")
        {

            itemToCreate = QSharedPointer<AbstractItem>(new Game("", "", "", 0, "", "", ""));
        }
        else
        {
            itemToCreate = QSharedPointer<AbstractItem>(new Music("", "", "", 0, "", "", ""));
        }

        if (itemToCreate)
        {
            itemToCreate->itemFromFileJSON(jObject);
            itemList.append(itemToCreate);
        }
    }
    return;
}

void Collezione::filterBooks()
{
    itemFilteredList.clear();
    for (const auto &it : itemList)
    {
        if (qSharedPointerDynamicCast<Book>(it))
            itemFilteredList.append(it);
    }
    activeFilter = BOOKS;
    emit listFilteredDone();
}

void Collezione::filterGames()
{
    itemFilteredList.clear();
    for (const auto &it : itemList)
    {
        if (qSharedPointerDynamicCast<Game>(it))
            itemFilteredList.append(it);
    }
    activeFilter = GAMES;
    emit listFilteredDone();
}

void Collezione::filterMusic()
{
    itemFilteredList.clear();
    for (const auto &it : itemList)
    {
        if (qSharedPointerDynamicCast<Music>(it))
            itemFilteredList.append(it);
    }
    activeFilter = MUSIC;
    emit listFilteredDone();
}

void Collezione::filterAll()
{
    itemFilteredList.clear();
    for (const auto &it : itemList)
    {
        itemFilteredList.append(it);
    }
    activeFilter = ALL;
    emit listFilteredDone();
}

void Collezione::collectionFromFile()
{
    collectionFileLoaded = QFileDialog::getOpenFileName(nullptr, "Seleziona la collezione che vuoi mostrare", "", "Items (*.json)");
    if (collectionFileLoaded.isEmpty())
        return;
    fromFileJSON(collectionFileLoaded);
    emit collectionLoaded();
}

void Collezione::saveCollection()
{
    QString fileDaSostituire = QApplication::applicationDirPath() + "/../JSON/Items.json";
    QString destinationPath = QApplication::applicationDirPath() + "/../JSON/";
    if (collectionFileLoaded.isEmpty())
        return;

    if (QFile::exists(fileDaSostituire))
        QFile::remove(fileDaSostituire);

    else
        QFile::copy(collectionFileLoaded, destinationPath);

    if (!QFile::copy(collectionFileLoaded, fileDaSostituire))
        QMessageBox::warning(nullptr, "Errore", "Impossibile sostituire il file scelto");
}

void Collezione::restoreDefault()
{
    auto risposta = QMessageBox::question(nullptr, "Ripristino", "Sei sicuro di voler annullare ripristinare la collezione di Default?", QMessageBox::Yes | QMessageBox::No);
    if (risposta == QMessageBox::No)
        return;

    collectionFileLoaded = QApplication::applicationDirPath() + "/../JSON/default/Items.json";
    QString fileDaSostituire = QApplication::applicationDirPath() + "/../JSON/Items.json";
    QString destinationPath = QApplication::applicationDirPath() + "/../JSON/";
    if (collectionFileLoaded.isEmpty())
        return;

    if (QFile::exists(fileDaSostituire))
        QFile::remove(fileDaSostituire);

    else
        QFile::copy(collectionFileLoaded, destinationPath);

    if (!QFile::copy(collectionFileLoaded, fileDaSostituire))
        QMessageBox::warning(nullptr, "Errore", "Impossibile sostituire il file scelto");

    fromFileJSON(collectionFileLoaded);
    emit collectionLoaded();
}