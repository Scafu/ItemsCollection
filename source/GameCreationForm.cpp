#include "GameCreationForm.h"

GameCreationForm::GameCreationForm(QWidget *parent) : ItemCreationForm(parent)
{
    publisherInput = new QLineEdit();
    platformInput = new QLineEdit();
    genreInput = new QLineEdit();

    formLayout->addRow("Publisher", publisherInput);
    formLayout->addRow("Piattaforma", platformInput);
    formLayout->addRow("Genere", genreInput);
}

QString GameCreationForm::getPublisher() const { return publisherInput->text(); }
QString GameCreationForm::getPlatform() const { return platformInput->text(); }
QString GameCreationForm::getGenre() const { return genreInput->text(); }
QMap<QString, QVariant> GameCreationForm::getNotDefaultFields() const
{
    QMap<QString, QVariant> fieldToRead;
    fieldToRead["Publisher"] = getPublisher();
    fieldToRead["Piattaforma"] = getPlatform();
    fieldToRead["Genere"] = getGenre();
    return fieldToRead;
}

void GameCreationForm::setPublisher(const QString &newPublisher) { publisherInput->setText(newPublisher); }
void GameCreationForm::setPlatform(const QString &newPlatform) { publisherInput->setText(newPlatform); }
void GameCreationForm::setGenre(const QString &newGenre) { publisherInput->setText(newGenre); }

void GameCreationForm::setNotDefaultFields(const QMap<QString, QVariant> &fieldsToAdd)
{
    if (fieldsToAdd.contains("Publisher"))
        setPublisher(fieldsToAdd["Publisher"].toString());
    if (fieldsToAdd.contains("Platform"))
        setPlatform(fieldsToAdd["Piattaforma"].toString());
    if (fieldsToAdd.contains("Genere"))
        setGenre(fieldsToAdd["Genere"].toString());
}

void GameCreationForm::clearFields()
{
    titleInput->clear();
    yearInput->clear();
    coverImageInput->clear();
    publisherInput->clear();
    platformInput->clear();
    genreInput->clear();
}

void GameCreationForm::accept(FormVisitor &visitor)
{
    visitor.visitGameForm(*this);
}

void GameCreationForm::accept(FormConstVisitor &constVisitor) const
{
    constVisitor.visitGameForm(*this);
}