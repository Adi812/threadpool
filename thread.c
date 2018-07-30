#include "thread.h"

void threadpool_init(threadpool_t *pool){
	cond_init(&(pool->cond));
	pool->first=NULL;
	pool->tail=NULL;
	pool->max_thread=MAX;
	pool->idle=0;
	pool->counter=0;
}

void* myroute(void *arg){
	threadpool_t *pool=(threadpool_t *)arg;
	while(1){
		cond_lock(&pool->cond);
		pool->idle++;
		if(pool->first==NULL){
			cond_wait(&pool->cond);
		}
		pool->idle--;

		if(pool->first!=NULL){
			task_t *t=pool->first;
			pool->first=pool->first->next;
			cond_unlock(&pool->cond);

			(t->pfun)(t->arg);
			cond_lock(&pool->cond);
			free(t);
		}
			cond_unlock(&pool->cond);
	}
}

void threadpool_add(threadpool_t *pool,void*(*pfun1)(void *),void *arg1){
	task_t *new=(task_t *)malloc(sizeof(task_t));
	new->pfun=pfun1;
	new->arg=arg1;
	new->next=NULL;
	cond_lock(&pool->cond);
	if(pool->first==NULL){
		pool->first=new;
	}else{
		pool->tail->next=new;
	}
	pool->tail=new;
	
	if(pool->idle>0){
		cond_signal(&pool->cond);
	}else if(pool->counter<pool->max_thread){
		pthread_t tid;
		pthread_create(&tid,NULL,myroute,(void *)pool);
		pool->counter++;
	}
	cond_unlock(&pool->cond);
}

void threadpool_destroy(threadpool_t *pool){
	cond_destroy(&pool->cond);
}

