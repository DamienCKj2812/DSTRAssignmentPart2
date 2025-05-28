#ifndef MATCH_HPP
#define MATCH_HPP

#include "Team.hpp"
#include "Array.hpp"
#include <iostream>


enum MatchStage {
    QUALIFIER,
    GROUP,
    SEMIFINAL,
    FINAL
};


inline std::string getStageName(MatchStage stage) {
    switch (stage) {
    case QUALIFIER: return "Qualifier";
    case GROUP:     return "Group Stage";
    case SEMIFINAL: return "Semifinal";
    case FINAL:     return "Final";
    default:        return "Unknown";
    }
}

class Match {
private:
    int matchID;
    Array<Team*> teams;
    Team* winner;
    std::string result;
    MatchStage stage;

public:
    Match();  
    Match(int id, const Array<Team*>& teams, MatchStage stage);  

    void simulateTeamBattle();  
    void setResult(const std::string& matchResult);  
    void setWinner(Team* t);  

    // Getters
    int getMatchID() const;
    Array<Team*> getTeams() const;
    Team* getWinner() const;
    std::string getResult() const;
    MatchStage getStage() const;

    void display() const; 
};

#endif
