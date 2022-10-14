#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
using namespace std;

/*!
    Represent Game objects
*/
enum SnakeLadderGameObject {
    SnakeObject, LadderObject 
};

/*! Abstract class to represent game objects like
    Snakes and Ladders
*/
class GameObject {
protected:
    int start = 0, end = 0;
public:
    GameObject(int start, int end)
     : start(start), end(end) {};

    virtual SnakeLadderGameObject getObjectType() = 0;

    virtual int getEndPosition() = 0;

    virtual int getStartPosition() = 0;
};

#endif