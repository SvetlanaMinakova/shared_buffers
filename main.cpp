#include <iostream>
#include <string>
#include "types.h"
#include "example_apps/SimpleExamples.h"
#include "example_apps/animal_name_translator/single_buf/ANTranslatorSB.h"

/*********************/
/** Main */

int main() {
    //run simple examples
    // SimpleExamples::allocateBufferToOneProc();
    // SimpleExamples::allocateBufferToTwoProc();
    // SimpleExamples::runProcessesInThreads();
    // SimpleExamples::readAndWriteToSharedCharBuffer();

    //SimpleExamples::readAndWriteToDoubleSharedCharBuffer();

    // run ANTranslator example

    ANTranslatorSB app = ANTranslatorSB();
    // app.printAnimals();
    app.run(2);


    return 0;
}