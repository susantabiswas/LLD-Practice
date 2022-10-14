#include "GameObject.h"
using namespace std;

/*
    Game object Snake. Takes a player from
    top end to bottom end.
*/
class Snake: public GameObject {
public:
    Snake(int start, int end): GameObject(start, end) {}

    SnakeLadderGameObject getObjectType() {
        return SnakeObject;
    }

    /*
        Get the lower end of Snake
    */
    int getEndPosition() {
        return this->end;
    }

    /*
        Get the upper end of Snake
    */
    int getStartPosition() {
        return this->start;
    }
};