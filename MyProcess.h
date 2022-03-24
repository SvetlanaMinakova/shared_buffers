//
// Created by svetlana on 23/03/2022.
//

#ifndef SHARED_BUFFERS_MYPROCESS_H
#define SHARED_BUFFERS_MYPROCESS_H
#include <string>

class MyProcess {
public:
    std::string name;
    int execTime;
    int runs;

    void SayHi() const;
    void exec();
    void main(void *par);

    explicit MyProcess(std::string name, int runs=1, int execTime=0);
};


#endif //SHARED_BUFFERS_MYPROCESS_H
