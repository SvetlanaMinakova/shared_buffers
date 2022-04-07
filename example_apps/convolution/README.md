# Convolution
**NOTE: example is unfinished!**
This example performs discrete convolution, simulating work of a Convolutional layers in a [Convolutional Neural Network](https://en.wikipedia.org/wiki/Convolutional_neural_network).
The example application has two processes, each defined as an object of a special class, inherited from *MyProcess* class:
* *dataLayer* process (see *DataLayer* class and classes inherited from this class)
* *convLayer* process (see *ConvLayer* class and classes inherited from this class)

The *dataLayer* process generates (float) input data array for *convLayer* process. The input data array is selected
from a predefined list, through which the *dataLayer* cycles during execution. The *convLayer* process applies discrete convolution to the input data array.
The data is exchanged through a *SharedBuffer*. The access to the *SharedBuffer* is synchronized by means of mutexes (see https://en.cppreference.com/imW/cpp/thread/mutex).