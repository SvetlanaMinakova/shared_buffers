//
// Created by svetlana on 23/03/2022.
//

#include "MyProcess.h"
#include <string>
#include <utility>
#include <iostream>
#include "types.h"
#include <chrono>
#include <thread>

void MyProcess::SayHi() const{
    std::cout<<"Hi, I am "<< this->name<<std::endl;
}

MyProcess::MyProcess(std::string name, int runs, int execTime) {
    this->name = std::move(name);
    this->runs = runs;
    this->execTime = execTime;
}

void MyProcess::exec(){
    int execTimeMS = execTime * 1000;
    std::this_thread::sleep_for(std::chrono::milliseconds(execTimeMS));
    SayHi();
}

/** INFERENCE HERE **/
void MyProcess::main(void *vpar) {
    for(int run =0; run < runs; run++){
        //read

        //execute
        exec();

        //write
    }
}
