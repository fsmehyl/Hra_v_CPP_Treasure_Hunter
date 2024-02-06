
#ifndef SHIP_HPP
#define SHIP_HPP

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

/////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////

class Game;

class Ship
{
private:

    int x;
    int y;

public:
    Ship( int x, int y) :  x(x), y(y) {}
    virtual ~Ship() {}
    virtual void moveUp(Game& game) = 0;
    virtual void moveDown(Game& game) = 0;
    virtual void moveLeft(Game& game) = 0;
    virtual void moveRight(Game& game) = 0;
    virtual void collide(Game& game) = 0;

    int getX() const
    {
        return x;
    }
    void setX(int newX)
    {
        x = newX;
    }
    int getY() const
    {
        return y;
    }
    void setY(int newY)
    {
        y = newY;
    }
};

#endif
