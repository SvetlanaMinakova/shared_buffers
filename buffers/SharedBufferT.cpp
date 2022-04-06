//
// Created by svetlana on 06/04/2022.
//

#include "SharedBufferT.h"
#include "BufferException.h"

template<class T>
void SharedBufferT<T>::init(std::string name, int size) {
    SharedBuffer::init(name, size);
    this->data = new T[size];
}

template<class T>
SharedBufferT<T>::~SharedBuffer() {
    delete [] this->data;
}

template<class T>
void SharedBufferT<T>::Write(T *new_data, int data_tokens) {
    if (FreeTokens() < data_tokens)
        throw BufferException("Cannot write to buffer: not enough free space!");

    for (int i=0; i<data_tokens; i++) {
        this->data[tokens+i] = new_data[i];
    }
    this->tokens += data_tokens;
}

template<class T>
void SharedBufferT<T>::Read(T *data_dst, int data_tokens, int start_token) {
    if ((start_token + data_tokens) >= size)
        throw BufferException("Cannot read from buffer: out of boundaries!");

    for (int i=0; i<data_tokens; i++) {
        data_dst[i] = this->data[start_token+i];
    }
    this->tokens -= data_tokens;
}

template<class T>
void SharedBufferT<T>::PrintData() {
    for (int i=0;i<this->tokens;i++){
        char elem = data[i];
        std::cout << elem;
    }
}