#include <iostream>
#include <string>
#include "types.h"
#include "example_apps/simple/SimpleExamples.h"
#include "example_apps/animal_name_translator/single_buf/ANTranslatorSB.h"
#include "example_apps/animal_name_translator/double_buf/ANTranslatorDB.h"
#include "example_apps/animal_name_translator/double_buf_nested/ANTranslatorDBN.h"

/*********************/
/** Main */

int main() {
    //run simple examples
    // SimpleExamples::allocateBufferToOneProc();
    // SimpleExamples::allocateBufferToTwoProc();
    // SimpleExamples::runProcessesInThreads();
    // SimpleExamples::readAndWriteToSharedCharBuffer();

    // SimpleExamples::readAndWriteToDoubleSharedCharBuffer();
    // SimpleExamples::createEmptySharedCharBuffer();
    // SimpleExamples::readAndWriteToDoubleNestedCharBuffer();

    // run ANTranslator example
    /**
    // single-buffer
    ANTranslatorSB app = ANTranslatorSB();
    // app.printAnimals();
    app.run(2);
    */
    /**
    // double-buffer
    ANTranslatorDB app = ANTranslatorDB();
    // app.printAnimals();
    app.run(2);
     */
    
    // double-buffer (nested)
    ANTranslatorDBN app = ANTranslatorDBN();
    // app.printAnimals();
    app.run(2);

    return 0;
}