#include "MatchScheduler.hpp"
#include "Player.hpp"
#include "Array.hpp"
#include "TournamentRegistration.hpp"
#include <iostream>

int main() {

    TournamentRegistration tournament;

    // Register players (same as your original list)
	tournament.registerPlayer(Player(1,  "Alice",   5,  "APU",     EARLY_BIRD));
	tournament.registerPlayer(Player(2,  "Bob",     3,  "UM",      REGULAR));
	tournament.registerPlayer(Player(3,  "Charlie", 2,  "UTAR",    WILDCARD));
	tournament.registerPlayer(Player(4,  "David",   7,  "UPM",     EARLY_BIRD));
	tournament.registerPlayer(Player(5,  "Eve",     1,  "USM",     WILDCARD));
	tournament.registerPlayer(Player(6,  "Frank",   8,  "MMU",     REGULAR));
	tournament.registerPlayer(Player(7,  "Grace",   4,  "TARUC",   EARLY_BIRD));
	tournament.registerPlayer(Player(8,  "Henry",   6,  "HELP",    REGULAR));
	tournament.registerPlayer(Player(9,  "Isaac",   9,  "INTI",    REGULAR));
	tournament.registerPlayer(Player(10, "Jasmine", 2,  "UCSI",    WILDCARD));
	tournament.registerPlayer(Player(11, "Kevin",   3,  "SEGI",    EARLY_BIRD));
	tournament.registerPlayer(Player(12, "Liam",    6,  "UNIMAS",  REGULAR));
	tournament.registerPlayer(Player(13, "Mona",    4,  "UITM",    EARLY_BIRD));
	tournament.registerPlayer(Player(14, "Nathan",  1,  "UKM",     WILDCARD));
	tournament.registerPlayer(Player(15, "Olivia",  7,  "UUM",     REGULAR));
	tournament.registerPlayer(Player(16, "Peter",   5,  "UUM",     EARLY_BIRD));
	tournament.registerPlayer(Player(17, "Queen",   3,  "UNITAR",  WILDCARD));
	tournament.registerPlayer(Player(18, "Ryan",    2,  "UNIKL",   EARLY_BIRD));
	tournament.registerPlayer(Player(19, "Sarah",   8,  "UCSI",    REGULAR));
	tournament.registerPlayer(Player(20, "Tom",     6,  "OUM",     EARLY_BIRD));

    tournament.moveToCheckInQueue();
    tournament.withdrawPlayer("Bob");

    tournament.addReplacementPlayer(Player(9, "Walter white", 9, "UTAR", WILDCARD));

    Array<Player> playerList = tournament.processCheckIns(8);
    MatchScheduler scheduler;

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
