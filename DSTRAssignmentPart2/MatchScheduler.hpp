
#ifndef MATCH_SCHEDULER_HPP
#define MATCH_SCHEDULER_HPP

#include "Player.hpp"
#include "Match.hpp"
#include "Array.hpp"

class MatchScheduler {
private:
    Array<Player> players;
    Array<Match> matches;
    int matchCounter;

public:
    MatchScheduler();

    // Load or register initial players
    void setPlayers(const Array<Player>& initialPlayers);

    // Schedule fair matchups based on ranking
    void scheduleInitialMatches(const std::string& stage);

    // Simulate results for the current round
    void simulateMatches();

    // Progress winners to the next round
    void progressToNextStage(const std::string& nextStage);

    // Show current match bracket
    void displayBracket() const;

    // Return players who won in this round
    Array<Player> getWinners() const;

    // Check if competition has a winner
    bool isTournamentOver() const;
};

#endif
