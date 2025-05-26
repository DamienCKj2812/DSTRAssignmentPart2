#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>

class Player {
private:
    int playerID;
    std::string name;

public:
    Player();  // Default constructor
    Player(int id, const std::string& name);

    // Getters
    int getPlayerID() const;
    std::string getName() const;

    // Utility
    void display() const;
};

#endif
