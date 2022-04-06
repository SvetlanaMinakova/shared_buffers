//
// Created by svetlana on 23/03/2022.
//

#include "SharedCharBuffer.h"
#include <string>
#include <utility>
#include <iostream>
#include <vector>
#include "BufferException.h"

// for post-initializing of SharedCharBuffer with empty constructor
void SharedCharBuffer::init(std::string bufName, int bufSize) {
    this->name=std::move(bufName);
    this->size=bufSize;
    delete [] this->data;
    this->data = new char[bufSize];
}

SharedCharBuffer::~SharedCharBuffer(){
    delete [] this->data;
}

void SharedCharBuffer::Read(char* data_dst, int data_tokens, int start_token) {
    if ((start_token + data_tokens) >= size)
        throw BufferException("Cannot read from buffer: out of boundaries!");

    for (int i=0; i<data_tokens; i++) {
        data_dst[i] = this->data[start_token+i];
    }
    this->tokens -= data_tokens;
}

void SharedCharBuffer::Write(char* new_data, int data_tokens) {
    if (FreeTokens() < data_tokens)
        throw BufferException("Cannot write to buffer: not enough free space!");

    for (int i=0; i<data_tokens; i++) {
        this->data[tokens+i] = new_data[i];
    }
    this->tokens += data_tokens;
}

void SharedCharBuffer::PrintData(){
    for (int i=0;i<this->tokens;i++){
        char elem = data[i];
        std::cout << elem;
    }
    //std::cout<<std::endl;
}



