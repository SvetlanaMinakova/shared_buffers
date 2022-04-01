//
// Created by svetlana on 01/04/2022.
//

#ifndef SHARED_BUFFERS_ANTRANSLATORDB_H
#define SHARED_BUFFERS_ANTRANSLATORDB_H

#include "../ANTranslator.h"

class ANTranslatorDB: public ANTranslator{
public:
    int run(int runs) override;
};


#endif //SHARED_BUFFERS_ANTRANSLATORDB_H
