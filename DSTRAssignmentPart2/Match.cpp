#include "Match.hpp"
#include "GameLogger.hpp"
#include "TimeUtils.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>


std::string getPlayerNameWithHighlight(const std::string& playerName) {
    std::string highlights[] = {"got First Blood", "got Double Kill", "got Triple Kill" ,"got Quadra Kill","got Penta Kill!!!"};
    int roll = rand() % 5;
    if (roll == 0) return playerName; 
    return playerName + " (" + highlights[roll] + ")";
}

Match::Match()
    : matchID(0), winner(nullptr), result("Not played"), stage(QUALIFIER) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

Match::Match(int id, const Array<Team*>& teams, MatchStage stage)
    : matchID(id), teams(teams), winner(nullptr), result("Not played"), stage(stage) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

void Match::setResult(const std::string& matchResult) {
    result = matchResult;
}

// Simulate the match and log game results
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

    Array<GameResult> tempResults;

    for (int i = 0; i < team1->getPlayerCount(); ++i) {
        Player& player = team1->getPlayer(i);
        int kills = rand() % 10 + 1;
        int assists = rand() % 6 + 1;
        int deaths = rand() % 4;
        team1Score += kills;

		 GameResult r(matchID, team1->getTeamName(),
					 getPlayerNameWithHighlight(player.getName()),
					 team1->getUniversity(), kills, assists, deaths,
					 "", getCurrentTimeString());
		tempResults.push(r);
    }

    for (int i = 0; i < team2->getPlayerCount(); ++i) {
        Player& player = team2->getPlayer(i);
        int kills = rand() % 10 + 1;
        int assists = rand() % 6 + 1;
        int deaths = rand() % 4;
        team2Score += kills;

		 GameResult r(matchID, team1->getTeamName(),
					 getPlayerNameWithHighlight(player.getName()),
					 team1->getUniversity(), kills, assists, deaths,
					 "", getCurrentTimeString()); 
		tempResults.push(r);
    }

    // Decide the winner
    winner = (team1Score >= team2Score) ? team1 : team2;
    result = winner->getTeamName() + " won the match.";

    for (int i = 0; i < tempResults.size(); ++i) {
        GameResult& r = tempResults.get(i);
        r.outcome = (r.teamName == winner->getTeamName()) ? "Win" : "Loss";
        gameLogger.pushFinalGameResult(r);
    }
}


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
