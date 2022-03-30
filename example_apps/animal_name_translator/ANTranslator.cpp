//
// Created by svetlana on 29/03/2022.
//

#include "ANTranslator.h"
#include "ANGenerator.h"
#include "ANReceiver.h"
#include "../../SharedCharBuffer.h"
#include <iostream>
#include <thread>
#include "../../types.h"

int ANTranslator::run(int runs){
    // create generator and receiver processes
    ANGenerator generator = ANGenerator("generator", animalNames, runs, 1, 1, 1);
    ANReceiver receiver = ANReceiver("receiver", animalNames, runs,1,1,1);
    // create and assign shared buffer
    SharedCharBuffer sharedBuffer = SharedCharBuffer("buffer", 10);
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

void ANTranslator::printAnimals() {
    std::cout<<"[ ";
    for (auto &item: animalNames){
        std::cout << item.first << ":" << item.second << "; ";
    }
    std::cout<<"]"<<std::endl;
}
