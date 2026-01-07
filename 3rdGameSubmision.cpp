//                                   ##############################  THIS CODE IS WRITTEN ACCORDING TO MacOS #########################
//                                                                         MIGHT NOT WORK ON WINDOWS
#include <iostream>
#include <unistd.h> // usleep
#include <termios.h>
#include <fcntl.h>
using namespace std;

int stage = 1;

bool e1Alive = true;
bool e2Alive = true;
bool e3Alive = true;
const int MAX_STAGES = 3;

bool pillCollected[21][49] = {false};
int pX = 25, pY = 18;
int playerLives = 3;
int score = 0;
int pbX = -1, pbY = -1;

void drawMaze();
void moveEnemy(int &x, int &y, int &dir);
void updateEnemy(int x, int y, bool erase = false);
void moveEnemyBullet(int &bx, int &by, int ex, int ey);
void updatePlayer(int x, int y, bool erase = false);
void drawPills();
void movePlayer();
void showScore();
void movePlayerBullet(int &bx, int &by);
bool checkEnemyHit(int bx, int by, int &ex, int &ey);
bool killEnemy(int bx, int by, int &ex, int &ey, bool &alive, int &ebx, int &eby);
// ####################################################### ALTERNATIVES FOR GetChar and Async ##############################################################
struct termios orig_termios;

void disableInputBuffering()
{
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios newt = orig_termios;
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_cc[VMIN] = 0;
    newt.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void restoreTerminal()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}
char getKey()
{
    char ch = 0;
    char a, b;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_cc[VMIN] = 0;
    newt.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    if (read(STDIN_FILENO, &ch, 1) == 1)
    {
        if (ch == 27)
        {
            if (read(STDIN_FILENO, &a, 1) == 1 &&
                read(STDIN_FILENO, &b, 1) == 1)
            {
                if (a == '[' && b == 'A')
                    ch = 'U'; // Up
                else if (a == '[' && b == 'B')
                    ch = 'D'; // Down
                else if (a == '[' && b == 'C')
                    ch = 'R'; // Right
                else if (a == '[' && b == 'D')
                    ch = 'L'; // Left
                else
                    ch = 0;
            }
        }
    }
    else
        ch = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    return ch;
}
// ########################################################################### MAIN ##############################################################################################################
int main()
{
    disableInputBuffering();

    int e1X = 10, e1Y = 3, e1Dir = 0;
    int e2X = 20, e2Y = 8, e2Dir = 0;
    int e3X = 30, e3Y = 5, e3Dir = 0;
    // -------- Enemy bullet --------
    int b1X = -1, b1Y = -1;
    int b2X = -1, b2Y = -1;
    int b3X = -1, b3Y = -1;

    drawMaze();
    drawPills();
    updatePlayer(pX, pY);

    if (e1Alive)
        updateEnemy(e1X, e1Y);
    if (e2Alive)
        updateEnemy(e2X, e2Y);
    if (e3Alive)
        updateEnemy(e3X, e3Y);

    updatePlayer(pX, pY);

    cout << "\033[22;1H";

    while (true)
    {

        usleep(120000);

        if (playerLives <= 0)
        {
            system("clear");
            cout << "\n\n\n         GAME OVER!\n";
            cout << "         Score: " << score << "\n\n";
            break;
        }

        movePlayer();
        movePlayerBullet(pbX, pbY);
        if (killEnemy(pbX, pbY, e1X, e1Y, e1Alive, b1X, b1Y))
        {
            score += 50;
            pbX = pbY = -1;
        }
        if (killEnemy(pbX, pbY, e2X, e2Y, e2Alive, b2X, b2Y))
        {
            score += 50;
            pbX = pbY = -1;
        }
        if (killEnemy(pbX, pbY, e3X, e3Y, e3Alive, b3X, b3Y))
        {
            score += 50;
            pbX = pbY = -1;
        }
        if (!e1Alive && !e2Alive && !e3Alive)
        {
            if (stage == MAX_STAGES)
            {
                system("clear");
                cout << "\n\n\n        YOU WIN!\n\n";
                cout << "        Final Score: " << score << "\n\n";
                restoreTerminal();
                return 0;
            }

            stage++;

            system("clear");
            cout << "\n\n   STAGE " << stage << "\n";
            usleep(1200000);

            drawMaze();
            drawPills();

            // reset enemies
            e1X = 10;
            e1Y = 3;
            e1Dir = 0;
            e2X = 25;
            e2Y = 5;
            e2Dir = 0;
            e3X = 40;
            e3Y = 4;
            e3Dir = 0;

            e1Alive = e2Alive = e3Alive = true;

            // reset bullets
            b1X = b1Y = -1;
            b2X = b2Y = -1;
            b3X = b3Y = -1;
            pbX = pbY = -1;
        }

        showScore();

        if (e1Alive)
            updateEnemy(e1X, e1Y, true);
        if (e2Alive)
            updateEnemy(e2X, e2Y, true);
        if (e3Alive)
            updateEnemy(e3X, e3Y, true);

        if (e1Alive)
            moveEnemy(e1X, e1Y, e1Dir);
        if (e2Alive)
            moveEnemy(e2X, e2Y, e2Dir);
        if (e3Alive)
            moveEnemy(e3X, e3Y, e3Dir);

        if (e1Alive)
            updateEnemy(e1X, e1Y);
        if (e2Alive)
            updateEnemy(e2X, e2Y);
        if (e3Alive)
            updateEnemy(e3X, e3Y);
            
        if (e1Alive)
            moveEnemyBullet(b1X, b1Y, e1X, e1Y);
        else
            b1X = b1Y = -1;

        if (e2Alive)
            moveEnemyBullet(b2X, b2Y, e2X, e2Y);
        else
            b2X = b2Y = -1;

        if (e3Alive)
            moveEnemyBullet(b3X, b3Y, e3X, e3Y);
        else
            b3X = b3Y = -1;

        cout.flush();
    }
    restoreTerminal();
    return 0;
}

