#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int size;
int counter;
int *fibonacci;

int outputcheck(int argc, char* argv[]);
void printFib();
void *fibThread(void *arg);

int main(int argc, char *argv[]){
  outputcheck(argc, argv);
  size = atoi(argv[1]);
  fibonacci = (int *)malloc(size * sizeof(int));
  pthread_t *threads = (pthread_t *) malloc(size * sizeof(pthread_t));
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  // Creates a single thread and waits
  pthread_create(&threads[counter], &attr, fibThread, NULL);
  pthread_join(threads[counter], NULL);


  printFib();
  return 0;
}


// Iterative fib sequence generator, adds numbers to dynamic malloc data structure
void *fibThread(void *arg){
  int prevprevNum, prevNum = 0, currNumber = 1;

	for (int i = 0; i < size; i++) {
		prevprevNum = prevNum;
		prevNum = currNumber;
		currNumber = prevprevNum + prevNum;
		fibonacci[i] = prevprevNum;
	}
    pthread_exit(0);
  }

  // Checks if a number is given for the length of the fib sequence
  int outputcheck(int argc, char* argv[]){
  if (argc != 2){
    printf("incorrect input \nformat must be '/a.out <intgervalue>'\n");
    exit(-1);
  }
  if (atoi(argv[1]) < 0){
    printf("incorrect input \n%d must be >= 0\n", atoi(argv[1]));
    exit(-1);
  }
  return 0;
}

// Prints fib sequence for testing purposes
void printFib(){
  printf("Fibonacci sequence: ");
  int k;

  for (k = 0; k < size; k++){
    printf("%d ", fibonacci[k]);
  }
  printf("\n");
}
