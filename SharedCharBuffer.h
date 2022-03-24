//
// Created by svetlana on 23/03/2022.
//

#ifndef SHARED_BUFFERS_SHAREDCHARBUFFER_H
#define SHARED_BUFFERS_SHAREDCHARBUFFER_H

#include <string>
#include <memory>
#include <vector>

class SharedCharBuffer {
public:
    // attributes
    int size;
    std::string src_proc_name;
    std::string dst_proc_name;

    //methods
    bool IsEmpty();
    bool IsFull();
    void Read(char* data_dst, int tokens, int start_token=0);
    void Write(char* new_data, int tokens);
    void PrintData();
    int StoredTokens();
    int FreeTokens();

    //constructor and destructor
    SharedCharBuffer(std::string src_proc_name, std::string dst_proc_name, int size);
    ~SharedCharBuffer();

private:
    // number of currently stored data tokens
    int tokens = 0;
    char* data;
};


#endif //SHARED_BUFFERS_SHAREDCHARBUFFER_H
