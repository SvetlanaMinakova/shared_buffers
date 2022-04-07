//
// Created by svetlana on 07/04/2022.
//

#ifndef SHARED_BUFFERS_IMAGEWORKER_H
#define SHARED_BUFFERS_IMAGEWORKER_H


class ImageWorker {
public:
    static void initRandomCHW(float* image, int imC, int imH, int imW);
    static void initNaturalOrderCHW(float* image, int imC, int imH, int imW, int startValue=0);
    static void printCHW(float* image, int imC, int imH, int imW);
};


#endif //SHARED_BUFFERS_IMAGEWORKER_H
