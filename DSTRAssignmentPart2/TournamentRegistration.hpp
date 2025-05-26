#ifndef TOURNAMENT_REGISTRATION_HPP
#define TOURNAMENT_REGISTRATION_HPP

#include "Team.hpp"
#include "RegistrationPriorityQueue.hpp"
#include <string>

class TournamentRegistration {
private:
    RegisterPriorityQueue<Team> registrationQueue;  // Now using Team
    RegisterPriorityQueue<Team> checkInQueue;
    Array<Team> teams;  // Store all registered teams

public:
    void registerTeam(const Team& team);         // Replaces registerPlayer
    void moveToCheckInQueue();                   // Transfers teams from registration to check-in
    void withdrawTeam(const std::string& teamName); // Removes team by name
    Array<Team> processCheckIns(int count);      // Check in N teams by priority

    // Team update utilities
	void replaceTeam(int teamID, const Team& newTeam); // Replace entire team by ID
	void replacePlayerInTeam(int teamID, int oldPlayerID, const Player& newPlayer); // Already exists
};

#endif
