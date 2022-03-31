#include <iostream>
#include <string>
#include "types.h"
#include "example_apps/SimpleExamples.h"
#include "example_apps/animal_name_translator/ANTranslator.h"

/*********************/
/** Main */

int main() {
    //run simple examples
    // SimpleExamples::allocateBufferToOneProc();
    // SimpleExamples::allocateBufferToTwoProc();
    // SimpleExamples::runProcessesInThreads();
    // SimpleExamples::readAndWriteToSharedCharBuffer();

    SimpleExamples::readAndWriteToDoubleSharedCharBuffer();

    // run ANTranslator example
    /**
    ANTranslator app = ANTranslator();
    // app.printAnimals();
    app.run(2);
    */

    return 0;
}