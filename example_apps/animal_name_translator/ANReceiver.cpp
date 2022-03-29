//
// Created by svetlana on 29/03/2022.
//

#include "ANReceiver.h"
#include "AnimalNames.h"

bool ANReceiver::inputDataAvailable(){
    for (auto bufPtr:inputBufferPtrs){
        if (!bufPtr->IsEmpty())
            return false;
    }
    return true;
}