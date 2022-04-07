//
// Created by svetlana on 07/04/2022.
//

#include "NumAveragerSB.h"
#include "NumArrayGeneratorSB.h"
#include "NumArrayAveragerSB.h"
#include <iostream>

int NumAveragerSB::run() {
    std::cout<<"Run num averager (single buffer)"<<std::endl;
    // init
    generator.init();
    averager.init();
    generator.addOutputBufferPtr(&buffer);
    averager.addInputBufferPtr(&buffer);

    // run
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
    std::thread my_thread0(&NumArrayGeneratorSB::main, &generator, &threadInfo[0]);
    std::thread my_thread1(&NumArrayAveragerSB::main, &averager, &threadInfo[1]);

    //join posix threads
    my_thread0.join();
    my_thread1.join();

    // delete pthread parameters
    free(threadInfo);

    return 0;
}