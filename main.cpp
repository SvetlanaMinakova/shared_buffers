#include <iostream>
#include <string>
#include "types.h"
#include "example_apps/SimpleExamples.h"

/*********************/
/** Main */

int main() {
    //run simple examples
    // SimpleExamples::allocateBufferToOneProc();
    SimpleExamples::allocateBufferToTwoProc();
    // SimpleExamples::runProcessesInThreads();
    // SimpleExamples::readAndWriteToSharedCharBuffer();
    return 0;
}