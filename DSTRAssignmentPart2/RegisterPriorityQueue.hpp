#ifndef REGISPlayerER_PRIORIPlayerY_QUEUE_HPP
#define REGISPlayerER_PRIORIPlayerY_QUEUE_HPP

#include "Array.hpp"
#include "Player.hpp"
#include <iostream>

// Min-Heap by default (for Player: lower ranking = higher priority)
class RegisterPriorityQueue {
private:
    Array<Player> data;

    bool isLowerPriority(const Player& a, const Player& b) {
		return a.getRegistrationType() < b.getRegistrationType(); // lower enum value = higher priority
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (isLowerPriority(data.get(parent), data.get(index))) {
                break;
            }
            Player temp = data.get(index);
            data.set(index, data.get(parent));
            data.set(parent, temp);
            index = parent;
        }
    }

    void heapifyDown(int index) {
        int size = data.size();
        while (index * 2 + 1 < size) {
            int left = index * 2 + 1;
            int right = index * 2 + 2;
            int smallest = index;

            if (left < size && isLowerPriority(data.get(smallest), data.get(left))) {
                smallest = left;
            }
            if (right < size && isLowerPriority(data.get(smallest), data.get(right))) {
                smallest = right;
            }
            if (smallest != index) {
                Player temp = data.get(index);
                data.set(index, data.get(smallest));
                data.set(smallest, temp);
                index = smallest;
            } else {
                break;
            }
        }
    }

public:
    void insert(const Player& value) {
        data.push(value);
        heapifyUp(data.size() - 1);
    }

    Player extractTop() {
        if (data.size() == 0) return Player();
        Player top = data.get(0);
        Player last = data.pop();
        if (data.size() > 0) {
            data.set(0, last);
            heapifyDown(0);
        }
        return top;
    }

    Player peek() const {
        if (data.size() == 0) return Player();
        return data.get(0);
    }

    bool isEmpty() const {
        return data.size() == 0;
    }

    int size() const {
        return data.size();
    }

    // Debug: print heap content
    void printHeap() const {
        std::cout << "Heap contents (by register type):\n";
        for (int i = 0; i < data.size(); ++i) {
            std::cout << " - " << data.get(i).getName()
                      << " (Register Playerype: " << data.get(i).getRegTypeAsString() << ")\n";
        }
    }
};

#endif
