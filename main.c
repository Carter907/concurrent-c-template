#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

sem_t toy_fox;
sem_t blue_book;

void *tony(void *task_args) {

  sem_wait(&blue_book);
  puts("Tony picked up the blue book, but wants the toy fox.");

  sem_wait(&toy_fox);

	puts("Tony plays with blue book and toy fox.");

	puts("Tony is done playing and puts the items back where he found them.");

  sem_post(&toy_fox);
  sem_post(&blue_book);

  return NULL;
}

void *christie(void *task_args) {

  sem_wait(&toy_fox);
  puts("Christie picked up the toy fox, but wants the blue book.");

  sem_wait(&blue_book);

	puts("Christie plays with blue book and toy fox.");

	puts("Christie is done playing and puts the items back where she found them.");

  sem_post(&toy_fox);
  sem_post(&blue_book);

  return NULL;
}

int main(void) {

  pthread_t tony_thread, christie_thread;
	sem_init(&toy_fox, 0, 1);
	sem_init(&blue_book, 0, 1);

  pthread_create(&tony_thread, NULL, tony, NULL);         // start tony
  pthread_create(&christie_thread, NULL, christie, NULL); // start christie

	pthread_join(tony_thread, NULL);
	pthread_join(christie_thread, NULL);

  return EXIT_SUCCESS;
}
