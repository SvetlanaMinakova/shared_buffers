//
// Created by svetlana on 01/04/2022.
//

#include "DoubleSharedCharBuffer.h"
#include <string>
#include <iostream>

DoubleSharedCharBuffer::DoubleSharedCharBuffer(std::string name, int size) {
    this->name = name;
    std::string topName = name + "1";
    std::string bottomName = name + "2";
    buf1.init(topName, size);
    buf2.init(bottomName,size);
    topPtr = &buf1;
    bottomPtr = &buf2;
}

void DoubleSharedCharBuffer::Read(int data_tokens, int start_token) {
    // lock bottom for reading
    auto bufLock = bottomPtr->lock_for_reading();
    bottomPtr->Read(data_tokens, start_token);
}

void DoubleSharedCharBuffer::Read(char *data_dst, int data_tokens, int start_token) {
    // lock bottom for reading
    // Here or in proc??
    auto bufLock = bottomPtr->lock_for_reading();
    bottomPtr->Read(data_dst, data_tokens, start_token);
}

void DoubleSharedCharBuffer::Write(char *new_data, int data_tokens) {
    // lock top for writing
    // Here or in proc??
    auto bufLock = topPtr->lock_for_updates();
    topPtr->Write(new_data, data_tokens);
}

void DoubleSharedCharBuffer::Write(int data_tokens) {
    // lock top for writing
    // Here or in proc??
    auto bufLock = topPtr->lock_for_updates();
    topPtr->Write(data_tokens);
}

void DoubleSharedCharBuffer::Swap() {
    // The whole object should be locked before this
    SharedCharBuffer* tmpPtr = topPtr;
    topPtr = bottomPtr;
    bottomPtr = tmpPtr;
}

void DoubleSharedCharBuffer::PrintData() {
    std::cout<<"[";
    topPtr->PrintData();
    std::cout<<"][";
    bottomPtr->PrintData();
    std::cout<<"]";
}

int DoubleSharedCharBuffer::StoredBottomTokens() {
    return bottomPtr->StoredTokens();
}

void DoubleSharedCharBuffer::setTopVisited() {
    auto bufLock = topPtr->lock_for_updates();
    topPtr->MarkAsVisited();
}

void DoubleSharedCharBuffer::setTopUnvisited() {
    auto bufLock = topPtr->lock_for_updates();
    topPtr->MarkAsUnVisited();
}

void DoubleSharedCharBuffer::setBottomVisited() {
    auto bufLock = bottomPtr->lock_for_reading();
    bottomPtr->MarkAsVisited();
}

void DoubleSharedCharBuffer::setBottomUnvisited() {
    auto bufLock = bottomPtr->lock_for_reading();
    bottomPtr->MarkAsUnVisited();
}

bool DoubleSharedCharBuffer::IsTopEmpty() {
    return topPtr->IsEmpty();
}

bool DoubleSharedCharBuffer::IsTopVisited() {
    return topPtr->IsVisited();
}

bool DoubleSharedCharBuffer::IsBottomVisited() {
    return bottomPtr->IsVisited();
}

bool DoubleSharedCharBuffer::ReadyForSwap() {
    return topPtr->IsVisited() && bottomPtr->IsVisited();
}




