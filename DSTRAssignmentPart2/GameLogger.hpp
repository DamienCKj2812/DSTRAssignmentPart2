#ifndef GAME_LOGGER_HPP
#define GAME_LOGGER_HPP

#include <string>
#include "Array.hpp"


struct FilterCondition {
    std::string field;
    std::string value;
};

struct GameResult {
    int matchID;
    std::string teamName;
    std::string playerName;   
    std::string university;
    int kills;
    int assists;
    int deaths;
    std::string outcome;
	std::string creationTime;


    GameResult() : matchID(0), kills(0), assists(0), deaths(0) {}
	GameResult(int id, const std::string& team, const std::string& player,
           const std::string& uni, int k, int a, int d,
           const std::string& result, const std::string& time)
    : matchID(id), teamName(team), playerName(player), university(uni),
      kills(k), assists(a), deaths(d), outcome(result), creationTime(time) {}
};


class GameLogger {
private:
    Array<GameResult> historyArray;
    Array<GameResult> historyStack;

public:
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
    void printArrayHistory() const;
    void printStackHistory();
	void filterHistory(const FilterCondition conditions[], int conditionCount) const;

    const Array<GameResult>& getHistory() const;

private:
    void printResult(const GameResult& r) const;
};

extern GameLogger gameLogger;

#endif
