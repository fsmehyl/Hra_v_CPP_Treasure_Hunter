#ifndef GAME_HPP
#define GAME_HPP

#include "playerShip.hpp"
#include "enemyShip.hpp"
#include "treasure.hpp"
#include "obstacle.hpp"

class Game {

public:
    vector<EnemyShip*> enemyShips;
    vector<Treasure> treasures;
    vector<Obstacle> obstacles;
    PlayerShip playerShip;
    int mapSize;
    bool gameOver;

    Game(int size) : mapSize(size), playerShip( size / 2, size / 2), gameOver(false)
    {
        srand(time(nullptr));
        generateEnemies();
        generateTreasures();
        generateObstacles();
    }

    ~Game()
    {
        for (auto enemyShip : enemyShips)
        {
            delete enemyShip;
        }
    }

    void generateEnemies()
    {
        int numEnemies = mapSize + 50;

        for (int i = 0; i < numEnemies; i++)
        {
            int x = rand() % mapSize;
            int y = rand() % mapSize;
            if (x == playerShip.getX() && y == playerShip.getY())
            {
                continue;
            }
            EnemyShip* enemyShip = new EnemyShip(x, y);
            enemyShips.push_back(enemyShip);
        }
    }

    void generateTreasures()
    {
        int numTreasures = mapSize / 4;
        for (int i = 0; i < numTreasures; i++)
        {
            int x = rand() % mapSize;
            int y = rand() % mapSize;
            if (x == playerShip.getX() && y == playerShip.getY())
            {
                continue;
            }
            Treasure treasure(x, y);
            treasures.push_back(treasure);
        }
    }

    void generateObstacles()
    {
        int numObstacles = mapSize * 2;
        for (int i = 0; i < numObstacles; i++)
        {
            int x = rand() % mapSize;
            int y = rand() % mapSize;
            if (x == playerShip.getX() && y == playerShip.getY())
            {
                continue;
            }
            Obstacle obstacle(x, y);
            obstacles.push_back(obstacle);
        }
    }

    void checkTreasure()
    {
        for (auto it = treasures.begin(); it != treasures.end(); ++it)
        {
            if (it->getX() == playerShip.getX() && it->getY() == playerShip.getY())
            {
                treasures.erase(it);
                playerShip.setScore(playerShip.getScore() + 1);
                if (treasures.empty())
                {
                    gameOver = true;
                    cout << "Congratulations, YOU WIN!" << endl;
                }
                break;
            }
        }
    }


    void checkCollision()
    {
        for (auto enemyShip : enemyShips)
        {
            if (enemyShip->getX() == playerShip.getX() && enemyShip->getY() == playerShip.getY())
            {
                playerShip.collide(*this);
                break;
            }
        }
        for (const auto& obstacle : obstacles)
        {
            if (obstacle.collidesWithShip(playerShip))
            {
                playerShip.collide(*this);
                break;
            }
        }
    }


    void printMap()
    {
        system("cls");

        for (int i = 0; i < mapSize; i++)
        {
            for (int j = 0; j < mapSize; j++)
            {
                if (i == playerShip.getX() && j == playerShip.getY())
                {
                    cout << "P ";
                }
                else
                {
                    bool enemyShipPresent = false;
                    for (const auto enemyShip : enemyShips)
                    {
                        if (enemyShip->getX() == i && enemyShip->getY() == j)
                        {
                            cout << "E ";
                            enemyShipPresent = true;
                            break;
                        }
                    }
                    if (!enemyShipPresent)
                    {
                        bool treasurePresent = false;
                        for (const auto& treasure : treasures)
                        {
                            if (treasure.getX() == i && treasure.getY() == j)
                            {
                                cout << "T ";
                                treasurePresent = true;
                                break;
                            }
                        }
                        if (!treasurePresent)
                        {
                            bool obstaclePresent = false;
                            for (const auto& obstacle : obstacles)
                            {
                                if (obstacle.getX() == i && obstacle.getY() == j)
                                {
                                    cout << "O ";
                                    obstaclePresent = true;
                                    break;
                                }
                            }
                            if (!obstaclePresent)
                            {
                                cout << ". ";
                            }
                        }
                    }
                }
            }
            cout << endl;
        }

        cout << "Remaining treasures: " << treasures.size() << endl;

        }

    void movePlayerShipUp()
    {
        if (playerShip.getX() > 0)
        {
            playerShip.moveUp(*this);
        }
        checkCollision();
        checkTreasure();
    }

    void movePlayerShipDown()
    {
        if (playerShip.getX() < mapSize - 1)
        {
            playerShip.moveDown(*this);
        }
        checkCollision();
        checkTreasure();
    }

