#include "GameLogger.hpp"
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


    GameResult result{ matchID, teamName, playerName, university, kills, assists, deaths, outcome};

    historyArray.push(result);
    historyStack.push(result);
}

void GameLogger::printArrayHistory() const {
    std::cout << "\n--- Game History Log (Queue) ---\n";
    for (int i = 0; i < historyArray.size(); ++i) {
        printResult(historyArray.get(i));
    }
}

void GameLogger::printStackHistory() {
    std::cout << "\n--- Game History Log (Stack) ---\n";
    while (historyStack.size() > 0) {
        GameResult r = historyStack.pop();
        printResult(r);
    }
}

const Array<GameResult>& GameLogger::getHistory() const {
    return historyArray;
}

void GameLogger::printResult(const GameResult& r) const {
    std::cout << "Match ID: " << r.matchID
        << " | Team: " << r.teamName
        << " | University: " << r.university
        << " | Player: " << r.playerName
        << " | Kills: " << r.kills
        << " | Assists: " << r.assists
        << " | Deaths: " << r.deaths
        << " | Outcome: " << r.outcome << "\n";

}


GameLogger gameLogger;
