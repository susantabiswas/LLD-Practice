#include "Snake.h"
#include "Ladder.h" 

class GameObjectFactory {
public:
    // Factory method that creates a GameObject based on requirement.
    // For a snake, lower point is the end and upper point is the start.
    // For a ladder, lower point is the start and upper point is the end.
    static GameObject* createGameObject(
        SnakeLadderGameObject object_type,
        int lower_pt, 
        int upper_pt) {

        switch(object_type) {
            case SnakeObject:
                return new Snake(upper_pt, lower_pt);
                break;
            case LadderObject:
                return new Ladder(lower_pt, upper_pt);
                break;
            default:
                throw invalid_argument("Illegal game object type!!");
        }
    }
};