void drawMaze()
{
    system("clear");

    cout << "===================================================================================#" << endl;
    cout << "#                                                  #                               #" << endl;
    cout << "#                                                  #         SPACE SHOOTER         #" << endl;
    cout << "#                                                  #                               #" << endl;
    cout << "#                                                  #                               #" << endl;
    cout << "#                                                  #                               #" << endl;
    cout << "#                                                  #                               #" << endl;
    cout << "#                                                  #                               #" << endl;
    cout << "#                                                  #                               #" << endl;
    cout << "#                                                  #                               #" << endl;
    cout << "#                                                  #                               #" << endl;
    cout << "#                                                  #                               #" << endl;
    cout << "#      =======            =======                  #                               #" << endl;
    cout << "#      =======            =======                  #                               #" << endl;
    cout << "#      =======            =======                  #                               #" << endl;
    cout << "#                                                  #    // Collect pills to        #" << endl;
    cout << "#                                                  #       increase score          #" << endl;
    cout << "#                                                  #                               #" << endl;
    cout << "#                                                  #                               #" << endl;
    cout << "#                                                  #                               #" << endl;
    cout << "#                                                  #                               #" << endl;
    cout << "#                                                  #                               #" << endl;
    cout << "####################################################################################" << endl;
}
void showScore()
{
    cout << "\033[6;55HScore: " << score
         << "  Lives: " << playerLives
         << "  Stage: " << stage;
}
void movePlayer()
{
    char key = getKey();
    if (key == 0)
        return;

    // erase old player
    updatePlayer(pX, pY, true);

    if (key == 'U' && pY > 16)
        pY--;
    else if (key == 'D' && pY < 20)
        pY++;
    else if (key == 'L' && pX > 2)
        pX--;
    else if (key == 'R' && pX < 48)
        pX++;
    // shoot bullet
    if (key == ' ' && pbX == -1 && pbY == -1)
    {
        pbX = pX + 1;
        pbY = pY - 1;
    }
    int rows[] = {16, 18, 20};
    int cols[] = {5, 11, 17, 23, 29, 35, 41, 47};

    for (int y : rows)
    {
        for (int x : cols)
        {

            if (pX <= x && pX + 2 >= x &&
                pY <= y && pY + 1 >= y &&
                !pillCollected[y][x])
            {
                score += 10;
                pillCollected[y][x] = true;
                cout << "\033[" << y << ";" << x << "H ";
            }
        }
    }

    updatePlayer(pX, pY);
}
void updatePlayer(int x, int y, bool erase)
{
    if (erase)
    {
        cout << "\033[" << y << ";" << x << "H   ";
        cout << "\033[" << y + 1 << ";" << x << "H    ";
    }
    else
    {
        cout << "\033[" << y << ";" << x << "H  A";
        cout << "\033[" << y + 1 << ";" << x << "H /V\\";
    }
    cout.flush();
}
void moveEnemyBullet(int &bx, int &by, int ex, int ey)
{
    if (bx == -1 && by == -1)
    {
        bx = ex + 1;
        by = ey + 2;
        return;
    }

    if (by >= pY && by <= pY + 1 &&
        bx >= pX && bx <= pX + 2)
    {
        playerLives--;
        bx = -1;
        by = -1;

        updatePlayer(pX, pY);
        return;
    }

    cout << "\033[" << by << ";" << bx << "H ";

    by++;

    if (by >= 22)
    {
        bx = -1;
        by = -1;
        return;
    }
    if ((by >= 13 && by <= 15) &&
        ((bx >= 8 && bx <= 14) || (bx >= 28 && bx <= 34)))
    {
        bx = -1;
        by = -1;
        return;
    }

    cout << "\033[" << by << ";" << bx << "H*";
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
    { // up
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
void drawPills()
{
    for (int y = 16; y <= 20; y += 2)
    {
        for (int x = 5; x <= 47; x += 6)
        {
            cout << "\033[" << y << ";" << x << "H.";
        }
    }
}
void movePlayerBullet(int &bx, int &by)
{
    if (bx == -1 || by == -1)
        return;

    // ERASE CURRENT BULLET POSITION FIRST
    cout << "\033[" << by << ";" << bx << "H ";

    // next position
    int nextY = by - 1;

    // STOP at maze blocks
    if ((nextY >= 13 && nextY <= 15) &&
        ((bx >= 8 && bx <= 14) || (bx >= 28 && bx <= 34)))
    {
        bx = by = -1;
        return;
    }

    // STOP at top border
    if (nextY <= 1)
    {
        bx = by = -1;
        return;
    }

    by = nextY;

    cout << "\033[" << by << ";" << bx << "H|";
}
bool killEnemy(int bx, int by, int &ex, int &ey, bool &alive,
               int &ebx, int &eby)
{
    if (!alive)
        return false;

    if (by >= ey && by <= ey + 1 &&
        bx >= ex && bx <= ex + 3)
    {
        // erase enemy
        updateEnemy(ex, ey, true);

        // erase enemy bullet on screen
        if (ebx != -1 && eby != -1)
            cout << "\033[" << eby << ";" << ebx << "H ";

        ebx = eby = -1;

        alive = false;
        return true;
    }
    return false;
}