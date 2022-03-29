# Animal Name Translator

An illustrative example of *SharedCharBuffer* use. The example application has 
two processes, each defined as an object of a special class, inherited from *MyProcess* class:
* *generator* process (an object of *ANGenerator* class)
* *receiver* process (an object of *ANReceiver* class)


The *generator* and *receiver* processes are executed in parallel, within two different pthreads, assigned to two different CPU cores. 
While being executed, the processes communicate data through a common *SharedCharBuffer* as follows:
* the *generator* process picks a name of an animal from a pre-defined *dictionary of animal names*. If the *SharedCharBuffer* is empty, the *generator* process writes the name of the animal into the *SharedCharBuffer*. Otherwise,  the *generator* process waits until the *SharedCharBuffer* is empty.
* the *receiver* process waits until the *SharedCharBuffer* is NOT empty, i.e., until the *SharedCharBuffer* contains a name of an animal. When the *SharedCharBuffer* is not empty, the *receiver* process reads the name of an animal from the *SharedCharBuffer*, thereby emptying the buffer. 
Then, the receiver process uses the pre-defined *dictionary of animal names* to translate the animal name, extracted from the *SharedCharBuffer*, and prints the translated name into console.

The pre-defined *dictionary of animal names* is a static dictionary, where key (string) is a name of an animal in English and value (string) is a name of the same animal in Dutch. 