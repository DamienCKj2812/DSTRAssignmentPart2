#ifndef SPECTATOR_HPP
#define SPECTATOR_HPP

#include <iostream>
#include <string>


enum SpectatorType {
    VIP = 1,
    STREAMER = 2,
    GENERAL = 3
};

class Spectator {
protected:
    int spectatorID;
    std::string name;
    SpectatorType type; // Using enum instead of string

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
