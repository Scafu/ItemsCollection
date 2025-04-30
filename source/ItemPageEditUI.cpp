#include "ItemPageEditUI.h"
#include "Game.h"
#include "Book.h"
#include "Music.h"
#include "Collezione.h"
#include <QMessageBox>
#include <QApplication>
#include <QFileDialog>
#include <QLineEdit>

ItemPageEditUI::ItemPageEditUI(QSharedPointer<AbstractItem> itemChosen, QWidget *parent) : QWidget(parent), item(itemChosen)
{
    QDir dir(QApplication::applicationDirPath());
    dir.cdUp();

    customFont.setPointSize(13);

    customSizePolicy = new QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    pageLayout = new QVBoxLayout(this);
    pageLayout->setAlignment(Qt::AlignCenter);

    containerWidget = new QWidget;
    containerWidget->setStyleSheet("border: 2px solid rgba(255, 255, 255, 0.06); background-color: rgba(255,255,255,0.06);");
    containerWidget->setFixedSize(1000, 800);
    pageLayout->addWidget(containerWidget, 0, Qt::AlignCenter);
    containerLayout = new QVBoxLayout;
    containerLayout->setAlignment(Qt::AlignVCenter);
    containerWidget->setLayout(containerLayout);

    layoutAusiliare = new QHBoxLayout;
    containerLayout->addLayout(layoutAusiliare);
    QLabel *containerCover = new QLabel;
    containerCover->setFixedSize(250, 400);
    QPixmap coverItem(dir.filePath(item->getCoverImage()));
    containerCover->setPixmap(coverItem);
    containerCover->setScaledContents(true);

    detailsLayout = showPage(item);

    layoutAusiliare->addSpacerItem(new QSpacerItem(100, 0));
    layoutAusiliare->addWidget(containerCover);
    layoutAusiliare->addSpacerItem(new QSpacerItem(80, 0));
    layoutAusiliare->addLayout(detailsLayout);
}

