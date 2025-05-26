#include "Player.hpp"

// Default constructor
Player::Player() : playerID(0), name("Unknown") {}

// Parameterized constructor
Player::Player(int id, const std::string& name) : playerID(id), name(name) {}

// Getter for playerID
int Player::getPlayerID() const {
    return playerID;
}

// Getter for name
std::string Player::getName() const {
    return name;
}

// Display player details
void Player::display() const {
    std::cout << "Player ID: " << playerID << std::endl;
    std::cout << "Name     : " << name << std::endl;
}
