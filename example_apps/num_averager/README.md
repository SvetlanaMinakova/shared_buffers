# Num Averager

An illustrative example of parallel processes data communication through a shared buffer. The example application has 
two processes, each defined as an object of a special class, inherited from *MyProcess* class:
* *generator* process (see *NumArrayGenerator* class and classes inherited from this class)
* *averager* process (see *NumArrayAverager* class and classes inherited from this class)

The *generator* and *averager* processes are executed in parallel, within two different pthreads, assigned to two different CPU cores.
While being executed, the processes communicate data through a common *SharedBuffer* as follows:
* the *generator* process generates a *float array of predetermined length*. The array contains float numbers, where each i-th number = i-th number + 0.1. If the *SharedBuffer* is available for writing, the *generator* process writes the generated float array into the *SharedBuffer*. Otherwise,  the *generator* process waits until the *SharedBuffer* is available for writing.
* the *averager* process waits until the *SharedBuffer* is full with data, i.e, when the *SharedBuffer* contains a *float array of predetermined length*. When the *SharedBuffer* is full and is available for reading, the *averager* process reads the numbers from the *SharedBuffer*, thereby emptying the buffer.
Then, the *averager* computes and average of *float array of predetermined length*, extracted from the *SharedBuffer*, and prints the array together with the average to console.

The access to the shared buffer is synchronized by means of mutexes (see https://en.cppreference.com/imW/cpp/thread/mutex).

The *float array of predetermined length* is a static array, which length is explicitly defined for a particular Num Averager example.

The example has two implementations that vary in type of *SharedBuffer* (see ./double_buf and ./single_buf sub-folders). The implementations vary in terms of:
* *SharedBuffer* implementation
* checks for buffer availability
* mutex-based synchronization