#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <stdbool.h>

// initialize with biggest possible value for unsigned type
uintmax_t LIMIT = (uintmax_t)(-1);

// global var for threadcount
int tc = 0;

void handleSIGINT() {
	printf("exiting...\n");
	exit(0);
}

// mainly used for debugging
void *printThNr() {
	// number of cores will probably not warrant a mutex
	printf("thread #%d with thread ID %ld\n", tc++, pthread_self());
	return 0;
}

void printPrimes(bool primes[]) {
	for (uintmax_t a = 1; a <= LIMIT; a++) {
        if (primes[a]) {
            printf("%ju ", (uintmax_t)a);
        }
    }
	printf("\n");
}

void *sieveOfAtkin() {
	bool sieve[LIMIT];
	for (uintmax_t i = 0; i < LIMIT; i++) {
		sieve[i] = false;
	}

	for (uintmax_t x = 1; x * x <= LIMIT; x++) {
		for (uintmax_t y = 1; y * y <= LIMIT; y++) {
			
			// condition 1
			uintmax_t n = (4 * x * x) + (y * y);
			if (n <= LIMIT && (n % 12 == 1 || n % 12 == 5)) {
				sieve[n] ^= true;
			}

			// condition 2
			n = (3 * x * x) + (y * y);
			if (n <= LIMIT && n % 12 == 7) {
				sieve[n] ^= true;
			}

			// condition 3
			n = (3 * x * x) - (y * y);
			if (x > y && n <= LIMIT && n % 12 == 11) {
				sieve[n] ^= true;
			}
		}
	}

	// mark all multiples of squares as non-prime
	for (uintmax_t r = 5; r * r <= LIMIT; r++) {
		if (sieve[r]) {
			for (uintmax_t i = r * r; i <= LIMIT; i += r * r) {
				sieve[i] = false;
			}
		}
	}

	// print all primes
	// comment this out to avoid the bottleneck of terminal printing
	//printPrimes(sieve);
	
	return 0;
}

int main(int argc, char *argv[]) {
	signal(SIGINT, handleSIGINT);

	// determine how many threads to start
	int threadcount;
	if (argc > 2) {
		printf("specify the amount of threads to use or give one arg as int for how many threads should be used>");
	} else if (argc > 1) {
		threadcount = atoi(argv[1]);
	} else {
		threadcount = sysconf(_SC_NPROCESSORS_ONLN);
	}
	printf("Amount of threads to saturate: %d\n", threadcount);
	printf("Primes up to %ju will be calculated\n", LIMIT);

	// start threads
	pthread_t th[threadcount];
	for (int i = 0; i < threadcount; i++) {
		pthread_create(&th[i], NULL, &sieveOfAtkin, NULL);
		pthread_detach(th[i]);
	}

	// wait so calculations can be done
	pause();

	pthread_exit(0);
	return 0;
}
