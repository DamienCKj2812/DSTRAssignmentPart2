#include "Spectator.hpp"

Spectator::Spectator(int id, const std::string& name, SpectatorType type)
    : spectatorID(id), name(name), type(type), hasStreamingSlot(false) {}

int Spectator::getSpectatorID() const {
    return spectatorID;
}

std::string Spectator::getName() const {
    return name;
}

SpectatorType Spectator::getType() const {
    return type;
}

bool Spectator::getHasStreamingSlot() const {
    return hasStreamingSlot;
}

void Spectator::setHasStreamingSlot(bool value) {
    hasStreamingSlot = value;
}

std::string Spectator::getTypeAsString() const {
    switch (type) {
        case VIP: return "VIP";
        case STREAMER: return "Streamer";
        case GENERAL: return "General Audience";
        default: return "Unknown";
    }
}

void Spectator::display() const {
    std::cout << "Spectator ID: " << spectatorID << "\n"
              << "Name: " << name << "\n"
              << "Type: " << getTypeAsString() << std::endl;
}
