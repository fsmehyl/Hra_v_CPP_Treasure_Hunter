
#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

class Obstacle
{
private:

    int x;
    int y;

public:
    Obstacle(int x, int y) : x(x), y(y) {}

    int getX() const
    {
        return x;
    }
    int getY() const
    {
        return y;
    }
    bool collidesWithShip(const Ship& ship) const
    {
        return (x == ship.getX() && y == ship.getY());
    }
};

#endif
