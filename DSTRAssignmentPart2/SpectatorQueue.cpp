#include "SpectatorQueue.hpp"

// ===============================
// SpectatorPriorityQueue Methods
// ===============================

// Add a new spectator to the heap and maintain the heap property
void SpectatorPriorityQueue::push(Spectator* s) {
    heap.push(s);
    heapifyUp(heap.size() - 1); // Restore heap upwards from the inserted node
}

// Remove and return the highest-priority spectator (root of heap)
Spectator* SpectatorPriorityQueue::pop() {
    if (heap.size() == 0) return nullptr;
    Spectator* top = heap[0];                           // Root element (highest priority)
    heap[0] = heap[heap.size() - 1];                    // Move last to root
    heap.pop();                                         // Remove last
    heapifyDown(0);                                     // Restore heap downwards
    return top;
}

// Return the number of spectators in the heap
int SpectatorPriorityQueue::size() const { return heap.size(); }

// Check if the heap is empty
bool SpectatorPriorityQueue::empty() const { return heap.size() == 0; }

// Index helper functions for heap navigation
int SpectatorPriorityQueue::parent(int i) const { return (i - 1) / 2; }
int SpectatorPriorityQueue::left(int i) const { return 2 * i + 1; }
int SpectatorPriorityQueue::right(int i) const { return 2 * i + 2; }

// After you add (push) a new spectator to the heap.
void SpectatorPriorityQueue::heapifyUp(int idx) {
    // While not at the root and the parent is a lower priority (larger enum value), swap up
    while (idx > 0 && heap[parent(idx)]->getType() > heap[idx]->getType()) {
        // Compares the new node with its parent.
        // If the new node has higher priority, it swaps them.
        // This repeats until the heap property is restored.
        Spectator* tmp = heap[idx];
        heap[idx] = heap[parent(idx)];
        heap[parent(idx)] = tmp;
        idx = parent(idx);
    }
}

// After you remove (pop) the top of the heap (seat allocation), and replace it with the last item.
void SpectatorPriorityQueue::heapifyDown(int idx) {
    int n = heap.size();
    while (true) {
        int l = left(idx), r = right(idx), smallest = idx;
        //Compares the new root with its children.
        //If a child has higher priority, it swaps with the smallest child.
        //This repeats until the heap property is restored.
        if (l < n && heap[l]->getType() < heap[smallest]->getType()) smallest = l;
        if (r < n && heap[r]->getType() < heap[smallest]->getType()) smallest = r;
        if (smallest == idx) break;
        // Swap current with smallest child
        Spectator* tmp = heap[idx];
        heap[idx] = heap[smallest];
        heap[smallest] = tmp;
        idx = smallest;
    }
}

// ===============================
// CircularQueue (Overflow) Methods
// ===============================

// Constructor initializes indices and empties the array
CircularQueue::CircularQueue() : front(0), rear(0), count(0) {
    for (int i = 0; i < MAX_OVERFLOW; ++i) arr[i] = nullptr;
}

// Adds a new spectator to the end (rear) of the overflow circular queue.
// Like people joining the end of a waiting line for tickets. 
// The queue wraps around to the start of the array if it reaches the end (circular buffer).
bool CircularQueue::enqueue(Spectator* s) {
    if (count == MAX_OVERFLOW) return false;         // Queue is full
    arr[rear] = s;                                   // Add to rear
    rear = (rear + 1) % MAX_OVERFLOW;                // Move rear forward (wrap around)
    ++count;                                         // Increment count
    return true;
}

// Removes and returns the spectator at the front of the overflow queue (the one waiting the longest).
// Like calling the next person forward from the front of the waiting line.
Spectator* CircularQueue::dequeue() {
    if (count == 0) return nullptr;                  // Queue is empty, returns nullptr.
    Spectator* s = arr[front];
    arr[front] = nullptr;                            // Remove pointer
    front = (front + 1) % MAX_OVERFLOW;              // Move front forward (wrap around)
    --count;                                         // Decrement count
    return s;
}

// Check if the queue is empty
bool CircularQueue::empty() const { return count == 0; }

// Get the number of spectators in the queue
int CircularQueue::size() const { return count; }

// ===============================
// StreamSlotQueue Methods
// ===============================

// Constructor initializes indices and empties the array
StreamSlotQueue::StreamSlotQueue() : front(0), rear(0), count(0) {
    for (int i = 0; i < MAX_STREAM_SLOTS; ++i) slots[i] = nullptr;
}

// Assign a streamer to the next available slot if not full
bool StreamSlotQueue::assignSlot(Spectator* s) {
    if (count == MAX_STREAM_SLOTS) return false;     // All slots in use
    slots[rear] = s;                                 // Assign to rear
    rear = (rear + 1) % MAX_STREAM_SLOTS;            // Move rear forward (wrap around)
    ++count;                                         // Increment count
    return true;
}

// Release (remove) a streamer from the front slot if not empty
Spectator* StreamSlotQueue::releaseSlot() {
    if (count == 0) return nullptr;                  // All slots empty
    Spectator* s = slots[front];
    slots[front] = nullptr;                          // Remove pointer
    front = (front + 1) % MAX_STREAM_SLOTS;          // Move front forward (wrap around)
    --count;                                         // Decrement count
    return s;
}

// Check if all slots are empty
bool StreamSlotQueue::empty() const { return count == 0; }

// Get the number of slots currently in use
int StreamSlotQueue::size() const { return count; }