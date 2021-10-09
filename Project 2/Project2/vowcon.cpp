#include <iostream>
#include <pthread.h>

using namespace std;

unsigned short curr_index = 1; // Starting index for passed values

// Struct to hold multiple arguments to pass to the thread
struct arg_struct {
  int size;
  char** words;
};

// Vowel identifier
void* vow(void* ptr) {
  struct arg_struct *args = (struct arg_struct *)ptr;

  // Array of c-strings
  char** word = args->words;

  while (curr_index < args->size) {
    if (word[curr_index][0] == 'a' || word[curr_index][0] == 'A' ||
        word[curr_index][0] == 'e' || word[curr_index][0] == 'E' ||
        word[curr_index][0] == 'i' || word[curr_index][0] == 'I' ||
        word[curr_index][0] == 'o' || word[curr_index][0] == 'O' ||
        word[curr_index][0] == 'u' || word[curr_index][0] == 'U')
        {
          printf("vow: %s\n", word[curr_index]);
          curr_index++;
        }
    sched_yield();
  }
  pthread_exit(0);
}

// Consonant identifier
void* con(void* ptr) {
  struct arg_struct *args = (struct arg_struct *)ptr;

  // Array of c-strings
  char** word = args->words;

  while (curr_index < args->size) {
    if (word[curr_index][0] != 'a' && word[curr_index][0] != 'A' &&
        word[curr_index][0] != 'e' && word[curr_index][0] != 'E' &&
        word[curr_index][0] != 'i' && word[curr_index][0] != 'I' &&
        word[curr_index][0] != 'o' && word[curr_index][0] != 'O' &&
        word[curr_index][0] != 'u' && word[curr_index][0] != 'U')
        {
          printf("con: %s\n", word[curr_index]);
          curr_index++;
        }
  }
  pthread_exit(0);
}

int main(int argc, char** argv) {
  arg_struct args;
  args.size = argc;
  args.words = argv;

  pthread_t vow_thread, con_thread;

  pthread_create(&vow_thread, NULL, vow, (void*)&args);
  pthread_create(&con_thread, NULL, con, (void*)&args);

  pthread_join(vow_thread, NULL);
  pthread_join(con_thread, NULL);

  return 0;
}
