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
    /**A char buffer that can by used by multiple processes
     * The buffer uses lock mechanism as proposed in
     * // https://riptutorial.com/cplusplus/example/30186/object-locking-for-efficient-access-
     * */
public:
    // attributes
    int size;
    std::string name;
    // mutex types aliases, given for code readability and maintainability
    using mutex_type = std::shared_timed_mutex;
    using reading_lock = std::shared_lock<mutex_type>;
    using updates_lock = std::unique_lock<mutex_type>;

    //methods
    // This returns a scoped lock that can be shared by multiple
    // readers at the same time while excluding any writers
    [[nodiscard]]
    reading_lock lock_for_reading() const { return reading_lock(mtx); }

    // This returns a scoped lock that is excluding to one
    // writer preventing any readers
    [[nodiscard]]
    updates_lock lock_for_updates() { return updates_lock(mtx); }

    bool IsEmpty();
    bool IsFull();
    void Read(int data_tokens, int start_token=0);
    void Read(char* data_dst, int data_tokens, int start_token=0);
    void Write(char* new_data, int data_tokens);
    void Write(int data_tokens);
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
