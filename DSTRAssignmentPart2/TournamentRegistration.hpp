#ifndef TOURNAMENT_REGISTRATION_HPP
#define TOURNAMENT_REGISTRATION_HPP

#include "Player.hpp"
#include "RegistrationPriorityQueue.hpp"
#include <string>

class TournamentRegistration {
private:
    RegisterPriorityQueue<Player> registrationQueue;
    RegisterPriorityQueue<Player> checkInQueue;

public:
    // Registers a new player into the registration queue (prioritized by registration type)
    void registerPlayer(const Player& player);

    // Transfers all players from the registration queue to the check-in queue
    void moveToCheckInQueue();

    // Removes a player by name from the check-in queue (used if they withdraw)
    void withdrawPlayer(const std::string& playerName);

    // Adds a new player as a replacement into the check-in queue
    void addReplacementPlayer(const Player& player);

    // Processes all players in the check-in queue (simulates check-in before tournament)
    Array<Player> processCheckIns(int count);
};

#endif
