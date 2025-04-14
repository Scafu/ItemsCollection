#include "ItemWidgetUI.h"
#include <QApplication>
#include <QDir>

ItemWidgetUI::ItemWidgetUI(QSharedPointer<AbstractItem> item, QWidget *parent) : QWidget(parent), item(item)
{
    setFixedSize(200, 300);
    QFont customFont;
    secondLabel = new QLabel(this);
    secondLabel->setAlignment(Qt::AlignCenter);
    if (auto itemCast = qSharedPointerDynamicCast<Book>(item))
    {
        secondLabel->setText(itemCast.data()->getAuthor());
    }
    else if (auto itemCast = qSharedPointerDynamicCast<Game>(item))
    {
        secondLabel->setText(itemCast.data()->getPublisher());
    }
    else if (auto itemCast = qSharedPointerDynamicCast<Music>(item))
    {
        secondLabel->setText(itemCast.data()->getArtist());
    }

    containerCover = new QLabel(this);
    widgetLayout = new QVBoxLayout(this);
    QFontMetrics customFontMetrics(customFont);

    itemTitle = new QLabel(customFontMetrics.elidedText(item->getTitle(), Qt::ElideRight, 180));
    itemTitle->setAlignment(Qt::AlignCenter);

    QDir dir(QApplication::applicationDirPath());
    dir.cdUp();
    qDebug() << dir.filePath(item->getCoverImage());
    coverImage = new QPixmap(dir.filePath(item->getCoverImage()));

    containerCover->setPixmap(*coverImage);
    containerCover->setScaledContents(true);
    widgetLayout->addWidget(containerCover);
    widgetLayout->addWidget(itemTitle);
    widgetLayout->addWidget(secondLabel);
    setStyleSheet("background: rgba(255, 255, 255, 0.20)");
}

void ItemWidgetUI::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit widgetClicked(item);
}