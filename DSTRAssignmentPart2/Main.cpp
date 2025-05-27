#include "MatchScheduler.hpp"
#include "TournamentRegistration.hpp"
#include "Player.hpp"
#include "Team.hpp"
#include "Array.hpp"
#include "Spectator.hpp"
#include "SpectatorQueue.hpp"

#include <iostream>
#include <string>
#include <cstdlib> 
#include <ctime>  
#include <chrono>
using namespace std::chrono;



// Task 3: Live Stream & Spectator Queue Management
void runSpectatorSystem() {
    // Priority queue (min-heap) for seat allocation, prioritizes VIPs/influencers
    SpectatorPriorityQueue seatQueue;

    // Circular queue for overflow/waiting list when seats are full
    CircularQueue overflowQueue;

    // Circular queue for assigning limited streaming slots
    StreamSlotQueue streamQueue;

    // Array to represent actual seats in the venue (store pointers to seated spectators)
    Spectator* seats[MAX_SEATS] = { nullptr };
    int seatCount = 0; // How many have been seated

    // --- Demo Input: Add All Arriving Spectators ---
    // Using your custom dynamic array class
    Array<Spectator*> arrivals;

    //Add spectators: some VIPs, some influencers, some general
    arrivals.push(new Spectator(1, "VIP_Alice", VIP));
    arrivals.push(new Spectator(2, "Gen_Bob", GENERAL));
    arrivals.push(new Spectator(3, "Influencer_Charlie", STREAMER));
    arrivals.push(new Spectator(4, "Gen_Dave", GENERAL));
    arrivals.push(new Spectator(5, "VIP_Eve", VIP));
    arrivals.push(new Spectator(6, "Gen_Frank", GENERAL));
    arrivals.push(new Spectator(7, "Streamer_Gina", STREAMER));
    arrivals.push(new Spectator(8, "Gen_Henry", GENERAL));
    arrivals.push(new Spectator(9, "VIP_Ivy", VIP));
    arrivals.push(new Spectator(10, "Gen_Jack", GENERAL));
    arrivals.push(new Spectator(11, "Streamer_Ken", STREAMER));
    arrivals.push(new Spectator(12, "Gen_Linda", GENERAL));
    arrivals.push(new Spectator(13, "Streamer_Mike", STREAMER));
    arrivals.push(new Spectator(14, "Streamer_Nina", STREAMER));
    arrivals.push(new Spectator(15, "Streamer_Omar", STREAMER));



    // --- Show Initial State (before sorting/prioritizing) ---
    std::cout << "\n--- Initial Spectator Arrivals ---\n";
    for (int i = 0; i < arrivals.size(); ++i) {
        std::cout << "Spectator " << i + 1 << ": ";
        arrivals[i]->display();
        std::cout << std::endl;
    }

    // --- Insert all spectators into the priority queue for seat allocation ---
    // This step simulates registration/check-in: everyone is "waiting for seat"
    for (int i = 0; i < arrivals.size(); ++i) {
        seatQueue.push(arrivals[i]);
    }

    // --- Measure seat allocation performance (time complexity) ---
    auto start = high_resolution_clock::now();

    // --- Seat Allocation (by priority) ---
    std::cout << "\n--- Seat Allocation ---\n";
    while (!seatQueue.empty()) {
        if (seatCount < MAX_SEATS) {
            // Take the highest-priority spectator and assign them to a seat
            seats[seatCount] = seatQueue.pop();
            std::cout << "Seat " << seatCount + 1 << ": ";
            seats[seatCount]->display();
            ++seatCount;
        }
        else {
            // Seats are full, so move spectator to overflow waiting list (FIFO)
            Spectator* s = seatQueue.pop();
            overflowQueue.enqueue(s);
            std::cout << "No seat available, added to overflow: ";
            s->display();
        }
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    std::cout << "\n[Performance] Seat allocation took " << duration.count() << " microseconds.\n";

    // --- Estimate memory usage for arrays and objects ---
    int totalSpectators = arrivals.size();
    int seatArraySize = MAX_SEATS;
    int overflowArraySize = MAX_OVERFLOW;
    int streamSlotArraySize = MAX_STREAM_SLOTS;

    size_t ptrSize = sizeof(Spectator*);
    size_t spectatorSize = sizeof(Spectator);

    std::cout << "\n[Memory Usage Estimate]" << std::endl;
    std::cout << "Total Spectator objects: " << totalSpectators << " (each ~" << spectatorSize << " bytes)" << std::endl;
    std::cout << "Seats array: " << seatArraySize << " pointers (each " << ptrSize << " bytes)" << std::endl;
    std::cout << "Overflow array: " << overflowArraySize << " pointers (each " << ptrSize << " bytes)" << std::endl;
    std::cout << "Stream slot array: " << streamSlotArraySize << " pointers (each " << ptrSize << " bytes)" << std::endl;
    std::cout << "Total estimated array memory: "
        << (seatArraySize + overflowArraySize + streamSlotArraySize) * ptrSize
        << " bytes\n";

    // --- Streaming Slot Assignment ---
    // Assign each streamer/influencer to a stream slot, if available
    std::cout << "\n--- Streaming Slot Assignment ---\n";
    for (int i = 0; i < seatCount; ++i) {
        if (seats[i]->getType() == STREAMER) {
            if (streamQueue.assignSlot(seats[i])) {
                std::cout << seats[i]->getName() << " assigned to stream slot.\n";
            }
            else {
                std::cout << seats[i]->getName() << " could not be assigned (slots full).\n";
            }
        }
    }

    // --- Simulate releasing a stream slot ---
    std::cout << "\n--- Releasing a Stream Slot ---\n";
    Spectator* released = streamQueue.releaseSlot();
    if (released) {
        std::cout << released->getName() << "'s slot is now free.\n";
    }

    // --- Demo: Simulate vacating seats, then fill from overflow ---
    std::cout << "\n--- Demo: Vacating Seats for Overflow ---\n";
    // Let's simulate 2 spectators leaving (seat 4 and seat 8, for example)
    int vacatedIndices[] = { 3, 7 }; // (Seat numbers 4 and 8, 0-based index)
    for (int i = 0; i < 2; ++i) {
        int idx = vacatedIndices[i];
        if (seats[idx] != nullptr) {
            std::cout << seats[idx]->getName() << " leaves Seat " << idx + 1 << ".\n";
            seats[idx] = nullptr;
            seatCount--;
        }
    }

    // Now fill seats from overflow!
    std::cout << "\n--- Filling Seats from Overflow ---\n";
    for (int i = 0; i < MAX_SEATS; ++i) {
        if (seats[i] == nullptr && !overflowQueue.empty()) {
            seats[i] = overflowQueue.dequeue();
            std::cout << "Seat " << i + 1 << ": (from overflow) ";
            seats[i]->display();
        }
    }

    //// --- Fill any remaining open seats from the overflow queue (FIFO) ---
    //std::cout << "\n--- Filling Seats from Overflow ---\n";
    //while (seatCount < MAX_SEATS && !overflowQueue.empty()) {
    //    seats[seatCount] = overflowQueue.dequeue();
    //    std::cout << "Seat " << seatCount + 1 << ": (from overflow) ";
    //    seats[seatCount]->display();
    //    ++seatCount;
    //}

    // --- Memory Cleanup (delete dynamically allocated spectators) ---
    for (int i = 0; i < arrivals.size(); ++i) delete arrivals[i];
}




Team createTeam(int teamID, const std::string& name, const std::string& university, RegistrationType type, int basePlayerID) {
    int randomRanking = std::rand() % 100 + 1; // range: 1 to 100

    Team team(teamID, name, randomRanking, university, type); // set ranking randomly

    for (int i = 0; i < 3; ++i) {
        Player p(basePlayerID + i, name + "_P" + std::to_string(i + 1));
        team.addPlayer(p);
    }

    return team;
}


void runTournamentSystem() {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // seed RNG
    TournamentRegistration registration;

    std::string universities[] = {
        "APU", "UM", "TARUC", "UPM", "UTAR", "USM",
        "UUM", "UKM", "UIA", "UNIMAS", "UMP", "MMU"
    };

    for (int i = 1; i <= 24; ++i) {
        RegistrationType type;
        if (i % 3 == 0) type = WILDCARD;
        else if (i % 3 == 1) type = EARLY_BIRD;
        else type = REGULAR;

        std::string name = "Team" + std::to_string(i);
        std::string uni = universities[(i - 1) % 12];
        registration.registerTeam(createTeam(i, name, uni, type, i * 10));
    }


    // Create a new team to replace an existing one (e.g. team ID 5)
    Team replacementTeam = createTeam(5, "ReplacementTeam", "XYZ University", WILDCARD, 1000);
    registration.replaceTeam(5, replacementTeam);

    // Replace a specific player inside team ID 3 (old player ID = 30, new player = ID 999)
    Player newPlayer(999, "Substitute_Player");
    registration.replacePlayerInTeam(3, 30, newPlayer);

    registration.moveToCheckInQueue();
    Array<Team> readyTeams = registration.processCheckIns(24);

    Array<Team*> teamPointers;
    for (int i = 0; i < readyTeams.size(); ++i) {
        teamPointers.push(&readyTeams[i]);  // Take address of each Team
    }


    MatchScheduler scheduler;

    scheduler.scheduleQualifierMatches(teamPointers);
    scheduler.playMatches(scheduler.getQualifierMatches());
    Array<Team*> qualified = scheduler.getWinners(scheduler.getQualifierMatches());
    std::cout << "\n=== Qualifier Matches ===\n";
    scheduler.displayMatches(scheduler.getQualifierMatches());

    scheduler.scheduleGroupStage(qualified);
    scheduler.playMatches(scheduler.getGroupMatches());
    Array<Team*> groupWinners = scheduler.getWinners(scheduler.getGroupMatches());
    std::cout << "\n=== Group Stage Matches ===\n";
    scheduler.displayMatches(scheduler.getGroupMatches());

    scheduler.scheduleSemifinals(groupWinners);
    scheduler.playMatches(scheduler.getSemifinalMatches());
    Array<Team*> semiWinners = scheduler.getWinners(scheduler.getSemifinalMatches());
    std::cout << "\n=== Semifinal Matches ===\n";
    scheduler.displayMatches(scheduler.getSemifinalMatches());

    scheduler.scheduleFinal(semiWinners);
    scheduler.playMatches(scheduler.getFinalMatches());
    Array<Team*> finalWinner = scheduler.getWinners(scheduler.getFinalMatches());
    std::cout << "\n=== Final Match ===\n";
    scheduler.displayMatches(scheduler.getFinalMatches());

    std::cout << "\nChampion: ";
    if (finalWinner.size() > 0) {
        std::cout << finalWinner[0]->getTeamName() << " from " << finalWinner[0]->getUniversity() << "!\n";
    }
    else {
        std::cout << "No winner determined.\n";
    }
}



int main() {
    int choice = 0;
    do {
        std::cout << "Select system to run:\n";
        std::cout << "1. Tournament/Team Management\n";
        std::cout << "2. Live Stream & Spectator Queue Management (Task 3)\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            runTournamentSystem();
        }
        else if (choice == 2) {
            runSpectatorSystem();
        }
        else {
            std::cout << "Invalid choice. Please try again.\n\n";
        }
    } while (choice != 1 && choice != 2);

    return 0;
}
