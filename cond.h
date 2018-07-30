#include <pthread.h>

//互斥量
typedef struct condition{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}condition_t;


