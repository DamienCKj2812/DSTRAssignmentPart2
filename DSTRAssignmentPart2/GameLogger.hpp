#ifndef GAME_LOGGER_HPP
#define GAME_LOGGER_HPP

#include <string>
#include "Array.hpp"

// Struct to store performance per player
struct GameResult {
    int matchID;
    std::string teamName;
    std::string playerName;
    std::string university;
    int kills;
    int assists;
    int deaths;
    std::string outcome;
    std::string highlight;
};

class GameLogger {
private:
    Array<GameResult> historyArray;
    Array<GameResult> historyStack;

public:
    // Log a game result
    void logGameResult(int matchID,
        const std::string& teamName,
        const std::string& playerName,
        const std::string& university,
        int kills, int assists, int deaths,
        const std::string& outcome);
    void pushFinalGameResult(const GameResult& result) {
        historyArray.push(result);
        historyStack.push(result);
    }
    // Print logs
    void printArrayHistory() const;
    void printStackHistory();

    // Allow Match to access game history
    const Array<GameResult>& getHistory() const;

private:
    void printResult(const GameResult& r) const;
};

extern GameLogger gameLogger;

#endif
