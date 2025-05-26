#include "TournamentRegistration.hpp"
#include "RegistrationPriorityQueue.hpp"
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

// Register a team into the registration queue
void TournamentRegistration::registerTeam(const Team& team) {
    std::cout << "Registering team: " << team.getTeamName() << std::endl;
    registrationQueue.insert(team);
    teams.push(team);
}

// Move all teams from registration queue to check-in queue
void TournamentRegistration::moveToCheckInQueue() {
    std::cout << "\nMoving teams from registration to check-in queue...\n";
    while (!registrationQueue.isEmpty()) {
        Team t = registrationQueue.extractTop();
        std::cout << "Team " << t.getTeamName()
                  << " moved to check-in queue. ("
                  << registrationTypeToString(t.getRegistrationType()) << ")\n";
        checkInQueue.insert(t);
    }
}

// Withdraw a team from the check-in queue by team name
void TournamentRegistration::withdrawTeam(const std::string& teamName) {
    RegisterPriorityQueue<Team> tempQueue;
    bool withdrawn = false;

    while (!checkInQueue.isEmpty()) {
        Team t = checkInQueue.extractTop();
        if (t.getTeamName() == teamName) {
            std::cout << "Team " << teamName << " has withdrawn before check-in.\n";
            withdrawn = true;
            continue; // skip this team
        }
        tempQueue.insert(t);
    }

    checkInQueue = tempQueue;

    if (!withdrawn) {
        std::cout << "Team " << teamName << " not found in check-in queue.\n";
    }
}

// Process check-in for a limited number of teams by priority
Array<Team> TournamentRegistration::processCheckIns(int count) {
    Array<Team> checkedInTeams;
    std::cout << "\nProcessing team check-ins by priority...\n";

    while (!checkInQueue.isEmpty() && count-- > 0) {
        Team t = checkInQueue.extractTop();
        std::cout << "Checking in team: " << t.getTeamName()
                  << " (" << registrationTypeToString(t.getRegistrationType()) << ")\n";
        checkedInTeams.push(t);
    }

    std::cout << "Check-in complete. Teams ready for matches: " << checkedInTeams.size() << "\n";
    return checkedInTeams;
}


void TournamentRegistration::replaceTeam(int teamID, const Team& newTeam) {
    for (int i = 0; i < teams.size(); ++i) {
        if (teams[i].getTeamID() == teamID) {
            teams[i] = newTeam;
            std::cout << "Team ID " << teamID << " has been fully replaced with " << newTeam.getTeamName() << ".\n";
            return;
        }
    }
    std::cout << "Team ID " << teamID << " not found.\n";
}

// Replace a player in a registered team
void TournamentRegistration::replacePlayerInTeam(int teamID, int oldPlayerID, const Player& newPlayer) {
    for (int i = 0; i < teams.size(); ++i) {
        if (teams[i].getTeamID() == teamID) {
            Array<Player>& players = teams[i].getPlayers();
            for (int j = 0; j < players.size(); ++j) {
                if (players[j].getPlayerID() == oldPlayerID) {
                    players[j] = newPlayer;
                    std::cout << "Player ID " << oldPlayerID << " has been replaced by " << newPlayer.getName()
                              << " in team " << teams[i].getTeamName() << ".\n";
                    return;
                }
            }
            std::cout << "Player ID " << oldPlayerID << " not found in team " << teams[i].getTeamName() << ".\n";
            return;
        }
    }
    std::cout << "Team ID " << teamID << " not found.\n";
}
