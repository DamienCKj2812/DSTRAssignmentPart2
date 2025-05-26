#include "MatchScheduler.hpp"
#include "Player.hpp"
#include "Array.hpp"
#include "TournamentRegistration.hpp"
#include <iostream>

int main() {

    TournamentRegistration tournament;

    // Register players (same as your original list)
    tournament.registerPlayer(Player(1, "Alice", 5, "APU", EARLY_BIRD));
    tournament.registerPlayer(Player(2, "Bob", 3, "UM", REGULAR));
    tournament.registerPlayer(Player(3, "Charlie", 2, "UTAR", WILDCARD));
    tournament.registerPlayer(Player(4, "David", 7, "UPM", EARLY_BIRD));
    tournament.registerPlayer(Player(5, "Eve", 1, "USM", WILDCARD));
    tournament.registerPlayer(Player(6, "Frank", 8, "MMU", REGULAR));
    tournament.registerPlayer(Player(7, "Grace", 4, "TARUC", EARLY_BIRD));
    tournament.registerPlayer(Player(8, "Henry", 6, "HELP", REGULAR));

    tournament.moveToCheckInQueue();

    tournament.moveToCheckInQueue();

    tournament.withdrawPlayer("Bob");

    tournament.addReplacementPlayer(Player(9, "Walter white", 9, "UTAR", WILDCARD));

    tournament.processCheckIns();


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
	

    return 0;
}
