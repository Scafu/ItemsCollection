#include "MainWindow.h"
#include "Collezione.h"
#include "CustomToolBar.h"
#include "ItemCreationForm.h"
#include "VisitorCreateForm.h"
#include "VisitorReadForm.h"
#include "VisitorReadItem.h"
#include "ItemWidgetUI.h"
#include <QIcon>
#include <QApplication>
#include <QLabel>
#include <QSpacerItem>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Collezione di Oggetti");
    setWindowIcon(QIcon(":/assets/icon/database.png"));
    stack = new QStackedWidget(this);
    toolBar = new CustomToolBar(this);
    addToolBar(toolBar);

    QWidget *mainPage = new QWidget;
    homePage = nullptr;
    aboutPage = nullptr;
    verticalLayout = new QVBoxLayout(mainPage);
    verticalLayout->addWidget(toolBar);
    verticalLayout->addWidget(stack);
    verticalLayout->setAlignment(Qt::AlignVCenter);
    setCentralWidget(mainPage);
    showHome();
}

// AREA HOME INSIEME ALL'AREA ITEM E GESTIONE DEI SINGOLI ITEM

void MainWindow::showHome()
{
    if (!homePage) // se non è stata creata in precedenza
    {

        customFont.setPointSize(12);

        homePage = new QWidget(this);
        QVBoxLayout *homeLayout = new QVBoxLayout();
        homeLayout->setAlignment(Qt::AlignCenter);
        homePage->setLayout(homeLayout);

        // Pulsanti dei filtri
        buttonFilterLayout = new QHBoxLayout;
        buttonFilterLayout->setAlignment(Qt::AlignHCenter);
        gameButtonFilter = new QPushButton("Giochi");
        gameButtonFilter->setFont(customFont);
        gameButtonFilter->setFixedSize(200, 30);
        bookButtonFilter = new QPushButton("Libri");
        bookButtonFilter->setFont(customFont);
        bookButtonFilter->setFixedSize(200, 30);
        musicButtonFilter = new QPushButton("Musica");
        musicButtonFilter->setFont(customFont);
        musicButtonFilter->setFixedSize(200, 30);
        allButtonFilter = new QPushButton("Tutti");
        allButtonFilter->setFont(customFont);
        allButtonFilter->setFixedSize(200, 30);
        buttonFilterLayout->addWidget(gameButtonFilter);
        buttonFilterLayout->addWidget(bookButtonFilter);
        buttonFilterLayout->addWidget(musicButtonFilter);
        buttonFilterLayout->addWidget(allButtonFilter);

        // Barra di ricerca
        searchBarLayout = new QHBoxLayout;
        QLabel *label = new QLabel("Cerca un Titolo");
        label->setFont(customFont);
        searchBar = new QLineEdit(this);
        searchBar->setFont(customFont);
        searchBar->setFixedSize(900, 30);
        searchBarLayout->addWidget(label);
        searchBarLayout->addWidget(searchBar, 0, Qt::AlignCenter);
        searchBarLayout->addSpacerItem(new QSpacerItem(20, 0));
        searchBarLayout->setAlignment(Qt::AlignCenter);
        QVBoxLayout *layoutRicerca = new QVBoxLayout;
        layoutRicerca->addLayout(buttonFilterLayout);
        layoutRicerca->addSpacerItem(new QSpacerItem(0, 40));
        layoutRicerca->addLayout(searchBarLayout);

        // Scritta centrale e Area Items
        QHBoxLayout *collezioneAction = new QHBoxLayout;
        collezioneAction->setAlignment(Qt::AlignCenter);
        QLabel *collezioneLabel = new QLabel("La Tua Collezione");
        customFont.setPointSize(20);
        collezioneLabel->setFont(customFont);
        QPushButton *saveCollection = new QPushButton("Salva");
        QPushButton *restoreDefault = new QPushButton("Ripristina");
        collezioneAction->addWidget(collezioneLabel);
        collezioneAction->addWidget(saveCollection);
        collezioneAction->addWidget(restoreDefault);
        itemsArea = new QScrollArea;
        itemsArea->setWidgetResizable(true);
        itemsArea->setMinimumSize(500, 300);
        itemsArea->setMaximumSize(1000, 800);

        homeLayout->addLayout(layoutRicerca);
        homeLayout->addSpacerItem(new QSpacerItem(0, 50));
        homeLayout->addLayout(collezioneAction);
        homeLayout->addWidget(itemsArea, 1);
        homeLayout->addStretch();

        stack->addWidget(homePage);
        stack->setCurrentWidget(homePage);
        updateAreaItem();

        // Connessioni
        connect(bookButtonFilter, &QPushButton::clicked, &Collezione::getCollezione(), [this]()
                {
                    Collezione::getCollezione().filterBooks(); updateColorButtonFilters(); });
        connect(gameButtonFilter, &QPushButton::clicked, &Collezione::getCollezione(), [this]()
                {
                    Collezione::getCollezione().filterGames(); updateColorButtonFilters(); });
        connect(musicButtonFilter, &QPushButton::clicked, &Collezione::getCollezione(), [this]()
                {
                    Collezione::getCollezione().filterMusic(); updateColorButtonFilters(); });
        connect(allButtonFilter, &QPushButton::clicked, &Collezione::getCollezione(), [this]()
                {
                    Collezione::getCollezione().filterAll(); updateColorButtonFilters(); });
        connect(&Collezione::getCollezione(), &Collezione::listFilteredDone, this, &MainWindow::updateAreaItem);
        connect(searchBar, &QLineEdit::textChanged, this, [](const QString &text)
                { Collezione::getCollezione().searchTitle(text); });
        connect(saveCollection, &QPushButton::clicked, &Collezione::getCollezione(), &Collezione::saveCollection);
        connect(restoreDefault, &QPushButton::clicked, &Collezione::getCollezione(), &Collezione::restoreDefault);
        connect(&Collezione::getCollezione(), &Collezione::collectionLoaded, this, &MainWindow::updateAreaItem);
        updateColorButtonFilters();
    }
    else
    {
        updateAreaItem();
        stack->setCurrentWidget(homePage);
    }
}

