//
// Created by svetlana on 23/03/2022.
//

#ifndef SHARED_BUFFERS_SHAREDCHARBUFFER_H
#define SHARED_BUFFERS_SHAREDCHARBUFFER_H

#include <string>
#include <memory>
#include <vector>
#include <shared_mutex>

class SharedCharBuffer {
public:
    // attributes
    int size;
    std::string name;
    // mutex primitives from tutorial on
    // https://riptutorial.com/cplusplus/example/30186/object-locking-for-efficient-access-
    using mutex_type = std::shared_timed_mutex;
    using reading_lock = std::shared_lock<mutex_type>;
    using updates_lock = std::unique_lock<mutex_type>;

    //methods
    bool IsEmpty();
    bool IsFull();
    void Read(char* data_dst, int tokens, int start_token=0);
    void Write(char* new_data, int tokens);
    void PrintData();
    int StoredTokens();
    int FreeTokens();

    //constructor and destructor
    SharedCharBuffer(std::string name, int size);
    ~SharedCharBuffer();

private:
    // number of currently stored data tokens
    int tokens = 0;
    char* data;
    mutable mutex_type mtx; // mutable allows const objects to be locked
};


#endif //SHARED_BUFFERS_SHAREDCHARBUFFER_H
