#include "Team.hpp"

// Default constructor
Team::Team()
    : teamID(0), teamName("Unknown"), ranking(0),
      university("Unknown"), regType(REGULAR), playerCount(0) {}

// Parameterized constructor
Team::Team(int id, const std::string& name, int teamRanking,
           const std::string& uni, RegistrationType type)
    : teamID(id), teamName(name), ranking(teamRanking),
      university(uni), regType(type), playerCount(0) {}

// Getters

int Team::getTeamID() const { return teamID; }
std::string Team::getTeamName() const { return teamName; }
int Team::getRanking() const { return ranking; }
std::string Team::getUniversity() const { return university; }
RegistrationType Team::getRegistrationType() const { return regType; }
std::string Team::getRegTypeAsString() const {
    switch (regType) {
        case WILDCARD: return "Wildcard";
        case EARLY_BIRD: return "Early Bird";
        case REGULAR: return "Regular";
        default: return "Unknown";
    }
}
Array<Player>& Team::getPlayers() { return players; }

// Setters
void Team::setRanking(int newRanking) {
    ranking = newRanking;
}

// Add player (limit 3)
void Team::addPlayer(const Player& player) {
    if (playerCount < 3) {
        players.push(player);
        playerCount++;
    } else {
        std::cout << "Team already has maximum number of players (3)." << std::endl;
    }
}

// Display
void Team::display() const {
    std::cout << "Team ID     : " << teamID << std::endl;
    std::cout << "Team Name   : " << teamName << std::endl;
    std::cout << "Ranking     : " << ranking << std::endl;
    std::cout << "University  : " << university << std::endl;
    std::cout << "Reg Type    : " << getRegTypeAsString() << std::endl;
    std::cout << "Players (" << playerCount << "/3):" << std::endl;
    for (int i = 0; i < playerCount; ++i) {
        std::cout << "  Player " << (i + 1) << ":" << std::endl;
        players[i].display();
        std::cout << std::endl;
    }
}

int Team::getPlayerCount() const {
    return players.size(); 
}

Player& Team::getPlayer(int index) {
    return players.get(index); 
}

