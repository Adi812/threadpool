#include "cond.h"

void cond_init(condition_t *condi){
	pthread_mutex_init(&condi->mutex,NULL);
	pthread_cond_init(&condi->cond,NULL);
}

void cond_lock(condition_t *condi){
	pthread_mutex_lock(&condi->mutex);
}

void cond_unlock(condition_t *condi){
	pthread_mutex_unlock(&condi->mutex);
}

void cond_wait(condition_t *condi){
	pthread_cond_wait(&condi->cond,&condi->mutex);
}

void cond_signal(condition_t *condi){
	pthread_cond_signal(&condi->cond);
}

void cond_destroy(condition_t *condi){
	pthread_mutex_destroy(&condi->mutex);
	pthread_cond_destroy(&condi->cond);
}
