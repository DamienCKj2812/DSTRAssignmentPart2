#ifndef SPECTATORQUEUE_HPP
#define SPECTATORQUEUE_HPP

#include "Spectator.hpp"
#include "Array.hpp"

// Constants for maximum sizes of various arrays/queues
const int MAX_SEATS = 10;           // Maximum number of seats in the viewing area
const int MAX_OVERFLOW = 10;        // Maximum number of spectators in overflow/waiting list
const int MAX_STREAM_SLOTS = 5;     // Maximum number of streaming slots

//------------------------------------
// Priority Queue (Heap-based) for Seat Assignment
//------------------------------------
// Manages spectators by priority: VIP > Influencer (Streamer) > General
// Implemented as a binary min-heap on SpectatorType (lower enum = higher priority)
class SpectatorPriorityQueue {
    Array<Spectator*> heap;   // Dynamic array to store heap elements
public:
    // Add a new spectator to the heap and maintain heap property
    void push(Spectator* s);

    // Remove and return the highest-priority spectator (VIPs first)
    Spectator* pop();

    // Return the current number of spectators in the heap
    int size() const;

    // Check if the heap is empty
    bool empty() const;

private:
    // Helper functions for heap navigation
    int parent(int i) const;   // Get parent index
    int left(int i) const;     // Get left child index
    int right(int i) const;    // Get right child index

    // Maintain heap property after insertion
    void heapifyUp(int idx);

    // Maintain heap property after removal
    void heapifyDown(int idx);
};

//------------------------------------
// Circular Queue for Overflow (Waiting List)
//------------------------------------
// Manages spectators who couldn't get a seat (FIFO order)
// Implemented as a fixed-size circular array
class CircularQueue {
    Spectator* arr[MAX_OVERFLOW]; // Array to hold pointers to waiting spectators
    int front, rear, count;       // Indices for front, rear, and current count
public:
    // Constructor initializes the queue
    CircularQueue();

    // Add a spectator to the rear of the queue
    bool enqueue(Spectator* s);

    // Remove and return a spectator from the front of the queue
    Spectator* dequeue();

    // Check if the queue is empty
    bool empty() const;

    // Return the number of spectators currently in the queue
    int size() const;
};

//------------------------------------
// Circular Queue for Stream Slot Management
//------------------------------------
// Manages allocation of fixed streaming slots for streamers/influencers (FIFO)
// Also implemented as a circular array
class StreamSlotQueue {
    Spectator* slots[MAX_STREAM_SLOTS]; // Array for assigned streamers
    int front, rear, count;             // Indices for front, rear, and current count
public:
    // Constructor initializes the queue
    StreamSlotQueue();

    // Assign a streamer to the next available slot (at the rear)
    bool assignSlot(Spectator* s);

    // Release (remove) a streamer from the front slot (when done streaming)
    Spectator* releaseSlot();

    // Check if all slots are empty
    bool empty() const;

    // Return the number of slots currently in use
    int size() const;
};

#endif // SPECTATORQUEUE_HPP

