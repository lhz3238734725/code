#include "lhz_thread_poll.h"
#include "lhz_log.h"
#include <stdlib.h>

void my_test(void* task){
    lhz_task* m_task = (lhz_task*)task;
    int* num = (int*)m_task->user_data;
    lhz_info("lhz-----%d\n", *num);
}

int main(){

    int res;
    lhz_thread_poll* thread_poll;

    res = lhz_thread_poll_create(&thread_poll, 2);
    if(res != 2) return -1;
    lhz_task* task = NULL;
    for (size_t i = 0; i < 100; i++)
    {
        task = (lhz_task*)malloc(sizeof(lhz_task));
        task->func = my_test;

        task->user_data = (void*)malloc(sizeof(int));
        *(int*)task->user_data = i;
        
        lhz_thread_poll_push_task(thread_poll, task);
    }
    getchar();
    lhz_thread_poll_destroy(&thread_poll);
    return 0;
}