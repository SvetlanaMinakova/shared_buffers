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
#include "../../MyProcess.h"
#include "../../types.h"
#include "../../buffers/DoubleSharedBuffer.h"
#include "../../buffers/SingleSharedBuffer.h"

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
    MyProcess<char> elfo = MyProcess<char>("Elfo");
    elfo.sayHi();
    MyProcess<char> bean = MyProcess<char>("Bean");
    bean.sayHi();
}

void SimpleExamples::runProcessesInThreads(){
    // create processes
    MyProcess<char> elfo = MyProcess<char>("Elfo",10, 1);
    MyProcess<char> bean = MyProcess<char>("Bean",5, 2);

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
    std::thread my_thread0(&MyProcess<char>::main, &elfo, &threadInfo[0]);
    std::thread my_thread1(&MyProcess<char>::main, &bean, &threadInfo[1]);

    //join posix threads
    my_thread0.join();
    my_thread1.join();

    // delete pthread parameters
    // std::cout<<" - Pthread parameters destruction"<<std::endl;
    free(threadInfo);

}

void SimpleExamples::allocateBufferToOneProc(){
    // Create new shared buffer
    SingleSharedBuffer<char> sharedCharBuffer = SingleSharedBuffer<char>("BUF", 25);
    // tokens in buffer
    std::cout<<"Tokens in shared buffer: "<<sharedCharBuffer.StoredTokens()<<std::endl;

    // create process that writes to shared buffer
    MyProcess<char> writer = MyProcess<char>("Writer",10, 1, 2, 1);

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
    std::thread writer_thread(&MyProcess<char>::main, &writer, &threadInfo[0]);

    // join posix threads
    writer_thread.join();

    // tokens in buffer
    std::cout<<"Tokens in shared buffer: "<<sharedCharBuffer.StoredTokens()<<std::endl;

    // delete pthread parameters
    free(threadInfo);
}

void SimpleExamples::allocateBufferToTwoProc(){
    // Create new shared buffer
    SingleSharedBuffer<char> sharedCharBuffer = SingleSharedBuffer<char>("BUF", 25);
    // tokens in buffer
    std::cout<<"Tokens in shared buffer: "<<sharedCharBuffer.StoredTokens()<<std::endl;

    // create process that writes to shared buffer
    MyProcess<char> writer = MyProcess<char>("Writer",10, 2, 2, 1);
    //create process that reads from shared buffer
    MyProcess reader = MyProcess<char>("Reader",5,1,1,4);

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
    std::thread writer_thread(&MyProcess<char>::main, &writer, &threadInfo[0]);
    std::thread reader_thread(&MyProcess<char>::main, &reader, &threadInfo[1]);

    // join posix threads
    writer_thread.join();
    reader_thread.join();

    // tokens in buffer
    std::cout<<"Tokens in shared buffer: "<<sharedCharBuffer.StoredTokens()<<std::endl;

    // delete pthread parameters
    free(threadInfo);
}

void SimpleExamples::readAndWriteToSharedTemplateBufferChar(){
    // Create new shared buffer
    SingleSharedBuffer<char> sharedCharBuffer = SingleSharedBuffer<char>("BUF", 25);

    // write data
    char beer[] = {'B', 'e', 'e', 'r'};
    int beer_size = sizeof (beer);
    std::cout<<"write data"<<std::endl;
    sharedCharBuffer.Write(beer, beer_size);
    sharedCharBuffer.PrintData();
    std::cout<<std::endl;
    std::cout<<"Tokens stored: "<<sharedCharBuffer.StoredTokens()<<std::endl;
    std::cout<<"Free space (tokens): "<<sharedCharBuffer.FreeTokens()<<std::endl;

    char potatoe[] = {'P', 'o', 't', 'a', 't', 'o', 'e'};
    int potatoe_size = sizeof(potatoe);
    sharedCharBuffer.Write(potatoe, potatoe_size);
    sharedCharBuffer.PrintData();
    std::cout<<std::endl;
    std::cout<<"Tokens stored: "<<sharedCharBuffer.StoredTokens()<<std::endl;
    std::cout<<"Free space (tokens): "<<sharedCharBuffer.FreeTokens()<<std::endl;
    std::cout<<std::endl;

    // read data
    char beer_receiver[beer_size];
    std::cout<<"read data. Start: 0, tokens: "<<beer_size<<std::endl;
    sharedCharBuffer.Read(beer_receiver, beer_size);
    printData(beer_receiver, beer_size);
    std::cout<<std::endl;

    char potatoe_receiver[potatoe_size];
    std::cout<<"read data. Start: "<<beer_size<<", tokens: "<<potatoe_size<<std::endl;
    sharedCharBuffer.Read(potatoe_receiver, potatoe_size, beer_size);
    printData(potatoe_receiver, potatoe_size);
    std::cout<<std::endl;
}

void SimpleExamples::readAndWriteToDoubleNestedCharBuffer() {
    DoubleSharedBuffer<char> dBuf = DoubleSharedBuffer<char>("dBuf", 10);
    // Test data
    char beer[] = {'B', 'e', 'e', 'r'};
    int beer_size = sizeof (beer);
    char potatoe[] = {'P', 'o', 't', 'a', 't', 'o', 'e'};
    int potatoe_size = sizeof(potatoe);

    // write data
    std::cout<<"write data"<<std::endl;
    dBuf.Write(beer, beer_size);
    dBuf.PrintData();
    std::cout<<std::endl;

    std::cout<<"Swap buffers"<<std::endl;
    dBuf.Swap();
    dBuf.PrintData();
    std::cout<<std::endl;

    // write second portion of data
    std::cout<<"write data"<<std::endl;
    dBuf.Write(potatoe, potatoe_size);
    dBuf.PrintData();
    std::cout<<std::endl;

    // read data
    std::cout<<"read data"<<std::endl;
    int readTokens = dBuf.StoredBottomTokens();
    char tmp[readTokens];
    dBuf.Read(tmp, readTokens);
    dBuf.PrintData();
    std::cout<<std::endl;
    std::cout<<"Data extracted: ";
    printData(tmp, readTokens);
    std::cout<<std::endl;

    std::cout<<"Swap buffers"<<std::endl;
    dBuf.Swap();
    dBuf.PrintData();
    std::cout<<std::endl;
}