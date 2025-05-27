#ifndef TEAM_HPP
#define TEAM_HPP

#include <iostream>
#include <string>
#include "Player.hpp"
#include "Array.hpp"

enum RegistrationType {
    WILDCARD = 1,
    EARLY_BIRD = 2,
    REGULAR = 3
};

class Team {
private:
    int teamID;
    std::string teamName;
    int ranking;
    std::string university;
    RegistrationType regType;
    Array<Player> players;
    int playerCount;

public:
    Team();
    Team(int id, const std::string& name, int teamRanking,
         const std::string& uni, RegistrationType type);
    // Add inside Team class (public)
    int getPlayerCount() const;
    Player& getPlayer(int index);  // returns reference to player

    int getTeamID() const;
    std::string getTeamName() const;
    int getRanking() const;
    std::string getUniversity() const;
    RegistrationType getRegistrationType() const;
    std::string getRegTypeAsString() const;
    Array<Player>& getPlayers();

    void setRanking(int newRanking);
    void addPlayer(const Player& player);
    void display() const;
};

#endif
