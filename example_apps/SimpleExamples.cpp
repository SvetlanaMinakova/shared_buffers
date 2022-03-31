//
// Created by svetlana on 29/03/2022.
//

#include "SimpleExamples.h"

//
// Created by svetlana on 29/03/2022.
//

#include <iostream>
#include <string>
#include <thread>
#include "../MyProcess.h"
#include "../buffers/SharedCharBuffer.h"
#include "../types.h"
#include "../buffers/DoubleSharedCharBuffer.h"

/*********************/
/** Helper functions */

void SimpleExamples::printData(char* data, int tokens){
    for (int i=0;i<tokens;i++){
        char elem = data[i];
        std::cout << elem;
    }
}

/*********************/
/** Examples of use */

void SimpleExamples::createProcesses(){
    MyProcess elfo = MyProcess("Elfo");
    elfo.sayHi();
    MyProcess bean = MyProcess("Bean");
    bean.sayHi();
}

void SimpleExamples::runProcessesInThreads(){
    // create processes
    MyProcess elfo = MyProcess("Elfo",10, 1);
    MyProcess bean = MyProcess("Bean",5, 2);

    const int numProcesses = 2;
    int cpuCoreIds[numProcesses] = {1, 2};

    // create pthread parameters
    // allocate memory for pthread_create() arguments
    const int numThreads = numProcesses;
    auto *threadInfo = (struct ThreadInfo*)(calloc(numThreads, sizeof(struct ThreadInfo)));

    //  allocate CPU cores to processes
    for(int i = 0; i < numThreads; i++)
        threadInfo[i].core_id = cpuCoreIds[i];

    // run threads
    //Create and run posix threads
    std::thread my_thread0(&MyProcess::main, &elfo, &threadInfo[0]);
    std::thread my_thread1(&MyProcess::main, &bean, &threadInfo[1]);

    //join posix threads
    my_thread0.join();
    my_thread1.join();

    // delete pthread parameters
    // std::cout<<" - Pthread parameters destruction"<<std::endl;
    free(threadInfo);

}

void SimpleExamples::allocateBufferToOneProc(){
    // Create new shared buffer
    SharedCharBuffer sharedCharBuffer = SharedCharBuffer("BUF", 25);
    // tokens in buffer
    std::cout<<"Tokens in shared buffer: "<<sharedCharBuffer.StoredTokens()<<std::endl;

    // create process that writes to shared buffer
    MyProcess writer = MyProcess("Writer",10, 1, 2, 1);

    // allocate shared buffer to process
    writer.addOutputBufferPtr(&sharedCharBuffer);
    std::cout<<"Output buffers of process"<<writer.name<<std::endl;
    writer.printOutputBufferNames();

    // create pthread parameters
    // allocate memory for pthread_create() arguments
    int numThreads = 1;
    auto *threadInfo = (struct ThreadInfo*)(calloc(numThreads, sizeof(struct ThreadInfo)));
    //  allocate CPU cores to processes
    threadInfo[0].core_id = 0;

    // create and run posix threads
    std::thread writer_thread(&MyProcess::main, &writer, &threadInfo[0]);

    // join posix threads
    writer_thread.join();

    // tokens in buffer
    std::cout<<"Tokens in shared buffer: "<<sharedCharBuffer.StoredTokens()<<std::endl;

    // delete pthread parameters
    free(threadInfo);
}

