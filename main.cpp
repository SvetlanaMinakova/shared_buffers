#include <iostream>
#include <string>
#include "types.h"
#include "example_apps/simple/SimpleExamples.h"
#include "example_apps/animal_name_translator/single_buf/ANTranslatorSB.h"
#include "example_apps/animal_name_translator/double_buf/ANTranslatorDB.h"
#include "example_apps/animal_name_translator/comparison/ANComparison.h"
#include "example_apps/convolution/ConvExample.h"
#include "example_apps/num_averager/single_buffer/NumAveragerSB.h"
#include "example_apps/num_averager/single_buffer/NumArrayGeneratorSB.h"
#include "example_apps/num_averager/single_buffer/NumArrayAveragerSB.h"

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
    // run convolution example
    //ConvExample convExample = ConvExample(3,5,5,2,3,3,1,2,1,0);
    //convExample.run(3);
    //convExample.printImages();

    // ************************
    // run NumAveragerSB example
    NumAveragerSB numAveragerSB = NumAveragerSB(10,2,1,0);
    numAveragerSB.run();

    //NumArrayGeneratorSB generatorSb = NumArrayGeneratorSB(10,2,0,0);
    //NumArrayGeneratorSB generatorSb = NumArrayGeneratorSB(0,0,0,0);
    //NumArrayAveragerSB averagerSb = NumArrayAveragerSB(10,2,0,0);
    //NumArrayAveragerSB averagerSb = NumArrayAveragerSB(0,0,0,0);

    return 0;
}