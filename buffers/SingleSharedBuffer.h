//
// Created by svetlana on 06/04/2022.
//

#ifndef SHARED_BUFFERS_SINGLESHAREDBUFFER_H
#define SHARED_BUFFERS_SINGLESHAREDBUFFER_H

#include "SharedBuffer.h"
#include "BufferException.h"

template <class T>
class SingleSharedBuffer: public SharedBuffer{
public:
    // Typed methods
    void Read(T* data_dst, int data_tokens, int start_token=0);
    void Write(T* new_data, int data_tokens);
    void PrintData() override;

    // constructor and destructor
    SingleSharedBuffer(): SharedBuffer(){
        this->data = nullptr;
    };
    SingleSharedBuffer(std::string name, int size): SharedBuffer(name, size){
        this->data = new T[size];
    }
    ~SingleSharedBuffer();
    void init(std::string name, int size) override;

protected:
    T* data;
};

template<class T>
void SingleSharedBuffer<T>::init(std::string name, int size) {
    SharedBuffer::init(name, size);
    this->data = new T[size];
}

template<class T>
SingleSharedBuffer<T>::~SingleSharedBuffer() {
    delete [] this->data;
}

template<class T>
void SingleSharedBuffer<T>::Read(T *data_dst, int data_tokens, int start_token) {
    if ((start_token + data_tokens) >= size)
        throw BufferException("Cannot read from buffer: out of boundaries!");

    for (int i=0; i<data_tokens; i++) {
        data_dst[i] = this->data[start_token+i];
    }
    this->tokens -= data_tokens;
}

template<class T>
void SingleSharedBuffer<T>::Write(T *new_data, int data_tokens) {
    if (FreeTokens() < data_tokens)
        throw BufferException("Cannot write to buffer: not enough free space!");

    for (int i=0; i<data_tokens; i++) {
        this->data[tokens+i] = new_data[i];
    }
    this->tokens += data_tokens;
}

template<class T>
void SingleSharedBuffer<T>::PrintData() {
    for (int i=0;i<this->tokens;i++){
        char elem = data[i];
        std::cout << elem;
    }
}


#endif //SHARED_BUFFERS_SINGLESHAREDBUFFER_H
