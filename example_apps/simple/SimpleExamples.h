//
// Created by svetlana on 29/03/2022.
//

#ifndef SHARED_BUFFERS_SIMPLEEXAMPLES_H
#define SHARED_BUFFERS_SIMPLEEXAMPLES_H


class SimpleExamples {
public:
    // MyProcess
    static void createProcesses();
    static void runProcessesInThreads();

    // SharedCharBuffer
    static void allocateBufferToOneProc();
    static void allocateBufferToTwoProc();
    static void readAndWriteToSharedCharBuffer();
    static void createEmptySharedCharBuffer();

    // DoubleSharedCharBuffer
    static void readAndWriteToDoubleSharedCharBuffer();
    //DoubleNestedCharBuffer
    static void readAndWriteToDoubleNestedCharBuffer();


protected:
    static void printData(char* data, int tokens);
};


#endif //SHARED_BUFFERS_SIMPLEEXAMPLES_H
