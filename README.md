### Shared buffers
This is my little project, where I study parallel processing and [mutex](https://en.wikipedia.org/wiki/Lock_(computer_science)) -based synchronization.
I implement parallel processes, that are executed on different CPUs, within different parallel [threads](https://en.wikipedia.org/wiki/Pthreads).
The processes communicate data through shared areas of memory, also referred as [buffers](https://en.wikipedia.org/wiki/Data_buffer). 

In my project I use my own implementation of process (see *MyProcess class*). This is a classical [dataflow](https://en.wikipedia.org/wiki/Dataflow) process, which operates using following primitives:
* *read* data from input buffer(s)
* *execute* a piece of code, possibly processing the input data
* *write* results into output buffer(s)

Every primitive action can be *delayed*. Delaying the primitives enables to study difference in time, required by a process to perform
reading/writing to/from certain type of buffer.

I also use custom implementations of buffers (see ./buffers folder). Currently, following types of buffers are implemented:
* *SharedCharBuffer*: a simple shared buffer, where data is an array of characters.
* *SharedCharDoubleBuffer* a [double-buffer] (https://en.wikipedia.org/wiki/Multiple_buffering) version of the *SharedCharBuffer*

My project has several illustrative examples, located in  *../example_apps*.

