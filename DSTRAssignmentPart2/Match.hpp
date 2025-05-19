#ifndef MATCH_HPP
#define MATCH_HPP

#include "Player.hpp"

class Match {
private:
    int matchID;
    Player* player1;
    Player* player2;
    std::string result;  // Format: "Player1 wins" / "Player2 wins" / "Draw"
    std::string stage;   // Qualifier, Group, Knockout

public:
    // Constructor
    Match(int id, Player* p1, Player* p2, const std::string& stage);

    // Set result
    void setResult(const std::string& matchResult);

    // Getters
    int getMatchID() const;
    Player* getPlayer1() const;
    Player* getPlayer2() const;
    std::string getResult() const;
    std::string getStage() const;

    // Utility
    void display() const;
};

#endif