QLayout *ItemPageEditUI::showPage(QSharedPointer<AbstractItem> item)
{

    detailsLayoutEdit = new QFormLayout;
    detailsLayoutEdit->setAlignment(Qt::AlignCenter);

    QLabel *titleLabel = new QLabel("Titolo");
    titleLabel->setFont(customFont);
    title = new QLineEdit;
    title->setText(item->getTitle());
    title->setFont(customFont);
    title->setStyleSheet("background: transparent;");
    fieldsEdited["Titolo"] = title->text();

    QPushButton *imageFolderButton = new QPushButton("Sfoglia", this);
    QLabel *yearLabel = new QLabel("Anno di Uscita");
    yearLabel->setFont(customFont);
    year = new QLineEdit;
    year->setText(QString::number(item->getYear()));
    year->setFont(customFont);
    year->setStyleSheet("background: transparent;");
    fieldsEdited["Anno"] = year->text();

    QLabel *coverLabel = new QLabel("Immagine di Copertina");
    coverLabel->setFont(customFont);
    cover = new QLineEdit;
    cover->setText(item->getCoverImage());
    cover->setFont(customFont);
    cover->setStyleSheet("background: transparent;");
    fieldsEdited["Immagine di Copertina"] = cover->text();

    QLabel *descriptionLabel = new QLabel("Descrizione");
    descriptionLabel->setFont(customFont);
    description = new QLineEdit;
    description->setText(item->getDescription());
    description->setFont(customFont);
    description->setStyleSheet("background: transparent;");
    description->setCursorPosition(0);
    fieldsEdited["Descrizione"] = description->text();

    if (auto itemCast = qSharedPointerDynamicCast<Book>(item))
    {
        QLabel *authorLabel = new QLabel("Autore");
        authorLabel->setFont(customFont);
        author = new QLineEdit;
        author->setText(itemCast.data()->getAuthor());
        author->setSizePolicy(*customSizePolicy);
        author->setFont(customFont);
        author->setStyleSheet("background: transparent");
        fieldsEdited["Autore"] = author->text();

        QLabel *numPagesLabel = new QLabel("Numero di Pagine");
        numPagesLabel->setFont(customFont);
        numPages = new QLineEdit;
        numPages->setText(QString::number(itemCast.data()->getNumPages()));
        numPages->setSizePolicy(*customSizePolicy);
        numPages->setFont(customFont);
        numPages->setStyleSheet("background: transparent");
        fieldsEdited["Numero di Pagine"] = numPages->text();

        QLabel *numChaptersLabel = new QLabel("Numero di Capitoli");
        numChaptersLabel->setFont(customFont);
        numChapters = new QLineEdit;
        numChapters->setText(QString::number(itemCast.data()->getNumChapters()));
        numChapters->setSizePolicy(*customSizePolicy);
        numChapters->setFont(customFont);
        numChapters->setStyleSheet("background: transparent");
        fieldsEdited["Numero di Capitoli"] = numChapters->text();

        QLabel *languageLabel = new QLabel("Lingua");
        languageLabel->setFont(customFont);
        language = new QLineEdit;
        language->setText(itemCast.data()->getLanguage());
        language->setSizePolicy(*customSizePolicy);
        language->setFont(customFont);
        language->setStyleSheet("background: transparent");
        fieldsEdited["Lingua"] = language->text();

        detailsLayoutEdit->addRow(titleLabel, title);
        detailsLayoutEdit->addRow(yearLabel, year);
        detailsLayoutEdit->addRow(coverLabel, cover);
        detailsLayoutEdit->addRow("", imageFolderButton);
        detailsLayoutEdit->addRow(authorLabel, author);
        detailsLayoutEdit->addRow(numPagesLabel, numPages);
        detailsLayoutEdit->addRow(numChaptersLabel, numChapters);
        detailsLayoutEdit->addRow(languageLabel, language);
        detailsLayoutEdit->addRow(descriptionLabel, description);
    }
    else if (auto itemCast = qSharedPointerDynamicCast<Game>(item))
    {

        QLabel *publisherLabel = new QLabel("Publisher");
        publisherLabel->setFont(customFont);
        publisher = new QLineEdit;
        publisher->setText(itemCast.data()->getPublisher());
        publisher->setSizePolicy(*customSizePolicy);
        publisher->setFont(customFont);
        publisher->setStyleSheet("background: transparent");
        fieldsEdited["Publisher"] = publisher->text();

        QLabel *platformLabel = new QLabel("Piattaforma");
        platformLabel->setFont(customFont);
        platform = new QLineEdit;
        platform->setText(itemCast.data()->getPlatform());
        platform->setSizePolicy(*customSizePolicy);
        platform->setFont(customFont);
        platform->setStyleSheet("background: transparent");
        fieldsEdited["Piattaforma"] = platform->text();

        QLabel *genreLabel = new QLabel("Genere");
        genreLabel->setFont(customFont);
        genre = new QLineEdit;
        genre->setText(itemCast.data()->getGenre());
        genre->setSizePolicy(*customSizePolicy);
        genre->setFont(customFont);
        genre->setStyleSheet("background: transparent");
        fieldsEdited["Genere"] = genre->text();

        detailsLayoutEdit->addRow(titleLabel, title);
        detailsLayoutEdit->addRow(yearLabel, year);
        detailsLayoutEdit->addRow(coverLabel, cover);
        detailsLayoutEdit->addRow("", imageFolderButton);
        detailsLayoutEdit->addRow(publisherLabel, publisher);
        detailsLayoutEdit->addRow(platformLabel, platform);
        detailsLayoutEdit->addRow(genreLabel, genre);
        detailsLayoutEdit->addRow(descriptionLabel, description);
    }
    else if (auto itemCast = qSharedPointerDynamicCast<Music>(item))
    {
        QLabel *artistLabel = new QLabel("Artista");
        artistLabel->setFont(customFont);
        artist = new QLineEdit;
        artist->setText(itemCast.data()->getArtist());
        artist->setSizePolicy(*customSizePolicy);
        artist->setFont(customFont);
        artist->setStyleSheet("background: transparent");
        fieldsEdited["Artista"] = artist->text();

        QLabel *bandLabel = new QLabel("Band");
        bandLabel->setFont(customFont);
        band = new QLineEdit;
        band->setText(itemCast.data()->getBand());
        band->setSizePolicy(*customSizePolicy);
        band->setFont(customFont);
        band->setStyleSheet("background: transparent");
        fieldsEdited["Band"] = band->text();

        QLabel *albumLabel = new QLabel("Album");
        albumLabel->setFont(customFont);
        album = new QLineEdit;
        album->setText(itemCast.data()->getAlbum());
        album->setSizePolicy(*customSizePolicy);
        album->setFont(customFont);
        album->setStyleSheet("background: transparent");
        fieldsEdited["Album"] = album->text();

        detailsLayoutEdit->addRow(titleLabel, title);
        detailsLayoutEdit->addRow(yearLabel, year);
        detailsLayoutEdit->addRow(coverLabel, cover);
        detailsLayoutEdit->addRow("", imageFolderButton);
        detailsLayoutEdit->addRow(artistLabel, artist);
        detailsLayoutEdit->addRow(bandLabel, band);
        detailsLayoutEdit->addRow(albumLabel, album);
        detailsLayoutEdit->addRow(descriptionLabel, description);
    }
    buttonsLayout = new QHBoxLayout;
    confirmButton = new QPushButton("Conferma");
    confirmButton->setFixedSize(200, 40);
    backButton = new QPushButton("Indietro");
    backButton->setFixedSize(200, 40);
    buttonsLayout->addWidget(confirmButton);
    buttonsLayout->addWidget(backButton);
    buttonsLayout->setAlignment(Qt::AlignHCenter);

    pageLayout->addLayout(buttonsLayout);

    // Connessioni
    connect(imageFolderButton, &QPushButton::clicked, this, &ItemPageEditUI::selectImage);
    connect(confirmButton, &QPushButton::clicked, this, [this, item]()
            { updateFields();
                Collezione::getCollezione().editItem(item, this->fieldsEdited); 
            emit confirmClicked(); });
    connect(backButton, &QPushButton::clicked, this, [&]
            {
        auto risposta = QMessageBox::question(this, "Conferma", "Sei sicuro di voler annullare la modifica?", QMessageBox::Yes | QMessageBox::No);
        if (risposta == QMessageBox::Yes)
            emit backClicked(); });

    detailsLayoutEdit->setSpacing(20);
    return detailsLayoutEdit;
}

