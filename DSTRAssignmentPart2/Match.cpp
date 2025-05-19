#include "Match.hpp"

Match::Match(int id, Player* p1, Player* p2, const std::string& stage)
    : matchID(id), player1(p1), player2(p2), stage(stage), result("Pending") {}

void Match::setResult(const std::string& matchResult) {
    result = matchResult;
}

int Match::getMatchID() const {
    return matchID;
}

Player* Match::getPlayer1() const {
    return player1;
}

Player* Match::getPlayer2() const {
    return player2;
}

std::string Match::getResult() const {
    return result;
}

std::string Match::getStage() const {
    return stage;
}

void Match::display() const {
    std::cout << "Match ID: " << matchID << "\n"
              << "Stage: " << stage << "\n"
              << "Player 1: " << player1->getName() << " (Rank: " << player1->getRanking() << ")\n"
              << "Player 2: " << player2->getName() << " (Rank: " << player2->getRanking() << ")\n"
              << "Result: " << result << std::endl;
}
