#pragma comment(lib, "rpcrt4.lib") 
#include <iostream>
#include "GameObjects/GameObjectFactory.h"
#include "board.h"
#include "player.h"
#include "dice.h"
#include <map>
#include <unordered_set>

using namespace std;

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

    void registerPlayer(Player& player) {
        this->players[player.getId()] = player;
        cout << "Player: " << player.getId() << " added\n";
    }

    void deregisterPlayer(const string& id) {
        if(!players.count(id))
            throw invalid_argument("Player Id doesn't exists!!");
        this->players.erase(id);
        
        cout << "Player: " << id << "removed\n";
    }

    bool isGameOver() {
        int players_who_finished = rankings.size();
        // Game is over if a single winner has emerged
        if(this->single_player_game_over)
            return players_who_finished == 1;

        // If game gets over when all the players have finished
        return players_who_finished == this->total_players;
    }

    void updateRankings(const Player& player) {
        if(rankings.empty()) {
            rankings[1] = player;
            return;
        }
        auto [last_rank, _] = *rankings.rbegin();
        rankings[last_rank + 1] = player;
    }

    void showRankings() {
        cout << endl << "Leaderboard Rankings\n";
        for(auto [rank, player]: rankings)
            cout << rank << ". " << player.getName() << " (" << player.getId() << ")\n";
    }

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
    Dice dice(3);
    
    Board board(5);

    // Create Snakes and Ladders
    // vector<GameObject*> gameObjects = {
    //     GameObjectFactory::createGameObject(SnakeObject, 3, 99),
    //     GameObjectFactory::createGameObject(SnakeObject, 3, 96),
    //     GameObjectFactory::createGameObject(SnakeObject, 13, 67),
    //     GameObjectFactory::createGameObject(SnakeObject, 66, 88),
    //     GameObjectFactory::createGameObject(SnakeObject, 28, 77),
    //     GameObjectFactory::createGameObject(SnakeObject, 55, 66),
    //     GameObjectFactory::createGameObject(LadderObject, 4, 98),
    //     GameObjectFactory::createGameObject(LadderObject, 5, 60),
    //     GameObjectFactory::createGameObject(LadderObject, 14, 82),
    //     GameObjectFactory::createGameObject(LadderObject, 54, 97),
    //     GameObjectFactory::createGameObject(LadderObject, 44, 93),
    //     GameObjectFactory::createGameObject(LadderObject, 35, 61),
    // };

    vector<GameObject*> gameObjects = {};

    // Add snakes and ladders
    for(auto game_obj: gameObjects)
        board.addGameObject(game_obj);
    
    // Create players
    vector<Player> players = {
        Player("Alpha"), Player("Beta"), Player("Gamma")
    };

    Game game(board, dice, players, false);
    
    // Start game till one player wins
    game.playGame();

    return 0;
}