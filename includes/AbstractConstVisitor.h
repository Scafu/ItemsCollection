/*
    CLASSE VISITOR CONST
*/
#ifndef ABSTRACTCONSTVISITOR_H
#define ABSTRACTCONSTVISITOR_H

class Book;
class Game;
class Music;

class AbstractConstVisitor
{
public:
    virtual ~AbstractConstVisitor() = default;
    virtual void visitBook(const Book &book) = 0;
    virtual void visitGame(const Game &game) = 0;
    virtual void visitMusic(const Music &music) = 0;
};

#endif