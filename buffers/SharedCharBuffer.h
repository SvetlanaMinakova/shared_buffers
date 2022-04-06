//
// Created by svetlana on 23/03/2022.
//

#ifndef SHARED_BUFFERS_SHAREDCHARBUFFER_H
#define SHARED_BUFFERS_SHAREDCHARBUFFER_H

#include <string>
#include <memory>
#include <vector>
#include <shared_mutex>
#include "SharedBuffer.h"

class SharedCharBuffer: public SharedBuffer{
    /**A char buffer that can by used by multiple processes
     * The buffer uses lock mechanism as proposed in
     * // https://riptutorial.com/cplusplus/example/30186/object-locking-for-efficient-access-
     * */
public:
    void Read(char* data_dst, int data_tokens, int start_token=0);
    void Write(char* new_data, int data_tokens);
    void PrintData() override;

    //constructor and destructor
    // required for DoubleSharedCharBuffer
    SharedCharBuffer(): SharedBuffer(){
        this->data = nullptr;
    };
    SharedCharBuffer(std::string name, int size): SharedBuffer(name, size){
        this->data = new char[size];
    }
    void init(std::string name, int size) override;
    ~SharedCharBuffer();

protected:
    char* data;
};


#endif //SHARED_BUFFERS_SHAREDCHARBUFFER_H
