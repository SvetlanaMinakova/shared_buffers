//
// Created by svetlana on 29/03/2022.
//

#ifndef SHARED_BUFFERS_ANTRANSLATOR_H
#define SHARED_BUFFERS_ANTRANSLATOR_H

#include <map>
#include <string>

class ANTranslator {
public:
    int run();
    void printAnimals();

protected:
    const std::map<std::string, std::string> animalNames = {{"Cat", "Kat"},
                                                            {"Dog","Hond"}};
};


#endif //SHARED_BUFFERS_ANTRANSLATOR_H
