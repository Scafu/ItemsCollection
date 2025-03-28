#include "AbstractItem.h"

AbstractItem::AbstractItem(const QString newImage, const QString newTitle, const QString newDescription, const int newYear) : coverImage(newImage), title(newTitle), description(newDescription), year(newYear) {}

AbstractItem::~AbstractItem() {}

// Funzioni gettere testuali
QString AbstractItem::getCoverImage() const { return coverImage; }
QString AbstractItem::getTitle() const { return title; }
QString AbstractItem::getDescription() const { return description; }
int AbstractItem::getYear() const { return year; }

// Funzioni setter relative
AbstractItem &AbstractItem::setCoverImage(const QString &newImage)
{
    this->coverImage = newImage;
    return *this;
}
AbstractItem &AbstractItem::setTitle(const QString &newTitle)
{
    this->title = newTitle;
    return *this;
}
AbstractItem &AbstractItem::setDescription(const QString &newDescription)
{
    this->description = newDescription;
    return *this;
}
AbstractItem &AbstractItem::setYear(const int &newYear)
{
    this->year = newYear;
    return *this;
}
