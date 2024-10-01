#include "ZombieArena.h"
#include <iostream>
using namespace std;

Zombie* createHorde(int numZombies, IntRect arena)
{
    Zombie* zombies = new Zombie[numZombies];

    int maxY = arena.height - 20;
    int minY = arena.top + 20;
    int maxX = arena.width - 20;
    int minX = arena.left + 20;

    for (int i = 0; i < numZombies; i++)
    {
        // which side should the zombies spawn on
        srand((int)time(0) * i);
        int side = (rand() % 4);
        float x, y;
        switch (side)
        {
            case 0:
                // left
                x = minX;
                y = (rand() % maxY) + minY;
                break;
            case 1:
                // right
                x = maxX;
                y = (rand() % maxY) + minY;
                break;
            case 2:
                // top
                x = (rand() % maxX + minX);
                y = minY;
                break;
            case 3:
                // bottom
                x = (rand() % maxX) + minX;
                y = maxY;
                break;
        }
        // bloater, crawler or runner
        srand((int)time(0) * i * 2);
        int type = (rand() % 3);

        // spawn the new zombie into the array
        zombies[i].spawn(x, y, type, i);
    }

    return zombies;
}
/*
Zombie* createHorde(int numZombies, IntRect arena) {
    Zombie *zombies = new Zombie[numZombies];
    int maxX=arena.width - 50-42;
    int maxY=arena.height - 50-12;
    int minX=arena.left +50;
    int minY=arena.top + 50;
    cout<<maxX<<" "<<maxY<<" "<<minX<<" "<<minY<<endl;
    srand(time(NULL));
    for (int i = 0; i < numZombies; i++) {
        // which side should the zombies spawn on
        int x;
        int y;

        int side = rand() %4;
        switch (side)
        {
            case 0:
                // left
                x = minX;
                y = (rand() % maxY) ;
                break;
            case 1:
                // right
                x = maxX;
                y = (rand() % maxY) ;
                break;
            case 2:
                // top
                x=(rand()%maxX);
                y=minY;
                break;
            case 3:
                // bottom
                x=(rand()%maxX);
                y=maxY;
                break;
        }
        // bloater, crawler or runner
        int type = rand()*3;
        cout<<x<<" "<<y<<endl;
        zombies[i].spawn(x, y, type, i);
    }
    return zombies;
}
 */