# Animal Name Translator

An illustrative example of parallel processes data communication through a shared buffer. The example application has 
two processes, each defined as an object of a special class, inherited from *MyProcess* class:
* *generator* process (see *ANGenerator* class and classes inherited from this class)
* *receiver* process (see *ANReceiver* class and classes inherited from this class)

The synchronization between the processes is based on mutexes (see https://en.cppreference.com/w/cpp/thread/mutex)


The *generator* and *receiver* processes are executed in parallel, within two different pthreads, assigned to two different CPU cores. 
While being executed, the processes communicate data through a common *SharedBuffer* as follows:
* the *generator* process picks a name of an animal from a pre-defined *dictionary of animal names*. If the *SharedBuffer* is available for writing, the *generator* process writes the name of the animal into the *SharedBuffer*. Otherwise,  the *generator* process waits until the *SharedBuffer* is available for writing.
* the *receiver* process waits until the *SharedBuffer* contains a name of an animal and is available for reading. When the *SharedBuffer* contains an animal name and is available for reading, the *receiver* process reads the name of an animal from the *SharedBuffer*, thereby emptying the buffer. 
Then, the receiver process uses the pre-defined *dictionary of animal names* to translate the animal name, extracted from the *SharedBuffer*, and prints the translated name into console.

The pre-defined *dictionary of animal names* is a static dictionary, where key (string) is a name of an animal in English and value (string) is a name of the same animal in Dutch.

The example has two implementations that vary in type of *SharedBuffer* (see ./double_buf and ./single_buf sub-folders). The implementations vary in terms of:
* *SharedBuffer* implementation
* checks for buffer availability
* mutex-based synchronization