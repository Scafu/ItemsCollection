/*
    CLASSE VISITOR ITEM NON CONST
*/
#ifndef VISITOR_H
#define VISITOR_H

class Book;
class Game;
class Music;

class AbstractVisitor
{
public:
    virtual ~AbstractVisitor() = default;
    virtual void visitBook(Book &book) = 0;
    virtual void visitGame(Game &game) = 0;
    virtual void visitMusic(Music &music) = 0;
};

#endif