#include "Match.hpp"
#include <cstdlib>
#include <ctime>

// Default constructor
Match::Match()
    : matchID(0), winner(nullptr), result("Not played"), stage(QUALIFIER) {
    // Seed the random number generator using the current time
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

// Parameterized constructor
Match::Match(int id, const Array<Team*>& teams, MatchStage stage)
    : matchID(id), teams(teams), winner(nullptr), result("Not played"), stage(stage) {
    // Re-seed random number generator (optional if already seeded once in main)
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

// Set the result text manually (for example, for custom match outcomes)
void Match::setResult(const std::string& matchResult) {
    result = matchResult;
}

// Simulate the match and randomly select one team as the winner
void Match::simulateMatch() {
    if (teams.size() == 0) {
        result = "No teams in match."; // Handle edge case
        return;
    }

    // Pick a random team index from the list of teams
    int winnerIndex = std::rand() % teams.size();
    winner = teams[winnerIndex];

    // Save the result string with the winner's name
    result = winner->getTeamName() + " won the match.";
}

// Optional manual override to set the winner directly
void Match::setWinner(Team* t) {
    winner = t;
}

// Getter: Return match ID
int Match::getMatchID() const {
    return matchID;
}

// Getter: Return list of teams in this match
Array<Team*> Match::getTeams() const {
    return teams;
}

// Getter: Return the winner team pointer
Team* Match::getWinner() const {
    return winner;
}

// Getter: Return the result description
std::string Match::getResult() const {
    return result;
}

// Getter: Return the match stage (Qualifier, Group, etc.)
MatchStage Match::getStage() const {
    return stage;
}

// Display full match details to the console
void Match::display() const {
    std::cout << "Match ID   : " << matchID << std::endl;
    std::cout << "Stage      : " << getStageName(stage) << std::endl;

    std::cout << "Teams      : ";
    for (int i = 0; i < teams.size(); ++i) {
        std::cout << teams[i]->getTeamName() << " (Ranking:" << teams[i]->getRanking() << " From:" << teams[i]->getUniversity() << ")";
        if (i < teams.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;

    std::cout << "Result     : " << result << std::endl;

    if (winner != nullptr) {
        std::cout << "Winner     : " << winner->getTeamName() << std::endl;
    } else {
        std::cout << "Winner     : Not decided yet." << std::endl;
    }
}
