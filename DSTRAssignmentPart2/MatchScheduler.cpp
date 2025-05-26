#include "MatchScheduler.hpp"
#include "TeamPriorityQueue.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Constructor: initialize match ID counter
MatchScheduler::MatchScheduler() : matchCounter(1) {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed RNG once
}

// Schedule Qualifier Matches using priority queue (strongest vs strongest)
void MatchScheduler::scheduleQualifierMatches(Array<Team*>& teams) {
    TeamPriorityQueue<Team*> pq;

    // Insert all teams into the priority queue
    for (int i = 0; i < teams.size(); ++i) {
        pq.insert(teams[i]);
    }

    // Schedule matches from strongest vs next strongest
    while (pq.size() >= 2) {
        Team* t1 = pq.extractTop();
        Team* t2 = pq.extractTop();

        Array<Team*> matchTeams;
        matchTeams.push(t1);
        matchTeams.push(t2);

        Match match(matchCounter++, matchTeams, QUALIFIER);
        qualifierMatches.push(match);
    }

    // Handle odd leftover team 
    if (!pq.isEmpty()) {
        Team* t1 = pq.extractTop();
        Array<Team*> matchTeams;
        matchTeams.push(t1);

        Match match(matchCounter++, matchTeams, QUALIFIER);
        match.setResult(t1->getTeamName() + " advances automatically due to odd team count.");
        match.setWinner(t1);  // Assume automatic win
        qualifierMatches.push(match);
    }
}

// Schedule Group Stage Matches using priority queue (strongest grouped first)
void MatchScheduler::scheduleGroupStage(Array<Team*>& qualifiedTeams) {
    const int groupSize = 3;

    // Step 1: Load all teams into the priority queue
    TeamPriorityQueue<Team*> pq;
    for (int i = 0; i < qualifiedTeams.size(); ++i) {
        pq.insert(qualifiedTeams[i]);
    }

    // Step 2: Form groups of 'groupSize' teams from highest ranked down
    while (pq.size() > 0) {
        Array<Team*> group;

        for (int i = 0; i < groupSize && !pq.isEmpty(); ++i) {
            group.push(pq.extractTop());
        }

        // Step 3: Create match from group
        if (group.size() > 0) {
            Match match(matchCounter++, group, GROUP);
            groupMatches.push(match);
        }
    }
}

// Schedule Semifinal Matches (2 teams per match)
void MatchScheduler::scheduleSemifinals(Array<Team*>& groupWinners) {
    for (int i = 0; i < groupWinners.size(); i += 2) {
        Array<Team*> pair;
        if (i + 1 < groupWinners.size()) {
            pair.push(groupWinners[i]);
            pair.push(groupWinners[i + 1]);
        } else {
            pair.push(groupWinners[i]);
        }
        Match match(matchCounter++, pair, SEMIFINAL);
        semifinalMatches.push(match);
    }
}

// Schedule Final Match (2 teams only)
void MatchScheduler::scheduleFinal(Array<Team*>& semifinalWinners) {
    if (semifinalWinners.size() >= 2) {
        Array<Team*> finalists;
        finalists.push(semifinalWinners[0]);
        finalists.push(semifinalWinners[1]);
        Match match(matchCounter++, finalists, FINAL);
        finalMatches.push(match);
    }
}

// Play all matches in a given stage
void MatchScheduler::playMatches(Array<Match>& matches) {
    for (int i = 0; i < matches.size(); ++i) {
        matches[i].simulateMatch();
    }
}

// Display all matches in a given stage
void MatchScheduler::displayMatches(const Array<Match>& matches) const {
    for (int i = 0; i < matches.size(); ++i) {
        matches[i].display();
        std::cout << "--------------------------\n";
    }
}

// Get winners from a list of matches
Array<Team*> MatchScheduler::getWinners(const Array<Match>& matches) const {
    Array<Team*> winners;
    for (int i = 0; i < matches.size(); ++i) {
        if (matches[i].getWinner() != nullptr) {
            winners.push(matches[i].getWinner());
        }
    }
    return winners;
}

const Array<Match>& MatchScheduler::getQualifierMatches() const {
    return qualifierMatches;
}
const Array<Match>& MatchScheduler::getGroupMatches() const {
    return groupMatches;
}
const Array<Match>& MatchScheduler::getSemifinalMatches() const {
    return semifinalMatches;
}
const Array<Match>& MatchScheduler::getFinalMatches() const {
    return finalMatches;
}

Array<Match>& MatchScheduler::getQualifierMatches() {
    return qualifierMatches;
}
Array<Match>& MatchScheduler::getGroupMatches() {
    return groupMatches;
}
Array<Match>& MatchScheduler::getSemifinalMatches() {
    return semifinalMatches;
}
Array<Match>& MatchScheduler::getFinalMatches() {
    return finalMatches;
}
