#ifndef MATCH_SCHEDULER_HPP
#define MATCHSCHEDULER_HPP

#include "Match.hpp"
#include "Array.hpp"

class MatchScheduler {
private:
    Array<Match> qualifierMatches;
    Array<Match> groupMatches;
    Array<Match> semifinalMatches;
    Array<Match> finalMatches;

    int matchCounter;

public:
    MatchScheduler();

    // Schedule functions
    void scheduleQualifierMatches(Array<Team*>& teams);
    void scheduleGroupStage(Array<Team*>& qualifiedTeams);
    void scheduleSemifinals(Array<Team*>& groupWinners);
    void scheduleFinal(Array<Team*>& semifinalWinners);

    // Run match simulations
    void playMatches(Array<Match>& matches);

    // Display results
    void displayMatches(const Array<Match>& matches) const;

    // Collect winners from a match array
    Array<Team*> getWinners(const Array<Match>& matches) const;


	const Array<Match>& getQualifierMatches() const;
	const Array<Match>& getGroupMatches() const;
	const Array<Match>& getSemifinalMatches() const;
	const Array<Match>& getFinalMatches() const;

	Array<Match>& getQualifierMatches();
	Array<Match>& getGroupMatches();
	Array<Match>& getSemifinalMatches();
	Array<Match>& getFinalMatches();
};

#endif
