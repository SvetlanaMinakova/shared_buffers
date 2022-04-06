//
// Created by svetlana on 01/04/2022.
//

#ifndef SHARED_BUFFERS_DOUBLESHAREDBUFFER_H
#define SHARED_BUFFERS_DOUBLESHAREDBUFFER_H

#include <string>
#include <memory>
#include <vector>
#include <shared_mutex>
#include "SharedBuffer.h"
#include "SingleSharedBuffer.h"
#include <iostream>
/**
 * DoubleSharedBuffer is a shared char* buffer,
 * which consists of two halves: a top half, and a bottom half
 * the top half is used for writing by the source process,
 * while the bottom part is (possibly simultaneously) used
 * by the destination process for reading. The source and destination
 * buffers can be swapped.
 */

template <class T>
class DoubleSharedBuffer: public SharedBuffer{
public:
    DoubleSharedBuffer(std::string name, int size): SharedBuffer(name, size){
        buf1.init("top", size);
        buf2.init("bottom",size);
        topPtr = &buf1;
        bottomPtr = &buf2;
    };

    void ReadSim(int data_tokens, int start_token=0) override;
    void WriteSim(int data_tokens) override;
    void Read(T* data_dst, int data_tokens, int start_token=0);
    void Write(T* new_data, int data_tokens);
    void Swap();
    bool ReadyForSwap();
    void PrintData() override;
    int StoredBottomTokens();

    // manual sync flags
    void setTopVisited();
    void setTopUnvisited();
    void setBottomVisited();
    void setBottomUnvisited();
    bool IsTopEmpty();
    bool IsTopVisited();
    bool IsBottomVisited();

private:
    SingleSharedBuffer<T>* topPtr;
    SingleSharedBuffer<T>* bottomPtr;

    SingleSharedBuffer<T> buf1 = SingleSharedBuffer<T>();
    SingleSharedBuffer<T> buf2 = SingleSharedBuffer<T>();
};


template<class T>
void DoubleSharedBuffer<T>::Read(T *data_dst, int data_tokens, int start_token) {
    auto bufLock = bottomPtr->lock_for_reading();
    bottomPtr->Read(data_dst, data_tokens, start_token);
}

template<class T>
void DoubleSharedBuffer<T>::Write(T *new_data, int data_tokens) {
    // lock top for writing
    // Here or in proc??
    auto bufLock = topPtr->lock_for_updates();
    topPtr->Write(new_data, data_tokens);
}

template<class T>
void DoubleSharedBuffer<T>::ReadSim(int data_tokens, int start_token) {
    // lock bottom for reading
    auto bufLock = bottomPtr->lock_for_reading();
    bottomPtr->ReadSim(data_tokens, start_token);
}

template<class T>
void DoubleSharedBuffer<T>::WriteSim(int data_tokens) {
    // lock top for writing
    // Here or in proc??
    auto bufLock = topPtr->lock_for_updates();
    topPtr->WriteSim(data_tokens);
}

template<class T>
void DoubleSharedBuffer<T>::Swap() {
    // The whole object should be locked before this
    SingleSharedBuffer<T>* tmpPtr = topPtr;
    topPtr = bottomPtr;
    bottomPtr = tmpPtr;
}

template<class T>
void DoubleSharedBuffer<T>::PrintData() {
    std::cout<<"[";
    topPtr->PrintData();
    std::cout<<"][";
    bottomPtr->PrintData();
    std::cout<<"]";
}

template<class T>
int DoubleSharedBuffer<T>::StoredBottomTokens() {
    return bottomPtr->StoredTokens();
}

template<class T>
void DoubleSharedBuffer<T>::setTopVisited() {
    auto bufLock = topPtr->lock_for_updates();
    topPtr->MarkAsVisited();
}

template<class T>
void DoubleSharedBuffer<T>::setTopUnvisited() {
    auto bufLock = topPtr->lock_for_updates();
    topPtr->MarkAsUnVisited();
}

template<class T>
void DoubleSharedBuffer<T>::setBottomVisited() {
    auto bufLock = bottomPtr->lock_for_reading();
    bottomPtr->MarkAsVisited();
}

template<class T>
void DoubleSharedBuffer<T>::setBottomUnvisited() {
    auto bufLock = bottomPtr->lock_for_reading();
    bottomPtr->MarkAsUnVisited();
}

template<class T>
bool DoubleSharedBuffer<T>::IsTopEmpty() {
    return topPtr->IsEmpty();
}

template<class T>
bool DoubleSharedBuffer<T>::IsTopVisited() {
    return topPtr->IsVisited();
}

template<class T>
bool DoubleSharedBuffer<T>::IsBottomVisited() {
    return bottomPtr->IsVisited();
}

template<class T>
bool DoubleSharedBuffer<T>::ReadyForSwap() {
    return topPtr->IsVisited() && bottomPtr->IsVisited();
}


#endif //SHARED_BUFFERS_DOUBLESHAREDBUFFER_H
