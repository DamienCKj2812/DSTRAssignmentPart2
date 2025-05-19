#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>

class Player {
private:
    int playerID;
    std::string name;
    int ranking;
    std::string university;

public:
    // Constructor
    Player(int id, const std::string& playerName, int playerRanking, const std::string& uni);

    // Getters
    int getPlayerID() const;
    std::string getName() const;
    int getRanking() const;
    std::string getUniversity() const;

    // Setters
    void setRanking(int newRanking);

    // Utility
    void display() const;
};

#endif
