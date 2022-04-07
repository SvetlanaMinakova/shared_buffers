//
// Created by svetlana on 07/04/2022.
//

#ifndef SHARED_BUFFERS_KERNELSLIB_H
#define SHARED_BUFFERS_KERNELSLIB_H
// kernels from https://towardsdatascience.com/simple-introduction-to-convolutional-neural-networks-cdf8d3077bac
static float detectEdgesKernel[] = {-1,-1,-1,
                                    -1,8,-1,
                                    -1,-1,-1};

static float sharpenKernel[] = {0,-1,0,
                                    -1,5,-1,
                                    0,-1,0};
#endif //SHARED_BUFFERS_KERNELSLIB_H
