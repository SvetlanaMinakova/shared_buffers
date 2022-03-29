//
// Created by svetlana on 29/03/2022.
//

#ifndef SHARED_BUFFERS_SIMPLEEXAMPLES_H
#define SHARED_BUFFERS_SIMPLEEXAMPLES_H


class SimpleExamples {
public:
    static void createProcesses();
    static void runProcessesInThreads();
    static void allocateBufferToOneProc();
    static void allocateBufferToTwoProc();
    static void readAndWriteToSharedCharBuffer();

protected:
    static void printData(char* data, int tokens);
};


#endif //SHARED_BUFFERS_SIMPLEEXAMPLES_H
