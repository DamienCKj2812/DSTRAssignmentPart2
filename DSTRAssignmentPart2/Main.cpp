#include "MatchScheduler.hpp"
#include "Player.hpp"
#include "Array.hpp"
#include <iostream>

int main() {
    MatchScheduler scheduler;
    Array<Player> playerList;

    // Add 8 players (simulate different rankings and types)
    playerList.push(Player(1, "Alice", 5, "APU", EARLY_BIRD));
    playerList.push(Player(2, "Bob", 3, "UM", REGULAR));
    playerList.push(Player(3, "Charlie", 2, "UTAR", WILDCARD));
    playerList.push(Player(4, "David", 7, "UPM", EARLY_BIRD));
    playerList.push(Player(5, "Eve", 1, "USM", WILDCARD));
    playerList.push(Player(6, "Frank", 8, "MMU", REGULAR));
    playerList.push(Player(7, "Grace", 4, "TARUC", EARLY_BIRD));
    playerList.push(Player(8, "Henry", 6, "HELP", REGULAR));

    scheduler.setPlayers(playerList);
    scheduler.scheduleInitialMatches("Quarterfinal");

    // Round 1
    std::cout << "\n--- Quarterfinal ---\n";
    scheduler.simulateMatches();

    // Round 2

Array<Player> winners = scheduler.getWinners();
std::cout << "Winners this round: " << winners.size() << "\n";
    scheduler.progressToNextStage("Semifinal");
    std::cout << "\n--- Semifinal ---\n";
    scheduler.simulateMatches();

    // Round 3
    scheduler.progressToNextStage("Final");
    std::cout << "\n--- Final ---\n";
    scheduler.simulateMatches();

    // Final Winner
    if (scheduler.isTournamentOver()) {
        Array<Player> finalWinner = scheduler.getWinners();
        std::cout << "\n?? Tournament Winner: " << finalWinner.get(0).getName() << "\n";
    }
	}

    return 0;
}
