//
// Created by svetlana on 01/04/2022.
//

#include "ANTranslatorSB.h"
#include "ANGeneratorSB.h"
#include "ANReceiverSB.h"
#include "../../../buffers/SharedBufferT.h"
#include <iostream>
#include <thread>
#include "../../../types.h"

int ANTranslatorSB::run(int runs, int execDelay, int rwDelay){
    // create generator and receiver processes
    ANGeneratorSB generator = ANGeneratorSB("generator", animalNames, runs, execDelay,rwDelay);
    ANReceiverSB receiver = ANReceiverSB("receiver", animalNames, runs,execDelay,rwDelay);
    // create and assign shared buffer
    SharedBufferT<char> sharedBuffer = SharedBufferT<char>("buffer", 10);
    generator.addOutputBufferPtr(&sharedBuffer);
    receiver.addInputBufferPtr(&sharedBuffer);

    // create pthread parameters
    // allocate memory for pthread_create() arguments
    int numProcesses = 2;
    const int numThreads = numProcesses;
    auto *threadInfo = (struct ThreadInfo*)(calloc(numThreads, sizeof(struct ThreadInfo)));

    //  allocate CPU cores to processes
    threadInfo[0].core_id = 0;
    threadInfo[1].core_id = 1;

    // run threads
    //Create and run posix threads
    std::thread my_thread0(&ANGeneratorSB::main, &generator, &threadInfo[0]);
    std::thread my_thread1(&ANReceiverSB::main, &receiver, &threadInfo[1]);

    //join posix threads
    my_thread0.join();
    my_thread1.join();

    // delete pthread parameters
    free(threadInfo);

    return 0;
}
