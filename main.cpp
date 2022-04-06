#include <iostream>
#include <string>
#include "types.h"
#include "example_apps/simple/SimpleExamples.h"
#include "example_apps/animal_name_translator/single_buf/ANTranslatorSB.h"
#include "example_apps/animal_name_translator/double_buf/ANTranslatorDB.h"
#include "example_apps/animal_name_translator/comparison/ANComparison.h"

/*********************/
/** Main */

int main() {
    //run simple examples
    // SimpleExamples::allocateBufferToOneProc();
    // SimpleExamples::allocateBufferToTwoProc();
    // SimpleExamples::runProcessesInThreads();
    // SimpleExamples::readAndWriteToDoubleNestedCharBuffer();
    // SimpleExamples::readAndWriteToSharedTemplateBufferChar();

    // ************************
    // run ANTranslator example
    int runs = 10;
    int execDelayS = 0;
    int rwDelayS = 1;

    /**
    // single-buffer
    ANTranslatorSB appSB = ANTranslatorSB();
    // app.printAnimals();
    appSB.run(runs, execDelayS, rwDelayS);
     */

    /**
    // double-buffer
    ANTranslatorDB app = ANTranslatorDB();
    // app.printAnimals();
    app.run(runs, execDelayS, rwDelayS);
     */

    // comparison
    ANComparison::compareTimeSingleAndDoubleBuf(runs, execDelayS, rwDelayS);

    return 0;
}