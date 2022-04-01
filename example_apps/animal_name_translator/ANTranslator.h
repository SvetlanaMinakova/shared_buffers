//
// Created by svetlana on 29/03/2022.
//

#ifndef SHARED_BUFFERS_ANTRANSLATOR_H
#define SHARED_BUFFERS_ANTRANSLATOR_H

#include <map>
#include <string>

class ANTranslator {
public:
    // abstract function run represents specific application implementation
    virtual int run(int runs) = 0;
    void printAnimals();
    std::map<std::string, std::string> animalNames = {{"Cat", "Kat"},
                                                            {"Dog", "Hond"},
                                                            {"Fox","Vos"},
                                                            {"Horse","Paard"}};
};


#endif //SHARED_BUFFERS_ANTRANSLATOR_H