void MainWindow::updateColorButtonFilters()
{
    allButtonFilter->setStyleSheet("");
    bookButtonFilter->setStyleSheet("");
    gameButtonFilter->setStyleSheet("");
    musicButtonFilter->setStyleSheet("");

    switch (Collezione::getCollezione().getActiveFilter())
    {
    case Collezione::ALL:
        allButtonFilter->setStyleSheet("background-color: rgb(0, 127, 247)");
        break;

    case Collezione::BOOKS:
        bookButtonFilter->setStyleSheet("background-color: rgb(0, 127, 247)");
        break;

    case Collezione::GAMES:
        gameButtonFilter->setStyleSheet("background-color: rgb(0, 127, 247)");
        break;

    case Collezione::MUSIC:
        musicButtonFilter->setStyleSheet("background-color: rgb(0, 127, 247)");
        break;

    default:
        break;
    }
}

void MainWindow::updateAreaItem()
{
    Collezione &collezione = Collezione::getCollezione();
    if (itemsArea->widget())
        delete itemsArea->widget();
    QWidget *containerItems = new QWidget;
    QGridLayout *containerLayout = new QGridLayout(containerItems);
    containerItems->setLayout(containerLayout);
    containerItems->setStyleSheet("border:2px solid rgba(255, 255, 255, 0.06); background-color: rgba(0, 0, 0, 0.07);");

    int rows = 0,
        columns = 0;
    for (auto it : collezione.getItemList())
    {
        ItemWidgetUI *singleItem = new ItemWidgetUI(it);
        containerLayout->addWidget(singleItem, rows, columns);
        columns++;
        connect(singleItem, &ItemWidgetUI::widgetClicked, this, &MainWindow::itemCliccato);
        if (columns >= 4)
        {
            columns = 0;
            rows++;
        }
    }
    itemsArea->setWidget(containerItems);
}

