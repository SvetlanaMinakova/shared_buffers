//
// Created by svetlana on 29/03/2022.
//

#include "ANTranslator.h"
#include <iostream>

void ANTranslator::printAnimals() {
    std::cout<<"[ ";
    for (auto &item: animalNames){
        std::cout << item.first << ":" << item.second << "; ";
    }
    std::cout<<"]"<<std::endl;
}
