#include "GameObject.h"
using namespace std;

class Snake: public GameObject {
public:
    Snake(int start, int end): GameObject(start, end) {}

    SnakeLadderGameObject getObjectType() {
        return SnakeObject;
    }

    int getEndPosition() {
        return this->end;
    }

    int getStartPosition() {
        return this->start;
    }
};