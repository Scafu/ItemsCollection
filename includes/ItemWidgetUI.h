/*
    WIDGET CHE VIENE MOSTRATO NELLA HOMEPAGE
*/
#ifndef ITEMWIDGETUI_H
#define ITEMWIDGETUI_h

#include "AbstractItem.h"
#include "Book.h"
#include "Game.h"
#include "Music.h"
#include <QSharedPointer>
#include <QLabel>
#include <QPixmap>
#include <QMouseEvent>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

class ItemWidgetUI : public QWidget
{
    Q_OBJECT

public:
    explicit ItemWidgetUI(QSharedPointer<AbstractItem> item, QWidget *parent = nullptr);

signals:
    void widgetClicked(QSharedPointer<AbstractItem> item);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QSharedPointer<AbstractItem> item;
    QLabel *itemTitle;
    QLabel *secondLabel;
    QLabel *containerCover;
    QPixmap *coverImage;
    QVBoxLayout *widgetLayout;
};

#endif
