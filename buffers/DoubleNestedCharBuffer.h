//
// Created by svetlana on 01/04/2022.
//

#ifndef SHARED_BUFFERS_DOUBLENESTEDCHARBUFFER_H
#define SHARED_BUFFERS_DOUBLENESTEDCHARBUFFER_H

#include <string>
#include <memory>
#include <vector>
#include <shared_mutex>
#include "SharedCharBuffer.h"
/**
 * THIS IS A NESTED IMPLEMENTATION OF DoubleSharedCharBuffer
 * DoubleSharedCharBuffer is a shared char* buffer,
 * which consists of two halves: a top half, and a bottom half
 * the top half is used for writing by the source process,
 * while the bottom part is (possibly simultaneously) used
 * by the destination process for reading. The source and destination
 * buffers can be swapped.
 */
class DoubleNestedCharBuffer {
public:
    DoubleNestedCharBuffer(std::string name, int size);
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
    // NOTE: only bottom half is used (and blocked) for writing
    [[nodiscard]]
    reading_lock lock_bottom_for_reading() const { return bottomPtr->lock_for_reading(); }

    // This returns a scoped lock that is excluding to one
    // writer preventing any readers
    // NOTE: only top half is used (and blocked) for writing
    [[nodiscard]]
    updates_lock lock_top_for_writing() { return topPtr->lock_for_updates();}

    // This returns a scoped lock that is excluding to one
    // writer preventing any readers to the WHOLE double-buffer object
    [[nodiscard]]
    updates_lock lock_for_updates() { return updates_lock(mtx); }

    void Read(int data_tokens, int start_token=0);
    void Read(char* data_dst, int data_tokens, int start_token=0);
    void Write(char* new_data, int data_tokens);
    void Write(int data_tokens);
    void Swap();
    void PrintData();
    int StoredBottomTokens();

    // manual sync flags
    void setTopVisited();
    void setTopUnvisited();
    void setBottomVisited();
    void setBottomUnvisited();
    bool IsTopEmpty();
    bool IsTopVisited();
    bool IsBottomVisited();

private:
    SharedCharBuffer* topPtr;
    SharedCharBuffer* bottomPtr;

    SharedCharBuffer buf1 = SharedCharBuffer();
    SharedCharBuffer buf2 = SharedCharBuffer();

    // mutex that locks the whole object
    // (mutable allows const objects to be locked)
    mutable mutex_type mtx;
};


#endif //SHARED_BUFFERS_DOUBLENESTEDCHARBUFFER_H
