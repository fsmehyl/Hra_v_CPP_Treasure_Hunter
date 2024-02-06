#include "game.hpp"

int main()
{
    Game game(20);

    while (!game.gameOver)
    {
        game.printMap();

        char m;
        cout << "Enter your move (W/A/S/D): " << endl;
        cout << "\t\t\t\t\t SAVE GAME(R)" << endl << endl;
        cout << "\t\t\t\t\t LOAD GAME(F)" << endl << endl;
        cout << "\t\t\t\t\t EXIT GAME(E)" << endl;
        cin >> m;

        switch (m)
        {
        case 'w':
        case 'W':
            game.movePlayerShipUp();
            break;
        case 's':
        case 'S':
            game.movePlayerShipDown();
            break;
        case 'a':
        case 'A':
            game.movePlayerShipLeft();
            break;
        case 'd':
        case 'D':
            game.movePlayerShipRight();
            break;
        case 'r':
        case 'R':
            game.saveGame("savedGame.txt");
            break;
        case 'f':
        case 'F':
            game.loadGame("savedGame.txt");
            break;
        case 'e':
        case 'E':
            return 1;
        default:
            cout << "Invalid move. Please try again." << endl;
            break;
        }

        game.moveEnemyShips();

    }

    return 0;
}