void SimpleExamples::allocateBufferToTwoProc(){
    // Create new shared buffer
    SharedCharBuffer sharedCharBuffer = SharedCharBuffer("BUF", 25);
    // tokens in buffer
    std::cout<<"Tokens in shared buffer: "<<sharedCharBuffer.StoredTokens()<<std::endl;

    // create process that writes to shared buffer
    MyProcess writer = MyProcess("Writer",10, 2, 2, 1);
    //create process that reads from shared buffer
    MyProcess reader = MyProcess("Reader",5,1,1,4);

    // allocate shared buffer to processes
    writer.addOutputBufferPtr(&sharedCharBuffer);
    reader.addInputBufferPtr(&sharedCharBuffer);
    std::cout<<"Output buffers of process"<<writer.name<<std::endl;
    writer.printOutputBufferNames();
    std::cout<<"Input buffers of process"<<reader.name<<std::endl;
    reader.printInputBufferNames();

    // create pthread parameters
    // allocate memory for pthread_create() arguments
    int numThreads = 2;
    auto *threadInfo = (struct ThreadInfo*)(calloc(numThreads, sizeof(struct ThreadInfo)));
    //  allocate CPU cores to processes
    threadInfo[0].core_id = 0;
    threadInfo[1].core_id = 1;

    // create and run posix threads
    std::thread writer_thread(&MyProcess::main, &writer, &threadInfo[0]);
    std::thread reader_thread(&MyProcess::main, &reader, &threadInfo[1]);

    // join posix threads
    writer_thread.join();
    reader_thread.join();

    // tokens in buffer
    std::cout<<"Tokens in shared buffer: "<<sharedCharBuffer.StoredTokens()<<std::endl;

    // delete pthread parameters
    free(threadInfo);
}

void SimpleExamples::readAndWriteToSharedCharBuffer(){
    // Create new shared buffer
    SharedCharBuffer sharedCharBuffer = SharedCharBuffer("BUF", 25);

    // Write data
    char beer[] = {'B', 'e', 'e', 'r'};
    int beer_size = sizeof (beer);
    std::cout<<"Write data"<<std::endl;
    sharedCharBuffer.Write(beer, beer_size);
    sharedCharBuffer.PrintData();
    std::cout<<"Tokens stored: "<<sharedCharBuffer.StoredTokens()<<std::endl;
    std::cout<<"Free space (tokens): "<<sharedCharBuffer.FreeTokens()<<std::endl;

    char potatoe[] = {'P', 'o', 't', 'a', 't', 'o', 'e'};
    int potatoe_size = sizeof(potatoe);
    sharedCharBuffer.Write(potatoe, potatoe_size);
    sharedCharBuffer.PrintData();
    std::cout<<"Tokens stored: "<<sharedCharBuffer.StoredTokens()<<std::endl;
    std::cout<<"Free space (tokens): "<<sharedCharBuffer.FreeTokens()<<std::endl;
    std::cout<<std::endl;

    // Read data
    char beer_receiver[beer_size];
    std::cout<<"Read data. Start: 0, tokens: "<<beer_size<<std::endl;
    sharedCharBuffer.Read(beer_receiver, beer_size);
    printData(beer_receiver, beer_size);
    std::cout<<std::endl;

    char potatoe_receiver[potatoe_size];
    std::cout<<"Read data. Start: "<<beer_size<<", tokens: "<<potatoe_size<<std::endl;
    sharedCharBuffer.Read(potatoe_receiver, potatoe_size, beer_size);
    printData(potatoe_receiver, potatoe_size);
    std::cout<<std::endl;
}

void SimpleExamples::readAndWriteToDoubleSharedCharBuffer() {
    DoubleSharedCharBuffer dBuf = DoubleSharedCharBuffer("dBuf", 10);
    // Test data
    char beer[] = {'B', 'e', 'e', 'r'};
    int beer_size = sizeof (beer);
    char potatoe[] = {'P', 'o', 't', 'a', 't', 'o', 'e'};
    int potatoe_size = sizeof(potatoe);

    // Write data
    std::cout<<"Write data"<<std::endl;
    dBuf.Write(beer, beer_size);
    dBuf.PrintData();
    std::cout<<std::endl;

    std::cout<<"Swap buffers"<<std::endl;
    dBuf.Swap();
    dBuf.PrintData();
    std::cout<<std::endl;

    // Write second portion of data
    std::cout<<"Write data"<<std::endl;
    dBuf.Write(potatoe, potatoe_size);
    dBuf.PrintData();
    std::cout<<std::endl;

    // Read data
    std::cout<<"Read data"<<std::endl;
    int readTokens = dBuf.OccupiedBottomTokens();
    char tmp[readTokens];
    dBuf.Read(tmp, readTokens);
    dBuf.PrintData();
    std::cout<<"Data extracted: ";
    printData(tmp, readTokens);
    std::cout<<std::endl;
    std::cout<<std::endl;

    std::cout<<"Swap buffers"<<std::endl;
    dBuf.Swap();
    dBuf.PrintData();
    std::cout<<std::endl;

}
