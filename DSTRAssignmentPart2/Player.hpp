#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>

enum RegistrationType {
    WILDCARD = 1,     // Highest priority
    EARLY_BIRD = 2,   // Medium priority
    REGULAR = 3,    // Lowest priority
    LATE=4  
};

class Player {
private:
    int playerID;
    std::string name;
    int ranking;
    std::string university;
    RegistrationType regType;

public:
	Player();  // Default constructor

    // Constructor
    Player(int id, const std::string& playerName, int playerRanking,
           const std::string& uni, RegistrationType type);

    // Getters
    int getPlayerID() const;
    std::string getName() const;
    int getRanking() const;
    std::string getUniversity() const;
    RegistrationType getRegistrationType() const;
    std::string getRegTypeAsString() const;

    // Setters
    void setRanking(int newRanking);

    // Utility
    void display() const;
};

#endif
