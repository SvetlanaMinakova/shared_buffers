//
// Created by svetlana on 01/04/2022.
//

#include "ANTranslatorDBN.h"
#include "ANGeneratorDBN.h"
#include "ANReceiverDBN.h"
#include "../../../buffers/DoubleNestedCharBuffer.h"
#include <iostream>
#include <thread>
#include "../../../types.h"

int ANTranslatorDBN::run(int runs) {
    // create generator and receiver processes
    ANGeneratorDBN generator = ANGeneratorDBN("generator", animalNames, runs, 1, 1, 1);
    ANReceiverDBN receiver = ANReceiverDBN("receiver", animalNames, runs,1,1,1);
    // create and assign shared buffer
    DoubleNestedCharBuffer sharedBuffer = DoubleNestedCharBuffer("buffer", 10);
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
    std::thread my_thread0(&ANGenerator::main, &generator, &threadInfo[0]);
    std::thread my_thread1(&MyProcess::main, &receiver, &threadInfo[1]);

    //join posix threads
    my_thread0.join();
    my_thread1.join();

    // delete pthread parameters
    free(threadInfo);

    return 0;
}
