#ifndef PLAYER_PRIORITY_QUEUE_HPP
#define PLAYER_PRIORITY_QUEUE_HPP

#include "Array.hpp"
#include "Player.hpp"
#include <iostream>

// Min-Heap by default (for Player: lower ranking = higher priority)
template<typename T>
class PlayerPriorityQueue {
private:
    Array<T> data;

    // Lower ranking value = higher priority
    bool isLowerPriority(const T& a, const T& b) {
        return a.getRanking() < b.getRanking(); 
    }

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (isLowerPriority(data.get(parent), data.get(index))) {
                break;
            }
            T temp = data.get(index);
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

			if (left < size && isLowerPriority(data.get(left), data.get(smallest))) {
				smallest = left;
			}
			if (right < size && isLowerPriority(data.get(right), data.get(smallest))) {
				smallest = right;
			}
            if (smallest != index) {
                T temp = data.get(index);
                data.set(index, data.get(smallest));
                data.set(smallest, temp);
                index = smallest;
            } else {
                break;
            }
        }
    }

public:
    void insert(const T& value) {
        data.push(value);
        heapifyUp(data.size() - 1);
    }

    T extractTop() {
        if (data.size() == 0) return T();
        T top = data.get(0);
        T last = data.pop();
        if (data.size() > 0) {
            data.set(0, last);
            heapifyDown(0);
        }
        return top;
    }

    T peek() const {
        if (data.size() == 0) return T();
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
        std::cout << "Heap contents (by ranking):\n";
        for (int i = 0; i < data.size(); ++i) {
            std::cout << " - " << data.get(i).getName()
                      << " (Rank: " << data.get(i).getRanking() << ")\n";
        }
    }
};

#endif
