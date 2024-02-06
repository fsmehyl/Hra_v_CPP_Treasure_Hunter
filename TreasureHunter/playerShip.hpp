#ifndef PLAYERSHIP_HPP
#define PLAYERSHIP_HPP

#include "ship.hpp"

class PlayerShip : public Ship
{
private:
    int score;

public:
    PlayerShip(int x, int y) : Ship( x, y), score(0) {}
    int getScore() const
    {
        return score;
    }
    void setScore(int s)
    {
        score = s;
    }
    void moveUp(Game& game) override;
    void moveDown(Game& game) override;
    void moveLeft(Game& game) override;
    void moveRight(Game& game) override;
    void collide(Game& game) override;


};

#endif
