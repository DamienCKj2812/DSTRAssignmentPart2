#include "MatchScheduler.hpp"
#include "TournamentRegistration.hpp"
#include "Player.hpp"
#include "Team.hpp"
#include "Array.hpp"
#include <iostream>
#include <string>
#include <cstdlib> 
#include <ctime>  
#include "GameLogger.hpp"



Team createTeam(int teamID, const std::string& name, const std::string& university, RegistrationType type, int basePlayerID) {
    int randomRanking = std::rand() % 100 + 1; // range: 1 to 100

    Team team(teamID, name, randomRanking, university, type); // set ranking randomly

    for (int i = 0; i < 3; ++i) {
        Player p(basePlayerID + i, name + "_P" + std::to_string(i + 1));
        team.addPlayer(p);
    }

    return team;
}

int main() {
	std::srand(static_cast<unsigned>(std::time(nullptr))); // seed RNG
    TournamentRegistration registration;

    std::string universities[] = {
        "APU", "UM", "TARUC", "UPM", "UTAR", "USM",
        "UUM", "UKM", "UIA", "UNIMAS", "UMP", "MMU"
    };

    for (int i = 1; i <= 24; ++i) {
        RegistrationType type;
        if (i % 3 == 0) type = WILDCARD;
        else if (i % 3 == 1) type = EARLY_BIRD;
        else type = REGULAR;

        std::string name = "Team" + std::to_string(i);
        std::string uni = universities[(i - 1) % 12];
        registration.registerTeam(createTeam(i, name, uni, type, i * 10));
    }


	// Create a new team to replace an existing one (e.g. team ID 5)
	Team replacementTeam = createTeam(5, "ReplacementTeam", "XYZ University", WILDCARD, 1000);
	registration.replaceTeam(5, replacementTeam);

	// Replace a specific player inside team ID 3 (old player ID = 30, new player = ID 999)
	Player newPlayer(999, "Substitute_Player");
	registration.replacePlayerInTeam(3, 30, newPlayer);

    registration.moveToCheckInQueue();
    Array<Team> readyTeams = registration.processCheckIns(24);

	Array<Team*> teamPointers;
	for (int i = 0; i < readyTeams.size(); ++i) {
		teamPointers.push(&readyTeams[i]);  // Take address of each Team
	}


    MatchScheduler scheduler;

	scheduler.scheduleQualifierMatches(teamPointers);
	scheduler.playMatches(scheduler.getQualifierMatches());
	Array<Team*> qualified = scheduler.getWinners(scheduler.getQualifierMatches());
	std::cout << "\n=== Qualifier Matches ===\n";
	scheduler.displayMatches(scheduler.getQualifierMatches());

	scheduler.scheduleGroupStage(qualified);
	scheduler.playMatches(scheduler.getGroupMatches());
	Array<Team*> groupWinners = scheduler.getWinners(scheduler.getGroupMatches());
	std::cout << "\n=== Group Stage Matches ===\n";
	scheduler.displayMatches(scheduler.getGroupMatches());

	scheduler.scheduleSemifinals(groupWinners);
	scheduler.playMatches(scheduler.getSemifinalMatches());
	Array<Team*> semiWinners = scheduler.getWinners(scheduler.getSemifinalMatches());
	std::cout << "\n=== Semifinal Matches ===\n";
	scheduler.displayMatches(scheduler.getSemifinalMatches());

	scheduler.scheduleFinal(semiWinners);
	scheduler.playMatches(scheduler.getFinalMatches());
	Array<Team*> finalWinner = scheduler.getWinners(scheduler.getFinalMatches());
	std::cout << "\n=== Final Match ===\n";
	scheduler.displayMatches(scheduler.getFinalMatches());

    std::cout << "\nChampion: ";
    if (finalWinner.size() > 0) {
        std::cout << finalWinner[0]->getTeamName() << " from " << finalWinner[0]->getUniversity() << "!\n";
    } else {
        std::cout << "No winner determined.\n";
    }

	gameLogger.printArrayHistory();  // Logs in order
	gameLogger.printStackHistory();  // Logs in reverse


    return 0;
}
