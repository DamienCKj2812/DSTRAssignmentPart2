#ifndef SPECTATOR_HPP
#define SPECTATOR_HPP

#include <iostream>
#include <string>


enum SpectatorType {
    VIP = 1,        // Highest Priority
    STREAMER = 2,   // Medium Priority
	GENERAL = 3     // Lowest Priority
};

class Spectator {
protected:
    int spectatorID;
    std::string name;
    SpectatorType type; 

public:
    Spectator(int id, const std::string& name, SpectatorType type);

    // Getters
    int getSpectatorID() const;
    std::string getName() const;
    SpectatorType getType() const;

    // Utility
    std::string getTypeAsString() const;
    virtual void display() const;
    virtual ~Spectator() {}
};

#endif
