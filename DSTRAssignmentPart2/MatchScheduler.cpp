#include "MatchScheduler.hpp"
#include "PlayerPriorityQueue.hpp"

MatchScheduler::MatchScheduler() : matchCounter(1) {}

void MatchScheduler::setPlayers(const Array<Player>& initialPlayers) {
    players = initialPlayers;
}

void MatchScheduler::scheduleInitialMatches(const std::string& stageStr) {
    MatchStage stage;
    if (stageStr == "Quarterfinal") stage = QUARTERFINAL;
    else if (stageStr == "Semifinal") stage = SEMIFINAL;
    else stage = FINAL;

    matches = Array<Match>();  // clear previous matches

    // Use priority queue to ensure pairing by ranking
    PlayerPriorityQueue<Player> queue;
    for (int i = 0; i < players.size(); ++i) {
        queue.insert(players.get(i));
    }

    while (queue.size() >= 2) {
        Player p1 = queue.extractTop();
        Player p2 = queue.extractTop();
        Match match(matchCounter++, new Player(p1), new Player(p2), stage);
        matches.push(match);
    }
}

void MatchScheduler::simulateMatches() {
    for (int i = 0; i < matches.size(); ++i) {
        Match& match = matches.get(i); 
        match.simulateMatch();
        match.display();
        std::cout << "----------------------------------------\n";
    }
}

void MatchScheduler::progressToNextStage(const std::string& nextStage) {
    Array<Player> winners = getWinners();
    setPlayers(winners);
    scheduleInitialMatches(nextStage);
}

void MatchScheduler::displayBracket() const {
    std::cout << "\n=== Current Match Bracket ===\n";
    for (int i = 0; i < matches.size(); ++i) {
        matches.get(i).display();
        std::cout << "----------------------------\n";
    }
}

Array<Player> MatchScheduler::getWinners() const {
    Array<Player> winners;
    for (int i = 0; i < matches.size(); ++i) {
        Player* winner = matches.get(i).getWinner();
        if (winner != nullptr) {
            winners.push(*winner);
        }
    }
    return winners;
}

bool MatchScheduler::isTournamentOver() const {
    return players.size() == 1;
}
