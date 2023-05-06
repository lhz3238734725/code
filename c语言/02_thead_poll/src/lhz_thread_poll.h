#ifndef __LHZ_THREAD_POLL_H__
#define __LHZ_THREAD_POLL_H__

#include <pthread.h>

typedef struct _lhz_task lhz_task;
typedef struct _lhz_work lhz_work;
typedef struct _lhz_task_queue lhz_task_queue;
typedef struct _lhz_work_queue lhz_work_queue;
typedef struct _lhz_thread_poll lhz_thread_poll;

//任务执行体函数指针
typedef void (*task_func) (void*);

//任务对象结构体
struct _lhz_task{
    task_func func;
    void* user_data;
    lhz_task* pre;
    lhz_task* next;
};

//工作对象结构体
struct _lhz_work{
    pthread_t thread_id;
    int termination;
    lhz_thread_poll* thread_poll;
    lhz_work* pre;
    lhz_work* next;
};

//任务队列结构体
struct _lhz_task_queue{
    lhz_task* head;
    lhz_task* tail;
};

//工作队列结构体
struct _lhz_work_queue
{
    lhz_work* head;
    lhz_work* tail;
};


//线程池
struct _lhz_thread_poll{
    lhz_task_queue* task_queue;
    lhz_work_queue* work_queue;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
};

//创建一个线程池
int lhz_thread_poll_create(lhz_thread_poll** p_thread_poll, int thread_count);

//销毁一个线程池
void lhz_thread_poll_destroy(lhz_thread_poll** thread_poll);

//往线程池里面添加任务
void lhz_thread_poll_push_task(lhz_thread_poll* thread_poll, lhz_task* task);

#endif