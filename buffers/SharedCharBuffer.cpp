//
// Created by svetlana on 23/03/2022.
//

#include "SharedCharBuffer.h"
#include <string>
#include <utility>
#include <iostream>
#include <vector>
#include <memory>
#include "BufferException.h"

SharedCharBuffer::SharedCharBuffer(std::string name, int size){
    this->name=std::move(name);
    this->size=size;
    this->data = new char[size];
}

SharedCharBuffer::~SharedCharBuffer(){
    delete [] this->data;
}

bool SharedCharBuffer::IsFull() {
    bool full = this->tokens >= this->size;
    return full;
}

bool SharedCharBuffer::IsEmpty() {
    bool empty = this->tokens == 0;
    return empty;
}

void SharedCharBuffer::Read(char* data_dst, int data_tokens, int start_token) {
    if ((start_token + data_tokens) >= size)
        throw BufferException("Cannot read from buffer: out of boundaries!");

    for (int i=0; i<data_tokens; i++) {
        data_dst[i] = this->data[start_token+i];
    }
    this->tokens -= data_tokens;
}

void SharedCharBuffer::Read(int data_tokens, int start_token){
    if ((start_token + data_tokens) >= size)
        throw BufferException("Cannot read from buffer: out of boundaries!");
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

void SharedCharBuffer::Write(int data_tokens) {
    if (FreeTokens() < data_tokens)
        throw BufferException("Cannot write to buffer: not enough free space!");
    this->tokens += data_tokens;
}

int SharedCharBuffer::StoredTokens() {
    return this->tokens;
}

int SharedCharBuffer::FreeTokens(){
    return this->size - this->tokens;
}

void SharedCharBuffer::PrintData(){
    for (int i=0;i<this->tokens;i++){
        char elem = data[i];
        std::cout << elem;
    }
    std::cout<<std::endl;
}