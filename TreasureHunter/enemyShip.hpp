
#ifndef ENEMYSHIP_HPP
#define ENEMYSHIP_HPP

#include "ship.hpp"

class EnemyShip : public Ship
{
public:
    EnemyShip(int x, int y) : Ship(x, y) {}
    void moveUp(Game& game) override;
    void moveDown(Game& game) override;
    void moveLeft(Game& game) override;
    void moveRight(Game& game) override;
    void collide(Game& game) override;
};


#endif
