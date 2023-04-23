# Calculate primes using threads
This is basically a CPU load generator up until now.  
Tested with GCC 11.30
## Building
```
$ make threadedprime
```
## Running
Running with all available CPU threads:
```
$ ./threadedprime
```
Running with *n* amount of threads:  
threadedprime *n*  
  
Example with 16 threads

```
$ ./threadedprime 16
```
## Terminating
The process will terminate all threads and itself once a SIGINT is received. So just press [CTRL] + [C] to terminate.
## TODOs and technical debt (in no particular order):
* confirm plattform-portability
* wait for threads to finish calculating instead of waiting for SIGINT
* make threads actually calculate on different sets of numbers, to that primes are not found multiple times
* set a global lower bound of interest, all primes above this shall be printed
