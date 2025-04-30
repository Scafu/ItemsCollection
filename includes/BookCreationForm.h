/*
    CLASSE CONCRETA BOOKCREATIONFORM
*/

#ifndef BOOKCREATIONFORM_H
#define BOOKCREATIONFORM_H

#include "ItemCreationForm.h"

class BookCreationForm : public ItemCreationForm
{
    Q_OBJECT

public:
    explicit BookCreationForm(QWidget *parent = nullptr);

    // Funzioni getter testuali
    QString getAuthor() const;
    QString getLanguage() const;
    int getNumPages() const;
    int getNumChapters() const;
    QMap<QString, QVariant> getNotDefaultFields() const override;

    // Relative funzioni setter
    void setAuthor(const QString &newAuthor);
    void setLanguage(const QString &newLanguage);
    void setNumPages(int newNumPages);
    void setNumChapters(int newNumChapters);
    void setNotDefaultFields(const QMap<QString, QVariant> &fieldsToAdd) override;

    // Funzioni di servizio
    void clearFields() override;
    bool isDataValid();
    // Funzioni di visitor
    void accept(FormVisitor &Visitor) override;
    void accept(FormConstVisitor &constVisitor) const override;

private:
    QLineEdit *authorInput;
    QLineEdit *languageInput;
    QLineEdit *numPagesInput;
    QLineEdit *numChaptersInput;
};

#endif