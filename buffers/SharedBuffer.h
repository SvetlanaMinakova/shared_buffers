//
// Created by svetlana on 06/04/2022.
//

#ifndef SHARED_BUFFERS_SHAREDBUFFER_H
#define SHARED_BUFFERS_SHAREDBUFFER_H

#include <string>
#include <memory>
#include <vector>
#include <shared_mutex>

class SharedBuffer {
public:
    // attributes
    // buffer size (in tokens), i.e., maximum amount of data
    // elements that can be stored in buffers
    int size;
    std::string name;
    // mutex types aliases, given for code readability and maintainability
    using mutex_type = std::shared_timed_mutex;
    using reading_lock = std::shared_lock<mutex_type>;
    using updates_lock = std::unique_lock<mutex_type>;

    // synchronization (mutexes)
    // This returns a scoped lock that can be shared by multiple
    // readers at the same time while excluding any writers
    [[nodiscard]]
    reading_lock lock_for_reading() const { return reading_lock(mtx); }

    // This returns a scoped lock that is excluding to one
    // writer preventing any readers
    [[nodiscard]]
    updates_lock lock_for_updates() { return updates_lock(mtx); }

    // read and write simulation functions
    // these functions do not work with actual memory,
    // but change the buffer tokens counter as if data was read/written
    // from/to the buffer
    virtual void ReadSim(int data_tokens, int start_token=0);
    virtual void WriteSim(int data_tokens);
    // abstract data print function
    virtual void PrintData()=0;

    // general checks and flags
    bool IsEmpty();
    bool IsFull();
    int StoredTokens();
    int FreeTokens();
    bool IsVisited();
    void MarkAsVisited();
    void MarkAsUnVisited();

    // constructor and destructor
    //constructor and destructor
    SharedBuffer();
    SharedBuffer(std::string name, int size);
    virtual void init(std::string name, int size);

protected:
    // number of currently stored data tokens
    int tokens = 0;
    bool visited = false;
    mutable mutex_type mtx; // mutable allows const objects to be locked
};


#endif //SHARED_BUFFERS_SHAREDBUFFER_H
