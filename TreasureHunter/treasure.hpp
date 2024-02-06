#ifndef TREASURE_HPP
#define TREASURE_HPP

class Treasure
{
private:

    int x;
    int y;

public:
    Treasure(int x, int y) : x(x), y(y) {}

    int getX() const
    {
        return x;
    }
    int getY() const
    {
        return y;
    }
};

#endif
