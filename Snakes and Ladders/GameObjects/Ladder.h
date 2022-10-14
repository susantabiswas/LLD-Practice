#include "GameObject.h"
using namespace std;

/*!
    Game object Ladder. Takes a player from
    bottom end to top end.
*/
class Ladder: public GameObject {
public:
    Ladder(int start, int end): GameObject(start, end) {};

    SnakeLadderGameObject getObjectType() {
        return LadderObject;
    }

    /*!
        Get the upper end of Ladder
    */
    int getEndPosition() {
        return this->end;
    }

    /*!
        Get the lower end of Ladder
    */
    int getStartPosition() {
        return this->start;
    }
};