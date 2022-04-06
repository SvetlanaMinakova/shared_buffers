//
// Created by svetlana on 06/04/2022.
//

#ifndef SHARED_BUFFERS_SHAREDBUFFERT_H
#define SHARED_BUFFERS_SHAREDBUFFERT_H

#include "SharedBuffer.h"
template <class T>
class SharedBufferT: public SharedBuffer{
    // Typed methods
    void Read(T* data_dst, int data_tokens, int start_token=0);
    void Write(T* new_data, int data_tokens);
    void PrintData() override;

    // constructor and destructor
    SharedBufferT(): SharedBuffer(){
        this->data = nullptr;
    };
    SharedBufferT(std::string name, int size): SharedBuffer(name, size){
        this->data = new T[size];
    }
    ~SharedBuffer();
    void init(std::string name, int size) override;

protected:
    T* data;
};


#endif //SHARED_BUFFERS_SHAREDBUFFERT_H
