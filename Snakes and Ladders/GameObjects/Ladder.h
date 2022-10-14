#include "GameObject.h"
using namespace std;

class Ladder: public GameObject {
public:
    Ladder(int start, int end): GameObject(start, end) {};

    SnakeLadderGameObject getObjectType() {
        return LadderObject;
    }

    int getEndPosition() {
        return this->end;
    }

    int getStartPosition() {
        return this->start;
    }
};