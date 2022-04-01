//
// Created by svetlana on 31/03/2022.
//

#ifndef SHARED_BUFFERS_DOUBLESHAREDCHARBUFFER_H
#define SHARED_BUFFERS_DOUBLESHAREDCHARBUFFER_H

#include <string>
#include <memory>
#include <vector>
#include <shared_mutex>
/**
 * DoubleSharedCharBuffer is a shared char* buffer,
 * which consists of two halves: a top half, and a bottom half
 * the top half is used for writing by the source process,
 * while the bottom part is (possibly simultaneously) used
 * by the destination process for reading. The source and destination
 * buffers can be swapped.
 */
class DoubleSharedCharBuffer {
public:
    // elements that can be stored in buffers
    int size;
    std::string name;
    // mutex types aliases, given for code readability and maintainability
    using mutex_type = std::shared_timed_mutex;
    using reading_lock = std::shared_lock<mutex_type>;
    using updates_lock = std::unique_lock<mutex_type>;

    void Read(int data_tokens, int start_token=0);
    void Read(char* data_dst, int data_tokens, int start_token=0);
    void Write(char* new_data, int data_tokens);
    void Write(int data_tokens);
    int FreeTopTokens();
    int OccupiedBottomTokens();
    void Swap(); // swap top and bottom
    void PrintData();

    // synchronization (mutexes)
    // This returns a scoped lock that can be shared by multiple
    // readers at the same time while excluding any writers
    [[nodiscard]]
    reading_lock lock_for_reading() const { return reading_lock(mtx); }

    // This returns a scoped lock that is excluding to one
    // writer preventing any readers
    [[nodiscard]]
    updates_lock lock_for_updates() { return updates_lock(mtx); }

    // constructor and destructor
    DoubleSharedCharBuffer(std::string name, int size);
    ~DoubleSharedCharBuffer();

private:
    // number of currently stored data tokens
    int topTokens = 0;
    int bottomTokens = 0;
    // top part of the buffer, to where a source process writes
    char* top;
    // bottom part of the buffer, from to where a destination process reads
    char* bottom;
    // mutex that locks the whole object
    // (mutable allows const objects to be locked)
    mutable mutex_type mtx;
};


#endif //SHARED_BUFFERS_DOUBLESHAREDCHARBUFFER_H
