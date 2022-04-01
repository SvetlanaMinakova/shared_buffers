//
// Created by svetlana on 01/04/2022.
//

#ifndef SHARED_BUFFERS_ANTRANSLATORDBN_H
#define SHARED_BUFFERS_ANTRANSLATORDBN_H

#include "../ANTranslator.h"

class ANTranslatorDBN: public ANTranslator{
public:
    int run(int runs) override;
};


#endif //SHARED_BUFFERS_ANTRANSLATORDBN_H
