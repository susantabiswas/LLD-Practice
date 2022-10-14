#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <functional>
#include "utils.h"
using namespace std;

/*!
    Class representing a player.
    A player has two main properties:
    1. Name
    2. Unique Id: Can be used to uniquely identify a player as players can 
                have the same name.
*/
class Player {
private: 
    // Current position of player on the board
    int position = 1;
    // Name and unique Id of player
    string name;
    string id;

public:
    Player(string name, int id_len = 5): name(name) {
        id = getUniqueId(id_len);
    };

    Player() {}

    bool operator==(const Player& p) const {
        return id == p.id && name == p.name;
    }

    void setPosition(int pos) {
        position = pos;
    }

    int getPosition() const {
        return position;
    }

    string getName() const {
        return name;
    }

    string getId() const {
        return id;
    }
};

/*! 
    Custom Hash function for Player class
*/
struct PlayerHash
{
    size_t operator()(const Player& p) const {
        return hash<string>()(p.getName())
            ^ hash<string>()(p.getId()) << 1
            ^ hash<int>()(p.getPosition()) << 1;
    }
};

#endif