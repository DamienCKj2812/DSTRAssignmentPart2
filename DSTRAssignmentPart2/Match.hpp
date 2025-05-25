#ifndef MATCH_HPP
#define MATCH_HPP

#include "Player.hpp"
#include <iostream>
#include <cstdlib>  
#include <ctime>   

// Enum for match stage
enum MatchStage {
    QUARTERFINAL,
    SEMIFINAL,
    FINAL
};

// Utility function to get stage name
inline std::string getStageName(MatchStage stage) {
    switch (stage) {
        case QUARTERFINAL: return "Quarterfinal";
        case SEMIFINAL: return "Semifinal";
        case FINAL: return "Final";
        default: return "Unknown";
    }
}

class Match {
private:
    int matchID;
    Player* player1;
    Player* player2;
    Player* winner;
    std::string result;  
    MatchStage stage;

public:
    Match(int id, Player* p1, Player* p2, MatchStage stage);

    void setResult(const std::string& matchResult);
    void simulateMatch();

    // Getters
    int getMatchID() const;
    Player* getPlayer1() const;
    Player* getPlayer2() const;
    Player* getWinner() const;
    std::string getResult() const;
    MatchStage getStage() const;

    void display() const;
};

#endif
