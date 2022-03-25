//
// Created by svetlana on 23/03/2022.
//

#ifndef SHARED_BUFFERS_MYPROCESS_H
#define SHARED_BUFFERS_MYPROCESS_H
#include <string>
#include "SharedCharBuffer.h"
#include "vector"
#include <condition_variable>

class MyProcess {
public:
    // mutex types aliases, given for code readability and maintainability
    using mutex_type = std::shared_timed_mutex;
    using reading_lock = std::shared_lock<mutex_type>;
    using updates_lock = std::unique_lock<mutex_type>;

    std::string name;
    int execDelay;
    int runs;

    void SayHi() const;

    void exec() const;
    void read();
    void write();

    void addInputBufferPtr(SharedCharBuffer* ptr);
    void addOutputBufferPtr(SharedCharBuffer* ptr);
    bool inputDataAvailable();
    bool outputDataAvailable();
    int productionRate = 1;
    int consumptionRate = 1;

    // main function executed in a thread
    void main(void *par);

    // constructor and destructor
    explicit MyProcess(std::string name, int runs=1, int execTime=0);


    // This returns a scoped lock that is excluding to one
    // writer preventing any readers
    [[nodiscard]]
    updates_lock lock_data_waiter() { return updates_lock(dataWaiter); }

protected:
    std::vector<SharedCharBuffer*> inputBufferPtrs;
    std::vector<SharedCharBuffer*> outputBufferPtrs;
    // mutable allows const objects to be locked
    mutable mutex_type dataWaiter;
    std::condition_variable_any cv;
};


#endif //SHARED_BUFFERS_MYPROCESS_H
