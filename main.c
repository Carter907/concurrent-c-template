#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>



pthread_mutex_t l1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t l2 = PTHREAD_MUTEX_INITIALIZER;

void *task1(void *task_args) {	

	pthread_mutex_lock(&l2);	
	sleep(1); // make sure this task has aquired the initial lock first
	pthread_mutex_lock(&l1);	
	puts("task1 executing...");
	pthread_mutex_unlock(&l1);
	pthread_mutex_unlock(&l2);

	return NULL;
}

void *task2(void *task_args) {	

	pthread_mutex_lock(&l1);	
	sleep(1); // make sure this task has aquired the initial lock first
	pthread_mutex_lock(&l2);	
	puts("task2 executing...");
	pthread_mutex_unlock(&l2);
	pthread_mutex_unlock(&l1);

	return NULL;
}

int main(void) {

	while (true) {

		pthread_t t1, t2;
		pthread_create(&t1, NULL, task1, NULL);
		pthread_create(&t2, NULL, task2, NULL);

		pthread_join(t1, NULL);
		pthread_join(t2, NULL);
	}

	return EXIT_SUCCESS;
}
