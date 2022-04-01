//
// Created by svetlana on 31/03/2022.
//

#include "DoubleSharedCharBuffer.h"
#include "BufferException.h"
#include <string>

DoubleSharedCharBuffer::DoubleSharedCharBuffer(std::string name, int size){
    this->name=std::move(name);
    this->size=size;
    this->top = new char[size];
    this->bottom = new char[size];
}

DoubleSharedCharBuffer::~DoubleSharedCharBuffer(){
    delete [] this->top;
    delete [] this->bottom;
}

int DoubleSharedCharBuffer::FreeTopTokens() {
    return this->size - this->topTokens;
}

int DoubleSharedCharBuffer::StoredBottomTokens(){
    return this->bottomTokens;
}

bool DoubleSharedCharBuffer::IsTopEmpty() {
    return topTokens==0;
}

bool DoubleSharedCharBuffer::IsBottomEmpty() {
    return bottomTokens==0;
}

void DoubleSharedCharBuffer::Read(char* data_dst, int data_tokens, int start_token) {
    if ((start_token + data_tokens) >= size)
        throw BufferException("Cannot read from buffer: out of boundaries!");

    for (int i=0; i<data_tokens; i++) {
        data_dst[i] = this->bottom[start_token + i];
    }
    this->bottomTokens -= data_tokens;
}

void DoubleSharedCharBuffer::Read(int data_tokens, int start_token){
    if ((start_token + data_tokens) >= size)
        throw BufferException("Cannot read from buffer: out of boundaries!");
    this->bottomTokens -= data_tokens;
}

void DoubleSharedCharBuffer::Write(char* new_data, int data_tokens) {
    if (FreeTopTokens() < data_tokens)
        throw BufferException("Cannot write to buffer: not enough free space!");

    for (int i=0; i<data_tokens; i++) {
        this->top[topTokens+i] = new_data[i];
    }
    this->topTokens += data_tokens;
}

void DoubleSharedCharBuffer::Write(int data_tokens) {
    if (FreeTopTokens() < data_tokens)
        throw BufferException("Cannot write to buffer: not enough free space!");
    this->topTokens += data_tokens;
}

void DoubleSharedCharBuffer::Swap() {
    // swap top and bottom memory pointers
    char *tmpBuf = top;
    top = bottom;
    bottom = tmpBuf;

    // swap top and bottom token Counters
    int tmpCounter = topTokens;
    topTokens = bottomTokens;
    bottomTokens = tmpCounter;
}

void DoubleSharedCharBuffer::PrintData(){
    std::cout << "[";
    for (int i=0;i<this->topTokens;i++){
        char elem = top[i];
        std::cout << elem;
    }
    std::cout << "][";
    for (int i=0;i<this->bottomTokens;i++){
        char elem = bottom[i];
        std::cout << elem;
    }
    std::cout<<"]"<<std::endl;
}

