#ifndef BOARD_H
#define BOARD_H

#include "GameObjects/GameObject.h"
#include "player.h"
#include <unordered_map>
#include <iostream>
using namespace std;

/*
    addGameObject(): Adds special game elements
    reachedEnd(player): whether the player has finished the game or not
    movePlayer(player, int moves): Returns the final position of player after moves steps
    printBoard(): Prints the board
*/
class Board {
    int dim = 0;
    int end_position = 0;
    // Tracks the position of snakes and ladders
    // <position, instance of game object that starts there>
    unordered_map<int, GameObject*> game_objects;

public:
    Board(int n): dim(n) { end_position = dim * dim; };

    void addGameObject(GameObject*& obj) {
        game_objects[obj->getStartPosition()] = obj;
    }

    // Returns the final position of player given after walking
    // 'moves' steps on the board
    int movePlayer(Player player, int moves) {
        int position = player.getPosition();
        int final_position = position + moves;

        // final position can't go past the final position
        if(final_position > end_position) {
            cout << "Can't move, final position is beyond end of board!!" << endl;
            return position;
        }

        // player hit either a snake or ladder
        if(game_objects.count(final_position)) {
            cout << "Player reached a " << (game_objects[final_position]->getObjectType() == SnakeObject ? "Snake" : "Ladder") << endl;
            return game_objects[final_position]->getEndPosition();
        }

        return final_position;
    }

    bool reachedEnd(Player player) {
        return player.getPosition() == end_position;
    }

    void printBoard() {
        for(int r = dim*dim - dim; r >= 0; r -= dim) {
            for(int c = dim; c >= 1; c--) {
                int pos = r + c;
                if(game_objects.count(pos))
                    cout << ((game_objects[pos])->getObjectType() == SnakeLadderGameObject::SnakeObject ? "S" : "L");
                cout << pos;
                cout << "  ";
            }
            cout << endl;
        }
    }
};
#endif