#include "Player.hpp"

Player::Player(int id, const std::string& playerName, int playerRanking, const std::string& uni)
    : playerID(id), name(playerName), ranking(playerRanking), university(uni) {}

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

void Player::setRanking(int newRanking) {
    ranking = newRanking;
}

void Player::display() const {
    std::cout << "Player ID: " << playerID << "\n"
              << "Name: " << name << "\n"
              << "Ranking: " << ranking << "\n"
              << "University: " << university << std::endl;
}

