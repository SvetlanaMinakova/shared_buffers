//
// Created by svetlana on 01/04/2022.
//

#include "DoubleNestedCharBuffer.h"
#include <string>
#include <iostream>

DoubleNestedCharBuffer::DoubleNestedCharBuffer(std::string name, int size) {
    std::string topName = name + "1";
    std::string bottomName = name + "2";
    buf1.init(topName, size);
    buf2.init(bottomName,size);
    topPtr = &buf1;
    bottomPtr = &buf2;
}

void DoubleNestedCharBuffer::Read(int data_tokens, int start_token) {
    // lock bottom for reading
    auto bufLock = bottomPtr->lock_for_reading();
    bottomPtr->Read(data_tokens, start_token);
}

void DoubleNestedCharBuffer::Read(char *data_dst, int data_tokens, int start_token) {
    // lock bottom for reading
    // Here or in proc??
    auto bufLock = bottomPtr->lock_for_reading();
    bottomPtr->Read(data_dst, data_tokens, start_token);
}

void DoubleNestedCharBuffer::Write(char *new_data, int data_tokens) {
    // lock top for writing
    // Here or in proc??
    auto bufLock = topPtr->lock_for_updates();
    topPtr->Write(new_data, data_tokens);
}

void DoubleNestedCharBuffer::Write(int data_tokens) {
    // lock top for writing
    // Here or in proc??
    auto bufLock = topPtr->lock_for_updates();
    topPtr->Write(data_tokens);
}

void DoubleNestedCharBuffer::Swap() {
    // The whole object should be locked before this
    SharedCharBuffer* tmpPtr = topPtr;
    topPtr = bottomPtr;
    bottomPtr = tmpPtr;
}

void DoubleNestedCharBuffer::PrintData() {
    std::cout<<"[";
    topPtr->PrintData();
    std::cout<<"][";
    bottomPtr->PrintData();
    std::cout<<"]";
}

int DoubleNestedCharBuffer::StoredBottomTokens() {
    return bottomPtr->StoredTokens();
}

void DoubleNestedCharBuffer::setTopVisited() {
    auto bufLock = topPtr->lock_for_updates();
    topPtr->MarkAsVisited();
}

void DoubleNestedCharBuffer::setTopUnvisited() {
    auto bufLock = topPtr->lock_for_updates();
    topPtr->MarkAsUnVisited();
}

void DoubleNestedCharBuffer::setBottomVisited() {
    auto bufLock = bottomPtr->lock_for_reading();
    bottomPtr->MarkAsVisited();
}

void DoubleNestedCharBuffer::setBottomUnvisited() {
    auto bufLock = bottomPtr->lock_for_reading();
    bottomPtr->MarkAsUnVisited();
}

bool DoubleNestedCharBuffer::IsTopEmpty() {
    return topPtr->IsEmpty();
}

bool DoubleNestedCharBuffer::IsTopVisited() {
    return topPtr->IsVisited();
}

bool DoubleNestedCharBuffer::IsBottomVisited() {
    return bottomPtr->IsVisited();
}




