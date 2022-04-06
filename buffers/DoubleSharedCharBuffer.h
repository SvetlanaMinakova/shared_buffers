//
// Created by svetlana on 01/04/2022.
//

#ifndef SHARED_BUFFERS_DOUBLESHAREDCHARBUFFER_H
#define SHARED_BUFFERS_DOUBLESHAREDCHARBUFFER_H

#include <string>
#include <memory>
#include <vector>
#include <shared_mutex>
#include "SharedCharBuffer.h"
#include "SharedBuffer.h"
/**
 * DoubleSharedCharBuffer is a shared char* buffer,
 * which consists of two halves: a top half, and a bottom half
 * the top half is used for writing by the source process,
 * while the bottom part is (possibly simultaneously) used
 * by the destination process for reading. The source and destination
 * buffers can be swapped.
 */
class DoubleSharedCharBuffer: public SharedBuffer{
public:
    DoubleSharedCharBuffer(std::string name, int size): SharedBuffer(name, size){
        buf1.init("top", size);
        buf2.init("bottom",size);
        topPtr = &buf1;
        bottomPtr = &buf2;
    };

    void ReadSim(int data_tokens, int start_token=0) override;
    void WriteSim(int data_tokens) override;
    void Read(char* data_dst, int data_tokens, int start_token=0);
    void Write(char* new_data, int data_tokens);
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
    SharedCharBuffer* topPtr;
    SharedCharBuffer* bottomPtr;

    SharedCharBuffer buf1 = SharedCharBuffer();
    SharedCharBuffer buf2 = SharedCharBuffer();
};


#endif //SHARED_BUFFERS_DOUBLESHAREDCHARBUFFER_H