// FUNZIONE CHE VIENE CHIAMATA QUANDO SI SCHIACCIA SUL SINGOLO ITEM NELLA COLLEZIONE

void MainWindow::itemCliccato(QSharedPointer<AbstractItem> item)
{
    ItemPageUI *widgetPage = new ItemPageUI(item);

    stack->addWidget(widgetPage);
    stack->setCurrentWidget(widgetPage);

    // Connessioni
    connect(widgetPage, &ItemPageUI::backClicked, this, [&]()
            { stack->setCurrentWidget(homePage); });
    connect(widgetPage, &ItemPageUI::removeClicked, this, [this, item]()
            { 
            Collezione::getCollezione().removeItem(item);
            Collezione::getCollezione().toFileJSON(QApplication::applicationDirPath()+ "/../JSON/Items.json");
            showHome(); });
    connect(stack, &QStackedWidget::currentChanged, widgetPage, [widgetPage]
            { widgetPage->deleteLater(); });

    connect(widgetPage, &ItemPageUI::editClicked, this, [this, item]()
            {
                ItemPageEditUI *widgetPageEdit = new ItemPageEditUI(item);
                stack->addWidget(widgetPageEdit);
                stack->setCurrentWidget(widgetPageEdit);
                connect(widgetPageEdit, &ItemPageEditUI::confirmClicked, this, [&]()
                        { showHome(); }); 
                connect(widgetPageEdit, &ItemPageEditUI::backClicked, this, [&](){stack->setCurrentWidget(homePage);});
            connect(stack, &QStackedWidget::currentChanged, widgetPageEdit, [widgetPageEdit]{
                widgetPageEdit->deleteLater();
            }); });
}

// AREA DI CREAZIONE DEL SINGOLO ITEM E VISIONE DEI FORM IN BASE AL TIPO CHE SI VUOLE CREARE
void MainWindow::showCrea()
{
    QWidget *itemType = new QWidget(this);
    QVBoxLayout *typeSelectionLayout = new QVBoxLayout(itemType);
    QLabel *label = new QLabel("Scegli il tipo di ITEM che vuoi creare");
    QSize buttonSize(200, 50);
    customFont.setPointSize(14);
    label->setFont(customFont);
    label->setWordWrap(true);
    label->setAlignment(Qt::AlignCenter);

    // Pulsanti per sceglie il tipo di ITEM
    QPushButton *bookButton = new QPushButton("Book");
    QPushButton *gameButton = new QPushButton("Game");
    QPushButton *musicButton = new QPushButton("Music");
    bookButton->setFont(customFont);
    gameButton->setFont(customFont);
    musicButton->setFont(customFont);
    bookButton->setFixedSize(buttonSize);
    gameButton->setFixedSize(buttonSize);
    musicButton->setFixedSize(buttonSize);
    typeSelectionLayout->addWidget(label);
    typeSelectionLayout->addSpacerItem(new QSpacerItem(0, 20));
    typeSelectionLayout->addWidget(bookButton);
    typeSelectionLayout->addWidget(gameButton);
    typeSelectionLayout->addWidget(musicButton);
    typeSelectionLayout->setAlignment(Qt::AlignCenter);

    stack->addWidget(itemType);
    stack->setCurrentWidget(itemType);

    // Connessioni
    connect(stack, &QStackedWidget::currentChanged, itemType, [itemType]
            { itemType->deleteLater(); });
    connect(bookButton, &QPushButton::clicked, this, [&]()
            { showTypedForm("Book"); });
    connect(gameButton, &QPushButton::clicked, this, [&]()
            { showTypedForm("Game"); });
    connect(musicButton, &QPushButton::clicked, this, [&]()
            { showTypedForm("Music"); });
}

