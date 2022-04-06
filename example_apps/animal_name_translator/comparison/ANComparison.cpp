//
// Created by svetlana on 06/04/2022.
//

#include "ANComparison.h"
#include "../single_buf/ANTranslatorSB.h"
#include "../double_buf/ANTranslatorDB.h"
#include <iostream>
#include <chrono>

void ANComparison::compareTimeSingleAndDoubleBuf(int runs, int execDelayS, int rwDelayS) {
    clock_t start, end;

    // single-buffer
    std::cout<<"Compare time for Animal Name Translator using single and double SharedCharBuffer"<<std::endl;
    std::cout<<"Comparison parameters: app. runs = "<<runs<<", process execution delay (s): "<<execDelayS<<", read/write delay (s): "<<rwDelayS<<std::endl;

    std::cout<<"Run app with SINGLE BUFFER"<<std::endl;
    // create app
    ANTranslatorSB appSB = ANTranslatorSB();
    start = clock(); //start timer
    appSB.run(runs, execDelayS, rwDelayS); //run app
    end = clock();   //stop timer
    // compute delay
    float execTimeSB = ((float) (end - start))/CLOCKS_PER_SEC;

    std::cout<<std::endl;
    std::cout<<"***************************"<<std::endl;
    std::cout<<"Run app with DOUBLE BUFFER"<<std::endl;

    // create app
    ANTranslatorDB appDB = ANTranslatorDB();
    start = clock(); //start timer
    appDB.run(runs, execDelayS, rwDelayS); //run app
    end = clock();   //stop timer
    // compute delay
    float execTimeDB = ((float) (end - start))/CLOCKS_PER_SEC;

    printf ("exec time: %0.8f sec single buffer, %0.8f sec double buffer\n", execTimeSB, execTimeDB);
}
