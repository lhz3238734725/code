#include "lhz_thread_poll.h"
#include <stdlib.h>
#include <string.h>
#include <lhz_log.h>

//线程回调函数
static void thread_callback(void* arg);

//往工作队列里添加工作线程，通过尾插法
static void lhz_work_queue_push(lhz_work_queue *work_queue, lhz_work* m_work);

//从任务队列里删除任务
static void lhz_task_queue_pop(lhz_task_queue* task_queue, lhz_task* task);

//往任务队列里添加任务,通过尾插法
static void lhz_task_queue_push(lhz_task_queue* task_queue, lhz_task* task);

//获取任务
static lhz_task* lhz_get_task(lhz_work* m_work);

//销毁各个线程
static void lhz_thread_destroy(lhz_thread_poll* thread_poll);

//初始化工作队列
static int work_queue_init(lhz_thread_poll* thread_poll);

//初始化任务队列
static int task_queue_init(lhz_thread_poll* thread_poll);

//创建一个线程池
int lhz_thread_poll_create(lhz_thread_poll** p_thread_poll, int thread_count){
    

    if(thread_count <= 0) thread_count=1;

    int res;

    //初始化日志
    res = lhz_log_init(LOG_LEVEL_DEBUG, LOG_TARGET_TREMINAL, NULL);
    if(res != 0){
        goto error;
    }

    //分配线程池空间
    *p_thread_poll = (lhz_thread_poll*)malloc(sizeof(lhz_thread_poll));

    lhz_thread_poll* thread_poll = *p_thread_poll;

    if (thread_poll == NULL) {
        lhz_error("thread_poll malloc failed\n");
        goto lhz_error;
    }
    memset(thread_poll, 0, sizeof(lhz_thread_poll));

     //初始化 cond
    res = pthread_cond_init(&(thread_poll->cond), NULL);
    if(res != 0){
        goto thead_poll_error;
    }

    //初始化 mutex
    res = pthread_mutex_init(&(thread_poll->mutex), NULL);
    if(res != 0){
        goto thead_poll_error;
    }

    res = task_queue_init(thread_poll);
    if (res != 0)
    {
        goto thead_poll_error;
    }
    
    res = work_queue_init(thread_poll);
    if (res != 0)
    {
        goto task_queue_error;
    }
    
    lhz_work* m_work = NULL;
    int count = 0;
    //初始化各个工作对象
    for (size_t i = 0; i < thread_count; i++)
    {   
        //创建一个work
        m_work = (lhz_work*)malloc(sizeof(lhz_work));
        if(m_work == NULL){
            lhz_error("m_work malloc failed\n");
            goto thread_create_error;
        } 
        memset(m_work, 0, sizeof(lhz_work));

        m_work->thread_poll = thread_poll;

        //创建一个thread
        res = pthread_create(&(m_work->thread_id), NULL, (void*)&thread_callback, m_work);
        if (res != 0)
        {
            lhz_error("pthread %d create error:%d\n",i+1 , res);
            goto thread_create_error;
        }
        
        //将work放入工作队列
        lhz_work_queue_push(thread_poll->work_queue, m_work);
        lhz_debug("create %d thread success\n", m_work->thread_id);
        count++;
    }
    return count;

thread_create_error:
    lhz_thread_destroy(thread_poll);
    free(thread_poll->task_queue->head);
    free(thread_poll->task_queue->tail);
    free(thread_poll->task_queue);
task_queue_error:
    free(thread_poll->task_queue->head);
    free(thread_poll->task_queue->tail);
    free(thread_poll->task_queue);
thead_poll_error:
    free(thread_poll);
lhz_error:
    lhz_log_exit();
error:
    return -1;
}



//往线程池里面添加任务
void lhz_thread_poll_push_task(lhz_thread_poll* thread_poll, lhz_task* task){
    pthread_mutex_t* mutex = &thread_poll->mutex;
    pthread_cond_t* cond = &thread_poll->cond;
    pthread_mutex_lock(mutex);
    lhz_task_queue_push(thread_poll->task_queue, task); 
    pthread_cond_signal(cond);
    pthread_mutex_unlock(mutex);
}

//销毁一个线程池
void lhz_thread_poll_destroy(lhz_thread_poll** p_thread_poll){
    lhz_thread_poll* thread_poll = *p_thread_poll;
    lhz_thread_destroy(thread_poll);
    free(thread_poll->work_queue->head);
    free(thread_poll->work_queue->tail);
    free(thread_poll->work_queue);
    free(thread_poll->task_queue->head);
    free(thread_poll->task_queue->tail);
    free(thread_poll->task_queue);
    free(thread_poll);
}

//线程回调函数
static void thread_callback(void* arg){

    lhz_work* m_work = (lhz_work*)arg;
    lhz_task* task = NULL;
    while (1)
    {
        task = lhz_get_task(m_work);

        if(task == NULL){
            free(m_work);
            pthread_exit(NULL);
        }
        task->func((void*)task);
    }
}

