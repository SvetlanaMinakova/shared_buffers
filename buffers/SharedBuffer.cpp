//
// Created by svetlana on 06/04/2022.
//

#include "SharedBuffer.h"
#include "BufferException.h"

SharedBuffer::SharedBuffer(std::string name, int size){
    this->name=std::move(name);
    this->size=size;
}

// required for DoubleSharedBufferT
SharedBuffer::SharedBuffer() {
    this->name = "none";
    this->size = 0;
}

void SharedBuffer::init(std::string name, int size) {
    this->name=std::move(name);
    this->size=size;
}

void SharedBuffer::ReadSim(int data_tokens, int start_token){
    if ((start_token + data_tokens) >= size)
        throw BufferException("Cannot read from buffer: out of boundaries!");
    this->tokens -= data_tokens;
}

void SharedBuffer::WriteSim(int data_tokens) {
    if (FreeTokens() < data_tokens)
        throw BufferException("Cannot write to buffer: not enough free space!");
    this->tokens += data_tokens;
}

bool SharedBuffer::IsFull() {
    bool full = this->tokens >= this->size;
    return full;
}

bool SharedBuffer::IsEmpty() {
    bool empty = this->tokens == 0;
    return empty;
}

int SharedBuffer::StoredTokens() {
    return this->tokens;
}

int SharedBuffer::FreeTokens(){
    return this->size - this->tokens;
}

void SharedBuffer::MarkAsVisited() {
    visited = true;
}

void SharedBuffer::MarkAsUnVisited() {
    visited = false;
}

bool SharedBuffer::IsVisited() {
    return visited;
}
