#include "TournamentRegistration.hpp"
#include <iostream>

void TournamentRegistration::registerPlayer(const Player& player) {
    std::cout << "Registering player: " << player.getName() << std::endl;
    registrationQueue.insert(player);
}

void TournamentRegistration::moveToCheckInQueue() {
    std::cout << "\nMoving players from registration to check-in queue...\n";
    while (!registrationQueue.isEmpty()) {
        Player p = registrationQueue.extractTop();
        std::cout << "Player " << p.getName() << " moved to check-in queue.\n";
        checkInQueue.push(p);
    }
}

void TournamentRegistration::withdrawPlayer(const std::string& playerName) {
    std::queue<Player> tempQueue;
    bool withdrawn = false;
    while (!checkInQueue.empty()) {
        Player p = checkInQueue.front();
        checkInQueue.pop();
        if (p.getName() == playerName) {
            std::cout << "Player " << playerName << " has withdrawn before check-in.\n";
            withdrawn = true;
            continue;
        }
        tempQueue.push(p);
    }
    checkInQueue = tempQueue;
    if (!withdrawn) {
        std::cout << "Player " << playerName << " not found in check-in queue.\n";
    }
}

void TournamentRegistration::addReplacementPlayer(const Player& player) {
    std::cout << "Adding replacement player " << player.getName() << " to check-in queue.\n";
    checkInQueue.push(player);
}

void TournamentRegistration::processCheckIns() {
    std::cout << "\nProcessing player check-ins...\n";
    while (!checkInQueue.empty()) {
        Player curr = checkInQueue.front();
        checkInQueue.pop();
        std::cout << "Checking in player: " << curr.getName() << std::endl;
        // You can extend this to do more during check-in (like marking status)
    }
    std::cout << "All players checked in successfully.\n";
}
