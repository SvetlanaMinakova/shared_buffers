//
// Created by svetlana on 24/03/2022.
//

#ifndef SHARED_BUFFERS_BUFFEREXCEPTION_H
#define SHARED_BUFFERS_BUFFEREXCEPTION_H

#include <iostream>
#include <exception>
#include <string>

struct BufferException: public std::exception {
protected:
    const char* message = "BufferException";
public:
    BufferException(const char* message){
        this->message = message;
    }
    const char * what () const noexcept override
    {
        return message;
    }
};


#endif //SHARED_BUFFERS_BUFFEREXCEPTION_H
