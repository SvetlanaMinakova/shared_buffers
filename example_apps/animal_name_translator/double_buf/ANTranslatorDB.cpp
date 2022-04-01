//
// Created by svetlana on 01/04/2022.
//

#include "ANTranslatorDB.h"
#include "ANGeneratorDB.h"
#include "ANReceiverDB.h"
#include "../../../buffers/DoubleSharedCharBuffer.h"
#include <iostream>
#include <thread>
#include "../../../types.h"

int ANTranslatorDB::run(int runs){
// create generator and receiver processes
    ANGeneratorDB generator = ANGeneratorDB("generator", animalNames, runs, 1, 1, 1);
    ANReceiverDB receiver = ANReceiverDB("receiver", animalNames, runs,1,1,1);
    // create and assign shared buffer
    DoubleSharedCharBuffer  dBuf = DoubleSharedCharBuffer("buffer", 10);
    generator.addOutputBufferPtr(&dBuf);
    receiver.addInputBufferPtr(&dBuf);

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
    std::thread my_thread0(&ANGenerator::main, &generator, &threadInfo[0]);
    std::thread my_thread1(&MyProcess::main, &receiver, &threadInfo[1]);

    //join posix threads
    my_thread0.join();
    my_thread1.join();

    // delete pthread parameters
    free(threadInfo);

    return 0;
}