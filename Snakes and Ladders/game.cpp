#include <iostream>
#include "GameObjects/GameObjectFactory.h"
#include "board.h"
#include "player.h"
#include "dice.h"
#include <map>
#include <unordered_set>

using namespace std;

/// @brief Game class orchestrates the entire game. It mainly uses dice, board and player objects.
class Game {
private:
    Dice dice;
    Board board;

    // Total players who started playing
    int total_players = 0;
    
    // Tracks the players actively playing
    unordered_map<string, Player> players;

    // Whether game finishes when a single player has won
    bool single_player_game_over;
    
    // Tracks the players who have finished the game in the order of completion
    map<int, Player> rankings;
public:
    /*!
        Registers the players to the game.
        It uses composition and has board and dice objects.
    */
    Game(Board board, Dice dice, vector<Player>& players, 
        bool single_player_game_over = true)
        : board(board), dice(dice) {
        
        this->single_player_game_over = single_player_game_over;

        // register the players currently playing
        for(auto& player: players)
            this->registerPlayer(player);

        this->total_players = players.size();
        
        cout << "Board Layout....\n";
        board.printBoard();
        cout << endl;

        cout << "Single Player Game Over: " << single_player_game_over << endl;
    };

    /*! 
        Registers a player to the game
    */
    void registerPlayer(Player& player) {
        this->players[player.getId()] = player;
        cout << "Player: " << player.getId() << " added\n";
    }

    /*! 
        De-registers a player to the game
    */
    void deregisterPlayer(const string& id) {
        if(!players.count(id))
            throw invalid_argument("Player Id doesn't exists!!");
        this->players.erase(id);
        
        cout << "Player: " << id << "removed\n";
    }

    /*!
        Checks if the condition has been met to end the game.
        players_who_finished: If this is set, then the game gets over when a 
        single player wins.
    */
    bool isGameOver() {
        int players_who_finished = rankings.size();
        // Game is over if a single winner has emerged
        if(this->single_player_game_over)
            return players_who_finished == 1;

        // If game gets over when all the players have finished
        return players_who_finished == this->total_players;
    }

    /*!
        Leaderboard is maintained, a new player is added to it.
    */
    void updateRankings(const Player& player) {
        if(rankings.empty()) {
            rankings[1] = player;
            return;
        }
        auto [last_rank, _] = *rankings.rbegin();
        rankings[last_rank + 1] = player;
    }

    /*!
        Prints the leaderboard rankings.
    */
    void showRankings() {
        cout << endl << "Leaderboard Rankings\n";
        for(auto [rank, player]: rankings)
            cout << rank << ". " << player.getName() << " (" << player.getId() << ")\n";
    }

    /*!
        Driver method that runs the game.
        It runs a game loop where each loop iteration ensures that each player rolls the
        dice and make the moves.

        In case a player reaches the end position of board, they are added to the leaderboard.
    */
    void playGame() {
        while(!isGameOver()) {
            // Each player will take a turn. The game ends if 
            // the player reaches the end of board
            for(auto& [id, player]: players) {
                int moves = dice.rollDice();

                cout << "Player: " << player.getName() 
                    << ", Current Position: " << player.getPosition() 
                    << ", Got " << moves << " from dice\n";
                
                // Make the player take steps given by dice
                // Also check if a game object like snake or ladder exists at the final step
                int position = board.movePlayer(player, moves);
                cout << "Player moved to " << position << endl;
                // update player's position
                player.setPosition(position);

                // check if the player has reached the end
                if(board.reachedEnd(player)) {
                    cout << "Player: " << player.getName() << " has won!!\n";
                    updateRankings(player);
                    
                    // remove the current player from active players
                    this->deregisterPlayer(id);
                    if(isGameOver())
                        break;
                }
                cout << endl;
            }
        }
        showRankings();
    }
};

int main() {
    // Dice instance
    Dice dice(3);
    // Snake and Ladder instance
    Board board(5);

    // Create Snakes and Ladders
    vector<GameObject*> gameObjects = {
        GameObjectFactory::createGameObject(SnakeObject, 3, 9),
        GameObjectFactory::createGameObject(SnakeObject, 5, 19),
        GameObjectFactory::createGameObject(LadderObject, 6, 24),
        GameObjectFactory::createGameObject(LadderObject, 10, 22),
        GameObjectFactory::createGameObject(LadderObject, 11, 20),
    };

    // Add snakes and ladders to the board
    for(auto game_obj: gameObjects)
        board.addGameObject(game_obj);
    
    // Create players
    vector<Player> players = {
        Player("Alpha"), Player("Beta"), Player("Gamma")
    };

    // Create the game object and then start the game
    Game game(board, dice, players, false);
    
    // Start game till one player wins
    game.playGame();

    return 0;
}