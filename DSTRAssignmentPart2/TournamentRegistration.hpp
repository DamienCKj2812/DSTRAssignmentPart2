#ifndef TOURNAMENT_REGISTRATION_HPP
#define TOURNAMENT_REGISTRATION_HPP

#include "Player.hpp"
#include "PriorityQueueRegistration.hpp"
#include <queue>
#include <string>

class TournamentRegistration {
private:
    RegisterPriorityQueue<Player> registrationQueue;
    RegisterPriorityQueue<Player> checkInQueue;

public:
    void registerPlayer(const Player& player);
    void moveToCheckInQueue();
    void withdrawPlayer(const std::string& playerName);
    void addReplacementPlayer(const Player& player);
    void processCheckIns();
};

#endif