QString ItemPageEditUI::selectImage()
{
    QString image = QFileDialog::getOpenFileName(this, "Seleziona l'immagine di copertina", "", "Immagini (*.png, *.jpeg, *.jpg)");
    if (!image.isEmpty())
    {
        cover->setText(image);
    }
    return image;
}

void ItemPageEditUI::updateFields()
{
    fieldsEdited["Titolo"] = title->text();
    fieldsEdited["Anno"] = year->text().toInt();
    fieldsEdited["Immagine di Copertina"] = cover->text();
    fieldsEdited["Descrizione"] = description->text();

    if (auto ItemCast = qSharedPointerDynamicCast<Book>(item))
    {
        fieldsEdited["Autore"] = author->text();
        fieldsEdited["Numero di Pagine"] = numPages->text().toInt();
        fieldsEdited["Numero di Capitoli"] = numChapters->text().toInt();
        fieldsEdited["Lingua"] = language->text();
    }
    else if (auto itemCast = qSharedPointerDynamicCast<Game>(item))
    {
        fieldsEdited["Publisher"] = publisher->text();
        fieldsEdited["Piattaforma"] = platform->text();
        fieldsEdited["Genere"] = genre->text();
    }
    else
    {
        fieldsEdited["Artista"] = artist->text();
        fieldsEdited["Band"] = band->text();
        fieldsEdited["Album"] = album->text();
    }
}
