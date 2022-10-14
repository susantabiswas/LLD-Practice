#include <iostream>
#include <random>
using namespace std;

/*!
    Class that represents a dice. 
    It mainly has a rollDice method that mimics a dice throw.
*/
class Dice {
private:
    int faces = 6;
    // Max no. of consecutive sixes player is allowed to make
    // before the turn is forfieted
    int max_consecutive_sixes = 3;

    // For generating random number with high degree of randomness
    // For normal usage, default_random_engine is also okay
    mt19937 mt;
    // For generating random number in range [1, faces]
    uniform_int_distribution<int> dist{1, faces};
public:
    Dice(int n_faces, int consecutive_sixes=3) {
        faces = n_faces;
        max_consecutive_sixes = consecutive_sixes;
        mt = mt19937(random_device()());
    }
    
    /*!
        Single dice throw
    */ 
    int getDiceFace() {
        return dist(mt);
    }

    /*!
        Final moves in case we get multiple 6s during throws
    */
    int rollDice() {
        int throws = 1;
        int value = 0;

        // If we get a 6, we get another chance.
        // If we get 6 consecutively 3 times, we lose all
        // the moves from last 3 dice throws
        do {
            int face = getDiceFace();
            value += face;

            if(face != 6)
                return value;
            ++throws;
        } while(throws <= max_consecutive_sixes);

        return 0;
    }
};
