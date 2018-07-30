#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "cond.h"

#define MAX 15

//任务队列
typedef struct tast{
	void*(*pfun) (void *);//回调函数
	void * arg; //回调函数参数
	struct task *next;
}task_t;

//线程池
typedef struct threadpool{
	condition_t cond;//互斥量
	task_t *first; //任务队列的队头
	task_t *tail; //任务队列队尾
	int max_thread; //最大线程数
	int idle; //空闲线程个数
	int counter; //线程池当前线程个数
}threadpool_t;


void threadpool_init(threadpool_t *pool);
void* myroute(void *arg);
void threadpool_add(threadpool_t *pool,void*(*pfun1)(void *),void *arg1);
void threadpool_destroy(threadpool_t *pool);


