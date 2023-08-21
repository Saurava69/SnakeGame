#include<bits/stdc++.h>
#include <stdio.h>
#include <malloc.h>
#include <Windows.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
using namespace std;
#define ff fflush(stdin)
struct Body
{
    int x;
    int y;

    Body *next;
} *head, *tail;

int Map[40][120];

int sizeX = 90;
int sizeY = 20;
int score = 0;
int xFood = 4;
int yFood = 10;

void createBody(int x, int y)
{
    Body *body = (Body *)malloc(sizeof(Body));
    body->x = x;
    body->y = y;
    if (!head)
    {
        head = tail = body;
    }
    else
    {
        tail->next = body;
        // body->prev = tail;
        tail = body;
    }
    tail->next = NULL;
}

void gotoxy(int x, int y)
{
    COORD c = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void createMap()
{
    for (int i = 0; i < sizeY; i++)
    {
        for (int j = 0; j < sizeX; j++)
        {
            if (i == 0 || i == sizeY - 1 || j == 0 || j == sizeX - 1)
                Map[i][j] = 1;
            else
                Map[i][j] = 0;
        }
    }
    Map[yFood][xFood] = 3;
}

void createFood()
{
    srand(time(NULL));
    Map[yFood][xFood] = 0;
    do
    {
        xFood = rand() % (sizeX - 1) + 1;
        yFood = rand() % (sizeY - 1) + 1;
    } while (Map[yFood][xFood] != 0);
    Map[yFood][xFood] = 3;
    gotoxy(xFood, yFood);
    printf("*");
}

void viewMap()
{
    for (int i = 0; i < sizeY; i++)
    {
        for (int j = 0; j < sizeX; j++)
        {
            if (Map[i][j] == 1)
                printf("%c", 177);
            else if (Map[i][j] == 3)
                printf("*");
            else
                printf(" ");
        }
        puts("");
    }
}

bool run(int x, int y)
{
    Body *curr = head;
    int tempX;
    int tempY;
    int helpX;
    int helpY;
    while (curr)
    {
        if (curr == head)
        {
            if (score > 2)
            {
                Body *vcurr = head->next->next;
                while (vcurr)
                {
                    if (vcurr->x == head->x && vcurr->y == head->y)
                    {
                        return false;
                    }
                    vcurr = vcurr->next;
                }
            }

            Map[curr->y][curr->x] = 0;
            if (head->x + x < 1 || head->x + x > sizeX - 2 || head->y + y < 1 || head->y + y > sizeY - 2)
            {
                return false;
            }
            if (head->x == xFood && head->y == yFood)
            {
                int newX = tail->x - x;
                int newY = tail->y - y;
                createBody(newX, newY);
                score++;
                createFood();
            }

            gotoxy(curr->x, curr->y);
            printf(" ");
            tempX = curr->x;
            tempY = curr->y;
            curr->x = curr->x + x;
            curr->y = curr->y + y;
        }
        else
        {

            Map[curr->y][curr->x] = 0;
            gotoxy(curr->x, curr->y);
            printf(" ");
            helpX = tempX;
            helpY = tempY;

            tempX = curr->x;
            tempY = curr->y;

            curr->x = helpX;
            curr->y = helpY;
        }

        Map[curr->y][curr->x] = 2;
        gotoxy(curr->x, curr->y);
        printf("%c", 177);

        curr = curr->next;
    }
    return true;
}

void play()
{
    char move;
    int dir = 4;
    bool walk = true;
    int speed;
    score = 0;
    while (walk)
    {
        if (score > 10)
            speed = 150;
        else if (score > 20)
            speed = 100;
        else if (score < 11)
            speed = 200;
        else
            speed = 50;

        if (kbhit())
        {
            switch (tolower(move = getch()))
            {
            case 'w':
                if (dir != 3)
                    dir = 1;
                if (dir == 1)
                    speed /= 2;
                break;
            case 'a':
                if (dir != 4)
                    dir = 2;
                if (dir == 2)
                    speed /= 2;
                break;
            case 's':
                if (dir != 1)
                    dir = 3;
                if (dir == 3)
                    speed /= 2;
                break;
            case 'd':
                if (dir != 2)
                    dir = 4;
                if (dir == 4)
                    speed /= 2;
                break;
            }
        }

        switch (dir)
        {
        case 1:
            walk = run(0, -1);
            break;
        case 2:
            walk = run(-1, 0);
            break;
        case 3:
            walk = run(0, 1);
            break;
        case 4:
            walk = run(1, 0);
            break;
        }

        gotoxy(1, sizeY + 1);
        printf("Scrore : %d", score);

        Sleep(speed);
    }
}
void popAll()
{
    while (head)
    {
        Body *curr;
        curr = head;
        head = head->next;
        free(curr);
    }
}

int main()
{
    system("Saurav's Snake Game");
    int input = 0;

    while (input != 2)
    {
        system("cls");
        puts("1.play");
        puts("2.exit");
        scanf("%d", &input);
        ff;
        if (input == 1)
        {
            system("cls");
            createBody(4, 4);
            createMap();
            viewMap();
            play();
            gotoxy(1, sizeY + 2);
            printf("game over");
            char m;
            scanf("%c", &m);
            ff;

            popAll();
        }
    }

    return 0;
}