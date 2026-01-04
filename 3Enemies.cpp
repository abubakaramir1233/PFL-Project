                                     //  gotoxy was not working on Mac  

#include <iostream>
#include <unistd.h> // usleep
using namespace std;

void drawMaze();
void moveEnemy(int &x, int &y, int &dir);
void updateEnemy(int x, int y, bool erase = false);

int main()
{
    int e1X = 10, e1Y = 3, e1Dir = 0;
    int e2X = 20, e2Y = 8, e2Dir = 0;
    int e3X = 30, e3Y = 5, e3Dir = 0;

    drawMaze();

    updateEnemy(e1X, e1Y);
    updateEnemy(e2X, e2Y);
    updateEnemy(e3X, e3Y);

    cout << "\033[22;1H";

    while (true)
    {
        usleep(300000);

        //                             # Erase enemies at old position#
        updateEnemy(e1X, e1Y, true);
        updateEnemy(e2X, e2Y, true);
        updateEnemy(e3X, e3Y, true);

        //                                     # Move enemies #
        moveEnemy(e1X, e1Y, e1Dir);
        moveEnemy(e2X, e2Y, e2Dir);
        moveEnemy(e3X, e3Y, e3Dir);

        //                               # Draw enemies at new positions#
        updateEnemy(e1X, e1Y);
        updateEnemy(e2X, e2Y);
        updateEnemy(e3X, e3Y);

        
        cout << "\033[22;1H";
        cout.flush();
    }

    return 0;
}

void drawMaze()
{
    system("clear");

    cout << "====================================================" << endl;
    cout << "#                                                  #" << endl;
    cout << "#                                                  #" << endl;
    cout << "#                                                  #" << endl;
    cout << "#                                                  #" << endl;
    cout << "#                                                  #" << endl;
    cout << "#                                                  #" << endl;
    cout << "#                                                  #" << endl;
    cout << "#                                                  #" << endl;
    cout << "#                                                  #" << endl;
    cout << "#                                                  #" << endl;
    cout << "#                                                  #" << endl;
    cout << "#      =======            =======                  #" << endl;
    cout << "#      =======            =======                  #" << endl;
    cout << "#      =======            =======                  #" << endl;
    cout << "#                                                  #" << endl;
    cout << "#                                                  #" << endl;
    cout << "#                                                  #" << endl;
    cout << "#                                                  #" << endl;
    cout << "#                                                  #" << endl;
    cout << "#                                                  #" << endl;
    cout << "#                                                  #" << endl;
    cout << "####################################################" << endl;
}

void moveEnemy(int &x, int &y, int &dir)
{
    if (dir == 0)
    { // right
        x++;
        if (x >= 44)
            dir = 1;
    }
    else if (dir == 1)
    { // down
        y++;
        if (y >= 6)
            dir = 2;
    }
    else if (dir == 2)
    { // left
        x--;
        if (x <= 8)
            dir = 3;
    }
    else if (dir == 3)
    {  // up
        y--;
        if (y <= 3)
            dir = 0;
    }
}

void updateEnemy(int x, int y, bool erase)
{
    if (erase)
    {
        cout << "\033[" << y << ";" << x << "H    ";
        cout << "\033[" << y + 1 << ";" << x << "H    ";
    }
    else
    {
        cout << "\033[" << y << ";" << x << "H /v\\";
        cout << "\033[" << y + 1 << ";" << x << "H  E";
    }
    cout.flush();
}
