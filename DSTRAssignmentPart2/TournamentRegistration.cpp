#include "TournamentRegistration.hpp"
#include "PriorityQueueRegistration.hpp"  // << Include your priority queue here
#include <iostream>
#include <string>

// Convert RegistrationType to readable string
std::string registrationTypeToString(RegistrationType type) {
    switch (type) {
    case EARLY_BIRD: return "EARLY_BIRD";
    case REGULAR:    return "REGULAR";
    case WILDCARD:   return "WILDCARD";
    default:         return "UNKNOWN";
    }
}

void TournamentRegistration::registerPlayer(const Player& player) {
    std::cout << "Registering player: " << player.getName() << std::endl;
    registrationQueue.insert(player);  // Use your custom insert
}

void TournamentRegistration::moveToCheckInQueue() {
    std::cout << "\nMoving players from registration to check-in queue...\n";
    while (!registrationQueue.isEmpty()) {
        Player p = registrationQueue.extractTop();
        std::cout << "Player " << p.getName() << " moved to check-in queue. ("
            << registrationTypeToString(p.getRegistrationType()) << ")\n";

        checkInQueue.insert(p);  // Insert into check-in queue
    }
}

void TournamentRegistration::withdrawPlayer(const std::string& playerName) {
    RegisterPriorityQueue<Player> tempQueue;
    bool withdrawn = false;

    while (!checkInQueue.isEmpty()) {
        Player p = checkInQueue.extractTop();
        if (p.getName() == playerName) {
            std::cout << "Player " << playerName << " has withdrawn before check-in.\n";
            withdrawn = true;
            continue;  // skip adding withdrawn player
        }
        tempQueue.insert(p);
    }

    checkInQueue = tempQueue;

    if (!withdrawn) {
        std::cout << "Player " << playerName << " not found in check-in queue.\n";
    }
}

void TournamentRegistration::addReplacementPlayer(const Player& player) {
    std::cout << "Adding replacement player " << player.getName() << " to check-in queue.\n";
    checkInQueue.insert(player);
}

void TournamentRegistration::processCheckIns() {
    std::cout << "\nProcessing player check-ins...\n";
    while (!checkInQueue.isEmpty()) {
        Player curr = checkInQueue.extractTop();
        std::cout << "Checking in player: " << curr.getName() << " ("
            << registrationTypeToString(curr.getRegistrationType()) << ")\n";
    }
    std::cout << "All players checked in successfully.\n";
}