void MainWindow::showTypedForm(const QString &typeChosen)
{

    QWidget *container = new QWidget;

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->setAlignment(Qt::AlignCenter);

    // Creazione dell'item vuoto contenitore e del relativo FORM per il riempimento
    QSharedPointer<AbstractItem> itemCreato = ItemCreationForm::createDerivedItem(typeChosen);
    if (!itemCreato)
        return;

    VisitorCreateForm visitorCreate(itemCreato);
    itemCreato->accept(visitorCreate);

    QSharedPointer<ItemCreationForm> formWidget = visitorCreate.getFormItem();
    if (!formWidget)
        return;

    stack->addWidget(container);
    stack->setCurrentWidget(container);

    formWidget->clearFields();

    mainLayout->addWidget(formWidget.data());
    container->setLayout(mainLayout);
    bool success = false;
    connect(formWidget.data(), &ItemCreationForm::createItem, this, [&success]()
            { success = true; });
    connect(formWidget.data(), &ItemCreationForm::deleteCreation, this, [&]()
            { stack->setCurrentIndex(0); });

    QEventLoop creationCycle;
    connect(formWidget.data(), &ItemCreationForm::createItem, &creationCycle, &QEventLoop::quit);
    connect(formWidget.data(), &ItemCreationForm::deleteCreation, &creationCycle, &QEventLoop::quit);
    creationCycle.exec();

    if (!success)
        return;
    VisitorReadForm visitorRead(formWidget.data());
    formWidget->accept(visitorRead);
    itemCreato = visitorRead.getCompleteItem();
    if (!itemCreato)
        return;

    VisitorReadItem *visitorReadItem = new VisitorReadItem;
    itemCreato->accept(*visitorReadItem);

    Collezione::getCollezione().addItem(itemCreato);
    Collezione::getCollezione().toFileJSON(QApplication::applicationDirPath() + "/../JSON/Items.json");
    showHome();
}

// AREA ABOUT
void MainWindow::showAbout()
{
    if (!aboutPage)
    {
        aboutPage = new QWidget;
        QVBoxLayout *layoutAbout = new QVBoxLayout();
        QLabel *label = new QLabel("La collezioni di oggetti è un progetto valido per l'anno accademico 2024/2025 per il corso Programmazione ad Oggetti, \ned una vera e propria collezione di item sfruttando il framework QT in linguaggio C++\n\n Creato da Alessandro Mazzariol");
        QHBoxLayout *gitHubLayout = new QHBoxLayout();
        QLabel *gitHubIcon = new QLabel;
        QLabel *repository = new QLabel("<a href=\"https://github.com/Scafu/Progetto_PAO_2.0\">Repository Github</a>");
        repository->setTextInteractionFlags(Qt::TextBrowserInteraction);
        repository->setOpenExternalLinks(true);
        gitHubIcon->setFixedSize(64, 64);
        gitHubIcon->setScaledContents(true);
        QPixmap pixmap(":/assets/icon/github.png");
        gitHubIcon->setPixmap(pixmap);
        gitHubLayout->addWidget(gitHubIcon);
        gitHubLayout->addWidget(repository);
        gitHubLayout->setAlignment(Qt::AlignHCenter);
        customFont.setPointSize(16);
        label->setFont(customFont);
        label->setWordWrap(true);
        label->setAlignment(Qt::AlignCenter);
        layoutAbout->addWidget(label);
        layoutAbout->addSpacerItem(new QSpacerItem(0, 20));
        layoutAbout->addLayout(gitHubLayout);
        layoutAbout->setAlignment(Qt::AlignCenter);
        aboutPage->setLayout(layoutAbout);
        stack->addWidget(aboutPage);
        stack->setCurrentWidget(aboutPage);
    }
    else
    {
        stack->setCurrentWidget(aboutPage);
    }
}

QStackedWidget *MainWindow::getPila() const { return stack; }
