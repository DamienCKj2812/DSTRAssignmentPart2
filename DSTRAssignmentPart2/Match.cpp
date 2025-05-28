#include "Match.hpp"
#include "GameLogger.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Default constructor
Match::Match()
    : matchID(0), winner(nullptr), result("Not played"), stage(QUALIFIER) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

// Parameterized constructor
Match::Match(int id, const Array<Team*>& teams, MatchStage stage)
    : matchID(id), teams(teams), winner(nullptr), result("Not played"), stage(stage) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

// Set result manually
void Match::setResult(const std::string& matchResult) {
    result = matchResult;
}

// Simulate the match and log game results
// Rename simulateMatch() → simulateTeamBattle()
void Match::simulateTeamBattle() {
    if (teams.size() != 2) {
        result = "Match must have exactly two teams.";
        winner = nullptr;
        return;
    }

    Team* team1 = teams.get(0);
    Team* team2 = teams.get(1);

    int team1Score = 0;
    int team2Score = 0;

    for (int i = 0; i < team1->getPlayerCount(); ++i) {
        Player& player = team1->getPlayer(i);
        int kills = rand() % 10 + 1;
        int assists = rand() % 6 + 1;
        int deaths = rand() % 4;
        team1Score += kills;

        gameLogger.logGameResult(matchID,
            team1->getTeamName(),
            player.getName(),
            team1->getUniversity(),
            kills, assists, deaths,
            "TBD");
    }

    for (int i = 0; i < team2->getPlayerCount(); ++i) {
        Player& player = team2->getPlayer(i);
        int kills = rand() % 10 + 1;
        int assists = rand() % 6 + 1;
        int deaths = rand() % 4;
        team2Score += kills;

        gameLogger.logGameResult(matchID,
            team2->getTeamName(),
            player.getName(),
            team2->getUniversity(),
            kills, assists, deaths,
            "TBD");
    }

    winner = (team1Score >= team2Score) ? team1 : team2;
    result = winner->getTeamName() + " won the match.";

    for (int i = 0; i < gameLogger.getHistory().size(); ++i) {
        GameResult& r = const_cast<GameResult&>(gameLogger.getHistory().get(i));
        if (r.matchID == matchID) {
            r.outcome = (r.teamName == winner->getTeamName()) ? "Win" : "Loss";
        }
    }
}


// Optional manual override
void Match::setWinner(Team* t) {
    winner = t;
}

int Match::getMatchID() const {
    return matchID;
}

Array<Team*> Match::getTeams() const {
    return teams;
}

Team* Match::getWinner() const {
    return winner;
}

std::string Match::getResult() const {
    return result;
}

MatchStage Match::getStage() const {
    return stage;
}

void Match::display() const {
    std::cout << "Match ID   : " << matchID << std::endl;
    std::cout << "Stage      : " << getStageName(stage) << std::endl;

    std::cout << "Teams      : ";
    for (int i = 0; i < teams.size(); ++i) {
        std::cout << teams[i]->getTeamName()
            << " (Ranking:" << teams[i]->getRanking()
            << " From:" << teams[i]->getUniversity() << ")";
        if (i < teams.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;

    std::cout << "Result     : " << result << std::endl;

    if (winner != nullptr) {
        std::cout << "Winner     : " << winner->getTeamName() << std::endl;
    }
    else {
        std::cout << "Winner     : Not decided yet." << std::endl;
    }
}
