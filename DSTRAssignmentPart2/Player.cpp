#include "Player.hpp"

Player::Player(int id, const std::string& playerName, int playerRanking, const std::string& uni, RegistrationType type)
    : playerID(id), name(playerName), ranking(playerRanking), university(uni), regType(type) {}

int Player::getPlayerID() const {
    return playerID;
}

std::string Player::getName() const {
    return name;
}

int Player::getRanking() const {
    return ranking;
}

std::string Player::getUniversity() const {
    return university;
}

RegistrationType Player::getRegistrationType() const {
    return regType;
}

std::string Player::getRegTypeAsString() const {
    switch (regType) {
        case WILDCARD: return "Wildcard";
        case EARLY_BIRD: return "Early Bird";
        case REGULAR: return "Regular";
        default: return "Unknown";
    }
}

void Player::setRanking(int newRanking) {
    ranking = newRanking;
}

void Player::display() const {
    std::cout << "Player ID: " << playerID << "\n"
              << "Name: " << name << "\n"
              << "Ranking: " << ranking << "\n"
              << "University: " << university << "\n"
              << "Registration Type: " << getRegTypeAsString() << std::endl;
}
