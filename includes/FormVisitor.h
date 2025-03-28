/*
    VISITOR DEI FORM NON CONSTANTE
*/

#ifndef FORMVISITOR_H
#define FORMVISITOR_H

class BookCreationForm;
class GameCreationForm;
class MusicCreationForm;

class FormVisitor
{
public:
    virtual ~FormVisitor() = default;
    virtual void visitBookForm(BookCreationForm &) = 0;
    virtual void visitGameForm(GameCreationForm &) = 0;
    virtual void visitMusicForm(MusicCreationForm &) = 0;
};

#endif