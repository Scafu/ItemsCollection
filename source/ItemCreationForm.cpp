#include "ItemCreationForm.h"
#include "Book.h"
#include "Game.h"
#include "Music.h"

#include <QMessageBox>
#include <QFileDialog>

ItemCreationForm::ItemCreationForm(QWidget *parent) : QWidget(parent)
{
    customFont.setPointSize(12);
    setFixedSize(1000, 800);
    setStyleSheet("QLineEdit{background-color: rgba(255, 255, 255, 0.3);} ");

    layoutParent = new QVBoxLayout(this);
    mainLayout = new QHBoxLayout;
    formLayout = new QFormLayout;

    // Righe di input
    titleInput = new QLineEdit(this);
    yearInput = new QLineEdit(this);
    coverImageInput = new QLineEdit(this);
    descriptionInput = new QLineEdit(this);

    // Pulsanti
    buttonLayout = new QHBoxLayout();
    buttonLayout->setAlignment(Qt::AlignVCenter);
    imageFolderButton = new QPushButton("Sfoglia", this);
    createButton = new QPushButton("Crea", this);
    deleteButton = new QPushButton("Annulla", this);
    deleteButton->setFont(customFont);
    deleteButton->setFixedSize(460, 50);
    createButton->setFont(customFont);
    createButton->setFixedSize(460, 50);
    buttonLayout->addWidget(createButton);
    buttonLayout->addWidget(deleteButton);

    // Creazione del form
    formLayout = new QFormLayout();
    formLayout->addRow("Titolo", titleInput);
    formLayout->addRow("Anno", yearInput);
    formLayout->addRow("Immagine di Copertina", coverImageInput);
    formLayout->addRow("", imageFolderButton);
    formLayout->addRow("Descrizione", descriptionInput);
    formLayout->setAlignment(Qt::AlignVCenter);

    mainLayout->addLayout(formLayout);
    mainLayout->addSpacerItem(new QSpacerItem(60, 10));

    layoutParent->addLayout(mainLayout);
    layoutParent->addSpacerItem(new QSpacerItem(0, 20));
    layoutParent->addLayout(buttonLayout);
    layoutParent->setAlignment(Qt::AlignCenter);
    setLayout(layoutParent);

    // Connessioni
    connect(imageFolderButton, &QPushButton::clicked, this, &ItemCreationForm::selectImage);
    connect(createButton, &QPushButton::clicked, this, &ItemCreationForm::createItemCheck);
    connect(deleteButton, &QPushButton::clicked, this, &ItemCreationForm::deleteCreation);
}

// Funzioni getter testuali
QString ItemCreationForm::getCoverImage() const { return coverImageInput->text(); }
QString ItemCreationForm::getTitle() const { return titleInput->text(); }
QString ItemCreationForm::getDescription() const { return descriptionInput->text(); }
int ItemCreationForm::getYear() const { return yearInput->text().toInt(); }

// Relative funzioni setter
void ItemCreationForm::setCoverImage(const QString &newImage) { coverImageInput->setText(newImage); }
void ItemCreationForm::setTitle(const QString &newTitle) { titleInput->setText(newTitle); }
void ItemCreationForm::setDescription(const QString &newDescription) { descriptionInput->setText(newDescription); }
void ItemCreationForm::setYear(const int &newYear) { yearInput->setText(QString::number(newYear)); }

// Funzioni di servizio

QString ItemCreationForm::selectImage()
{
    QString image = QFileDialog::getOpenFileName(this, "Seleziona l'immagine di copertina", "", "Immagini(*.png, *.jpeg, *.jpg)");
    if (!image.isEmpty())
    {
        coverImageInput->setText(image);
    }
    return image;
}
QSharedPointer<AbstractItem> ItemCreationForm::createDerivedItem(const QString &typeChosen)
{
    if (typeChosen == "Book")
        return QSharedPointer<Book>::create();
    else if (typeChosen == "Game")
        return QSharedPointer<Game>::create();
    else if (typeChosen == "Music")
        return QSharedPointer<Music>::create();
    else
        return nullptr;
}

void ItemCreationForm::createItemCheck()
{
    if (titleInput->text().isEmpty())
    {
        QMessageBox::warning(this, "Errore", "Serve almeno il titolo per poter creare l'item");
        return;
    }
    if (yearInput->text().toInt() <= 0)
    {
        QMessageBox::warning(this, "Errore", "L'anno inserito deve essere un numero maggiore di 0");
        return;
    }
    else
        emit createItem();
}