//往工作队列里添加工作线程,通过尾插法
static void lhz_work_queue_push(lhz_work_queue* work_queue, lhz_work* m_work){

    //保存tail前一个元素
    lhz_work* temp_work = work_queue->tail->pre;
    //将tail->pre指向新添加的元素
    work_queue->tail->pre = m_work;
    //将新加入元素的前后指针分别指向temp_work和tail
    m_work->pre = temp_work;
    m_work->next = work_queue->tail;
    //将temp_work的next指向新添加的元素
    temp_work->next = m_work;
}

//从任务队列里删除任务
static void lhz_task_queue_pop(lhz_task_queue* task_queue, lhz_task* task){

    lhz_task* temp_pre_task = task->pre;
    lhz_task* temp_next_task = task->next;
    temp_pre_task->next = temp_next_task;
    temp_next_task->pre = temp_pre_task;

    task->pre = NULL;
    task->next = NULL;
}

//往任务队列里添加任务,通过尾插法
static void lhz_task_queue_push(lhz_task_queue* task_queue, lhz_task* task){

    lhz_task* temp_task = task_queue->tail->pre;
    task_queue->tail->pre = task;
    task->pre = temp_task;
    task->next = task_queue->tail;
    temp_task->next = task;
}

//获取任务
static lhz_task* lhz_get_task(lhz_work* m_work){
    lhz_task* task = NULL;
    lhz_task_queue* task_queue = m_work->thread_poll->task_queue;
    pthread_cond_t* cond = &m_work->thread_poll->cond;
    pthread_mutex_t* mutex = &m_work->thread_poll->mutex;

    while (1)
    {
        pthread_mutex_lock(mutex);
        if(task_queue->head->next == task_queue->tail){
             //是否退出进程
            if(m_work->termination) {
                pthread_mutex_unlock(mutex);
                return NULL;
            }
            pthread_cond_wait(cond, mutex);
        }
        //取任务队列的首任务
        if(task_queue->head->next != task_queue->tail){
            task = task_queue->head->next;
            lhz_task_queue_pop(task_queue, task);
        }

        if(task != NULL) {
            pthread_mutex_unlock(mutex);
            return task;
        }
    }
}

//销毁各个线程
static void lhz_thread_destroy(lhz_thread_poll* thread_poll){

    lhz_work* m_work = thread_poll->work_queue->head->next;
    pthread_mutex_t* mutex = &m_work->thread_poll->mutex;
    pthread_cond_t* cond = &m_work->thread_poll->cond;

    while (m_work != thread_poll->work_queue->tail)
    {
        m_work->termination = 1;
        m_work = m_work->next;
    }
    pthread_mutex_lock(mutex);
    pthread_cond_broadcast(cond);
    pthread_mutex_unlock(mutex);
}

//初始化工作队列
static int work_queue_init(lhz_thread_poll* thread_poll){
    thread_poll->work_queue = (lhz_work_queue*)malloc(sizeof(lhz_work_queue));
    if(thread_poll->work_queue == NULL) {
        lhz_error("work_queue malloc failed\n");
        goto error;
    }
    lhz_work_queue* work_queue = thread_poll->work_queue;

    work_queue->head = (lhz_work*)malloc(sizeof(lhz_work));
    if (work_queue->head == NULL)
    {
        lhz_error("work_queue malloc failed\n");
        free(work_queue);
        goto error;
    }
    memset(work_queue->head, 0, sizeof(lhz_work));

    work_queue->tail = (lhz_work*)malloc(sizeof(lhz_work));
    if (work_queue->tail == NULL)
    {
        lhz_error("work_queue malloc failed\n");
        free(work_queue->head);
        free(work_queue);
        goto error;
    }
    memset(work_queue->tail, 0, sizeof(lhz_work));

    work_queue->head->pre = work_queue->tail;
    work_queue->head->next =  work_queue->tail;
    work_queue->tail->pre = work_queue->head;
    work_queue->tail->next = work_queue->head;

    return 0;
error:
    return -1;
}

//初始化任务队列
static int task_queue_init(lhz_thread_poll* thread_poll){
    thread_poll->task_queue = (lhz_task_queue*)malloc(sizeof(lhz_task_queue));
    if(thread_poll->task_queue == NULL) {
        lhz_error("task_queue malloc failed\n");
        goto error;
    }
    lhz_task_queue* task_queue = thread_poll->task_queue;

    task_queue->head = (lhz_task*)malloc(sizeof(lhz_task));
    if (task_queue->head == NULL)
    {
        lhz_error("task queue malloc fialed\n");
        free(task_queue);
        goto error;
    }
    memset(task_queue->head, 0, sizeof(lhz_task));

    task_queue->tail = (lhz_task*)malloc(sizeof(lhz_task));
    if (task_queue->tail == NULL)
    {
        lhz_error("task queue malloc fialed\n");
        free(task_queue->head);
        free(task_queue);
        goto error;
    }
    memset(task_queue->tail, 0, sizeof(lhz_task));

    task_queue->head->pre = task_queue->tail;
    task_queue->head->next = task_queue->tail;
    task_queue->tail->pre = task_queue->head;
    task_queue->tail->next = task_queue->head;

    return 0;
error:
    return -1;
}