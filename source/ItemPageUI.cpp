#include "ItemPageUI.h"
#include "Game.h"
#include "Book.h"
#include "Music.h"
#include "Collezione.h"
#include <QTextBrowser>
#include <QLineEdit>

ItemPageUI::ItemPageUI(QSharedPointer<AbstractItem> itemChosen, QWidget *parent) : QWidget(parent), item(itemChosen)
{
    customFont.setPointSize(13);

    customSizePolicy = new QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}