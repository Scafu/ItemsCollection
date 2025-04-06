#include "ItemPageUI.h"
#include <QFileDialog>
#include <QApplication>
#include "Game.h"
#include "Book.h"
#include "Music.h"
#include "Collezione.h"
#include <QTextBrowser>
#include <QMessageBox>
#include <QLineEdit>

ItemPageUI::ItemPageUI(QSharedPointer<AbstractItem> itemChosen, QWidget *parent) : QWidget(parent), item(itemChosen)
{
    QDir dir(QApplication::applicationDirPath());
    dir.cdUp();

    customFont.setPointSize(13);

    customSizePolicy = new QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
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

QLayout *ItemPageUI::showPage(QSharedPointer<AbstractItem> item)
{
    customFont.setPointSize(12);
    detailsLayoutNoEdit = new QVBoxLayout;
    detailsLayoutNoEdit->setAlignment(Qt::AlignCenter);
    detailsLayoutNoEdit->setSpacing(20);

    itemTitle = new QLabel("Titolo: <b>" + item->getTitle() + "</b>");
    itemTitle->setSizePolicy(*customSizePolicy);
    itemTitle->setFont(customFont);
    itemTitle->setMaximumWidth(500);

    itemYear = new QLabel("Anno di Uscita: <b>" + QString::number(item->getYear()) + "</b>");
    itemYear->setSizePolicy(*customSizePolicy);
    itemYear->setFont(customFont);
    itemYear->setMaximumWidth(500);

    QTextBrowser *itemDescription = new QTextBrowser;
    itemDescription->setText("Descrizione:<br> <b>" + item->getDescription() + "</b>");
    itemDescription->setWordWrapMode(QTextOption::WrapAnywhere);
    itemDescription->setSizePolicy(*customSizePolicy);
    itemDescription->setMaximumHeight(150);
    itemDescription->setFont(customFont);
    itemDescription->setMaximumWidth(500);

    detailsLayoutNoEdit->addWidget(itemTitle);
    detailsLayoutNoEdit->addWidget(itemYear);

    if (auto itemCast = qSharedPointerDynamicCast<Book>(item))
    {
        itemAuthor = new QLabel("Autore: <b>" + itemCast->getAuthor() + "</b>");
        itemAuthor->setSizePolicy(*customSizePolicy);
        itemAuthor->setFont(customFont);
        itemAuthor->setMaximumWidth(500);
        itemNumPages = new QLabel("Numero di Pagine: <b>" + QString::number(itemCast->getNumPages()) + "</b>");
        itemNumPages->setSizePolicy(*customSizePolicy);
        itemNumPages->setFont(customFont);
        itemNumPages->setMaximumWidth(500);
        itemNumChapters = new QLabel("Numero di Capitoli: <b>" + QString::number(itemCast->getNumChapters()) + "</b>");
        itemNumChapters->setSizePolicy(*customSizePolicy);
        itemNumChapters->setFont(customFont);
        itemNumChapters->setMaximumWidth(500);
        itemLanguage = new QLabel("Lingua: <b>" + itemCast->getLanguage() + "</b>");
        itemLanguage->setSizePolicy(*customSizePolicy);
        itemLanguage->setFont(customFont);
        itemLanguage->setMaximumWidth(500);

        detailsLayoutNoEdit->addWidget(itemAuthor);
        detailsLayoutNoEdit->addWidget(itemNumPages);
        detailsLayoutNoEdit->addWidget(itemNumChapters);
        detailsLayoutNoEdit->addWidget(itemLanguage);
    }
    else if (auto itemCast = qSharedPointerDynamicCast<Game>(item))
    {

        itemPublisher = new QLabel("Publisher: <b>" + itemCast->getPublisher() + "</b>");
        itemPublisher->setSizePolicy(*customSizePolicy);
        itemPublisher->setFont(customFont);
        itemPublisher->setMaximumWidth(500);
        itemPlatform = new QLabel("Piattaforma: <b>" + itemCast->getPlatform() + "</b>");
        itemPlatform->setSizePolicy(*customSizePolicy);
        itemPlatform->setFont(customFont);
        itemPlatform->setMaximumWidth(500);
        itemGenre = new QLabel("Genere: <b>" + itemCast->getGenre() + "</b>");
        itemGenre->setSizePolicy(*customSizePolicy);
        itemGenre->setFont(customFont);
        itemGenre->setMaximumWidth(500);

        detailsLayoutNoEdit->addWidget(itemPublisher);
        detailsLayoutNoEdit->addWidget(itemPlatform);
        detailsLayoutNoEdit->addWidget(itemGenre);
    }
    else if (auto itemCast = qSharedPointerDynamicCast<Music>(item))
    {
        itemArtist = new QLabel("Artista: <b>" + itemCast->getArtist() + "</b>");
        itemArtist->setSizePolicy(*customSizePolicy);
        itemArtist->setFont(customFont);
        itemArtist->setMaximumWidth(500);
        itemBand = new QLabel("Band: <b>" + itemCast->getBand() + "</b>");
        itemBand->setSizePolicy(*customSizePolicy);
        itemBand->setFont(customFont);
        itemBand->setMaximumWidth(500);
        itemAlbum = new QLabel("Album: <b>" + itemCast->getAlbum() + "</b>");
        itemAlbum->setSizePolicy(*customSizePolicy);
        itemAlbum->setFont(customFont);
        itemAlbum->setMaximumWidth(500);

        detailsLayoutNoEdit->addWidget(itemArtist);
        detailsLayoutNoEdit->addWidget(itemBand);
        detailsLayoutNoEdit->addWidget(itemAlbum);
    }
    buttonsLayout = new QHBoxLayout;
    editButton = new QPushButton("Modifica");
    editButton->setFixedSize(200, 40);
    deleteButton = new QPushButton("Elimina");
    deleteButton->setFixedSize(200, 40);
    backButton = new QPushButton("Indietro");
    backButton->setFixedSize(200, 40);
    buttonsLayout->addWidget(editButton);
    buttonsLayout->addWidget(deleteButton);
    buttonsLayout->addWidget(backButton);
    buttonsLayout->setAlignment(Qt::AlignHCenter);

    detailsLayoutNoEdit->addWidget(itemDescription);
    pageLayout->addLayout(buttonsLayout);

    // Connessioni
    connect(editButton, &QPushButton::clicked, this, &ItemPageUI::editClicked);
    connect(deleteButton, &QPushButton::clicked, this, &ItemPageUI::removeClicked);
    connect(backButton, &QPushButton::clicked, this, &ItemPageUI::backClicked);
    return detailsLayoutNoEdit;
}