    void movePlayerShipLeft()
    {
        if (playerShip.getY() > 0)
        {
            playerShip.moveLeft(*this);
        }
        checkCollision();
        checkTreasure();
    }

    void movePlayerShipRight()
    {
        if (playerShip.getY() < mapSize - 1)
        {
            playerShip.moveRight(*this);
        }
        checkCollision();
        checkTreasure();
    }

    void moveEnemyShips()
    {
        for (auto enemyShip : enemyShips)
        {
            int direction = rand() % 4;  // Generate a random direction: 0 - up, 1 - down, 2 - left, 3 - right
            switch (direction)
            {
            case 0:
                if (enemyShip->getX() > 0)
                {
                    enemyShip->moveUp(*this);
                }
                break;
            case 1:
                if (enemyShip->getX() < mapSize - 1)
                {
                    enemyShip->moveDown(*this);
                }
                break;
            case 2:
                if (enemyShip->getY() > 0)
                {
                    enemyShip->moveLeft(*this);
                }
                break;
            case 3:
                if (enemyShip->getY() < mapSize - 1)
                {
                    enemyShip->moveRight(*this);
                }
                break;
            default:
                break;
            }
        }
        checkCollision();
    }

    void saveGame(const string& filename)
    {
        ofstream file(filename);
        if (file.is_open())
        {
            file << mapSize << endl;
            file << playerShip.getX() << " " << playerShip.getY() << endl;
            file << playerShip.getScore() << endl;
            file << enemyShips.size() << endl;
            for (const auto enemyShip : enemyShips)
            {
                file << " " << enemyShip->getX() << " " << enemyShip->getY() << endl;
            }
            file << treasures.size() << endl;
            for (const auto& treasure : treasures)
            {
                file << treasure.getX() << " " << treasure.getY() << endl;
            }
            file << obstacles.size() << endl;
            for (const auto& obstacle : obstacles)
            {
                file << obstacle.getX() << " " << obstacle.getY() << endl;
            }
            file.close();
            cout << "Game saved successfully!" << endl;
        }
        else
        {
            cout << "Unable to save the game." << endl;
        }
    }

    void loadGame(const string& filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        int size, playerX, playerY, score, numEnemies, numTreasures, numObstacles;
        file >> size;
        file >> playerX >> playerY;
        file >> score;
        file >> numEnemies;

        for (auto enemyShip : enemyShips)
        {
            delete enemyShip;
        }
        enemyShips.clear();
        treasures.clear();
        obstacles.clear();

        for (int i = 0; i < numEnemies; i++)
        {
            int enemyX, enemyY;
            file >> enemyX >> enemyY;
            enemyShips.push_back(new EnemyShip(enemyX, enemyY));
        }
        file >> numTreasures;
        for (int i = 0; i < numTreasures; i++)
        {
            int treasureX, treasureY;
            file >> treasureX >> treasureY;
            treasures.push_back(Treasure(treasureX, treasureY));
        }
        file >> numObstacles;
        for (int i = 0; i < numObstacles; i++)
        {
            int obstacleX, obstacleY;
            file >> obstacleX >> obstacleY;
            obstacles.push_back(Obstacle(obstacleX, obstacleY));
        }
        file.close();

        mapSize = size;
        playerShip.setX(playerX);
        playerShip.setY(playerY);
        playerShip.setScore(score);
        gameOver = false;
        cout << "Game loaded successfully!" << endl;
    }
    else
    {
        cout << "Unable to load the game." << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

};

void PlayerShip::moveUp(Game& game)
{
    game.playerShip.setX(game.playerShip.getX() - 1);
}

void PlayerShip::moveDown(Game& game)
{
    game.playerShip.setX(game.playerShip.getX() + 1);
}

void PlayerShip::moveLeft(Game& game)
{
    game.playerShip.setY(game.playerShip.getY() - 1);
}

void PlayerShip::moveRight(Game& game)
{
    game.playerShip.setY(game.playerShip.getY() + 1);
}

void PlayerShip::collide(Game& game)
{
    game.gameOver = true;
    cout << "Player was killed in action!" << endl;
    cout << "Better luck next time!" << endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////

void EnemyShip::moveUp(Game& game)
{
    setX(getX() - 1);
}

void EnemyShip::moveDown(Game& game)
{
    setX(getX() + 1);
}

void EnemyShip::moveLeft(Game& game)
{
    setY(getY() - 1);
}

void EnemyShip::moveRight(Game& game)
{
    setY(getY() + 1);
}


void EnemyShip::collide(Game& game)
{
    game.enemyShips.erase(game.enemyShips.begin());
}

/////////////////////////////////////////////////////////////////////////////////////////////////////



#endif
