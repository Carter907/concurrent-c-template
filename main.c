#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t toy_fox = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t blue_book = PTHREAD_MUTEX_INITIALIZER;

void *tony(void *task_args) {

  pthread_mutex_lock(&blue_book);
  puts("Tony picked up the blue book, but wants the toy fox.");

  pthread_mutex_lock(&toy_fox);

	puts("Tony plays with blue book and toy fox.");

	puts("Tony is done playing and puts the items back where he found them.");

  pthread_mutex_unlock(&toy_fox);
  pthread_mutex_unlock(&blue_book);

  return NULL;
}

void *christie(void *task_args) {

  pthread_mutex_lock(&toy_fox);
  puts("Christie picked up the toy fox, but wants the blue book.");

  pthread_mutex_lock(&blue_book);

	puts("Christie plays with blue book and toy fox.");

	puts("Christie is done playing and puts the items back where she found them.");

  pthread_mutex_unlock(&toy_fox);
  pthread_mutex_unlock(&blue_book);

  return NULL;
}

int main(void) {

  pthread_t tony_thread, christie_thread;

  pthread_create(&tony_thread, NULL, tony, NULL);         // start tony
  pthread_create(&christie_thread, NULL, christie, NULL); // start christie

	for (;;)
		;

  return EXIT_SUCCESS;
}
