#include <stdio.h>
#include <stdlib.h>
#include "thread.h"


void * route(void * arg){
	int num=*(int *)arg;
	free(arg);
	printf("%#X thread say %d runing\n",pthread_self(),num);
	sleep(1);
}

int main(void){
	threadpool_t pool;
	threadpool_init(&pool);
	int i=0;
	for(;i<10;i++){
		int *p=malloc(sizeof(int));
		*p=i;
		threadpool_add(&pool,route,(void*)p);
	}
	sleep(15);
	threadpool_destroy(&pool);
}
