#include <iostream>
#include <string>
#include "types.h"
#include "example_apps/simple/SimpleExamples.h"
#include "example_apps/animal_name_translator/single_buf/ANTranslatorSB.h"
#include "example_apps/animal_name_translator/double_buf/ANTranslatorDB.h"
#include "example_apps/animal_name_translator/comparison/ANComparison.h"
#include "example_apps/num_averager/single_buffer/NumAveragerSB.h"
#include "example_apps/num_averager/double_buffer/NumAveragerDB.h"

/*********************/
/** Main */

int main() {
    // ************************
    //run simple examples
    // SimpleExamples::allocateBufferToOneProc();
    // SimpleExamples::allocateBufferToTwoProc();
    // SimpleExamples::runProcessesInThreads();
    // SimpleExamples::readAndWriteToDoubleNestedCharBuffer();
    // SimpleExamples::readAndWriteToSharedTemplateBufferChar();

    // ************************
    // run ANTranslator example
    //parameters
    /**
   int runs = 10;
   int execDelayS = 0;
   int rwDelayS = 1;
   */
    // single-buffer
   /**
   ANTranslatorSB appSB = ANTranslatorSB();
   // app.printAnimals();
   appSB.run(runs, execDelayS, rwDelayS);
    */
    // double-buffer
    /**
    ANTranslatorDB app = ANTranslatorDB();
    // app.printAnimals();
    app.run(runs, execDelayS, rwDelayS);
     */

    // comparison
    //ANComparison::compareTimeSingleAndDoubleBuf(runs, execDelayS, rwDelayS);

    // ************************
    // run NumAverager example

    int arrayLen = 10;
    int runs = 10;
    int execDelayS = 0;
    int rwDelayS = 1;

    //single buffer
    NumAveragerSB numAveragerSB = NumAveragerSB(arrayLen,runs,execDelayS,rwDelayS);
    numAveragerSB.run();
    std::cout<<std::endl<<"*************************"<<std::endl;

    //double buffer
    NumAveragerDB numAveragerDB = NumAveragerDB(arrayLen, runs,execDelayS,rwDelayS);
    numAveragerDB.run();

    return 0;
}