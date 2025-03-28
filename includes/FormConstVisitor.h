/*
    VISITOR DEI FORM COSTANTE
*/

#ifndef FORMCONSTVISITOR_H
#define FORMCONSTVISITOR_H

class BookCreationForm;
class GameCreationForm;
class MusicCreationForm;

class FormConstVisitor
{
public:
    virtual ~FormConstVisitor() = default;
    virtual void visitBookForm(const BookCreationForm &) = 0;
    virtual void visitGameForm(const GameCreationForm &) = 0;
    virtual void visitMusicForm(const MusicCreationForm &) = 0;
};

#endif