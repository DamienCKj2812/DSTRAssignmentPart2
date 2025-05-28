#include "GameLogger.hpp"
#include "TimeUtils.hpp"
#include "Array.hpp"
#include <string>
#include <iostream>
#include <cstdlib>  
#include <ctime>


void GameLogger::logGameResult(int matchID,
    const std::string& teamName,
    const std::string& playerName,
    const std::string& university,
    int kills, int assists, int deaths,
    const std::string& outcome) {

    GameResult result{ matchID, teamName, playerName, university, kills, assists, deaths, outcome, getCurrentTimeString()};

    historyArray.push(result);
    historyStack.push(result);
}

void GameLogger::printArrayHistory() const {
    std::cout << "\n--- Game History Log (By Created Time) ---\n";
    for (int i = 0; i < historyArray.size(); ++i) {
        printResult(historyArray.get(i));
    }
}

void GameLogger::printStackHistory() {
    std::cout << "\n--- Game History Log (By Most Recent) ---\n";

    while (historyStack.size() > 0) {
        GameResult r = historyStack.pop();
        printResult(r);
    }
}

const Array<GameResult>& GameLogger::getHistory() const {
    return historyArray;
}

void GameLogger::printResult(const GameResult& r) const {
	std::cout << "----------------------------------------\n"
        << "Match ID: " << r.matchID
        << " | Team: " << r.teamName
        << " | University: " << r.university
        << " | Player: " << r.playerName
        << " | Kills: " << r.kills
        << " | Assists: " << r.assists
        << " | Deaths: " << r.deaths << "\n"
        << " | Outcome: " << r.outcome 
        << " | Created At: " << r.creationTime  << "\n"
        ;

}


void GameLogger::filterHistory(const FilterCondition conditions[], int conditionCount) const {
    std::cout << "\n--- Filtered Game History ---\n";

    for (int i = 0; i < historyArray.size(); ++i) {
        const GameResult& r = historyArray.get(i);
        bool match = true;

        for (int j = 0; j < conditionCount; ++j) {
            const std::string& field = conditions[j].field;
            const std::string& value = conditions[j].value;

            if (field == "teamName" && r.teamName != value) match = false;
            else if (field == "playerName" && r.playerName != value) match = false;
            else if (field == "university" && r.university != value) match = false;
            else if (field == "outcome" && r.outcome != value) match = false;
            else if (field == "matchID" && std::to_string(r.matchID) != value) match = false;

            if (!match) break;
        }

        if (match) {
            printResult(r);
            std::cout << "----------------------------------------\n";
        }
    }
}

GameLogger gameLogger;
