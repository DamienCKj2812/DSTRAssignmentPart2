#ifndef MATCH_HPP
#define MATCH_HPP

#include "Team.hpp"
#include "Array.hpp"
#include <iostream>

// Enum for match stages
enum MatchStage {
    QUALIFIER,
    GROUP,
    SEMIFINAL,
    FINAL
};

// Stage name helper
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
    Match();  // Default constructor
    Match(int id, const Array<Team*>& teams, MatchStage stage);  // Param constructor

    void simulateTeamBattle();  // Simulate & log battle
    void setResult(const std::string& matchResult);  // Manually set result
    void setWinner(Team* t);  // Manually set winner

    // Getters
    int getMatchID() const;
    Array<Team*> getTeams() const;
    Team* getWinner() const;
    std::string getResult() const;
    MatchStage getStage() const;

    void display() const;  // Print match details
};

#endif
