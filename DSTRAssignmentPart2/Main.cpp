#include "Player.hpp"
#include "PlayerPriorityQueue.hpp"
#include <iostream>

int main() {
    PlayerPriorityQueue<Player> playerHeap;

    playerHeap.insert(Player(1, "Alice", 2, "APU", EARLY_BIRD));
    playerHeap.insert(Player(2, "Bob", 3, "UTM", REGULAR));
    playerHeap.insert(Player(3, "Charlie", 1, "UTAR", WILDCARD));
    playerHeap.insert(Player(4, "Charles", 5, "UTAR", WILDCARD));

    playerHeap.printHeap();

    std::cout << "Top Player:" << std::endl ;
    while (!playerHeap.isEmpty()) {
		Player curr = playerHeap.extractTop();
		curr.display();
        std::cout << "------------------------------------------------------------" << std::endl ; 
	}

    return 0;
}
