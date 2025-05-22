#ifndef MATCH_HPP
#define MATCH_HPP

#include "Player.hpp"
#include <cstdlib>  // for rand()
#include <ctime>    // for time()

class Match {
private:
    int matchID;
    Player* player1;
    Player* player2;
    Player* winner;
    std::string result;  // Format: "Player1 wins" / "Player2 wins" / "Draw"
    std::string stage;   // Qualifier, Group, Knockout

public:
    Match(int id, Player* p1, Player* p2, const std::string& stage);

    void setResult(const std::string& matchResult);
    void simulateMatch(); // NEW METHOD

    // Getters
    int getMatchID() const;
    Player* getPlayer1() const;
    Player* getPlayer2() const;
    Player* getWinner() const; // NEW GETTER
    std::string getResult() const;
    std::string getStage() const;

    void display() const;
};

#endif
