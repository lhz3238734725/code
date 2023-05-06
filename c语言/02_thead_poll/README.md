# 手写一个轻量级日志框架

**功能**

实现了一个简易的线程池

**编译**

本项目依赖01_log项目，使用其作为日志输出

整体代码使用meson和dpkg进行管理,使用命令

meson build

meson install -C build

进行编译生成动态库，最终生成动态库，头文件，pc文件安装在相应的路径中，可在自己的项目中进行引用

**api**

```c
//任务执行体函数指针
typedef void (*task_func) (void*);

typedef struct _lhz_task lhz_task;
//任务对象结构体
struct _lhz_task{
    task_func func;
    void* user_data;
    lhz_task* pre;
    lhz_task* next;
};

//创建一个线程池
int lhz_thread_poll_create(lhz_thread_poll** p_thread_poll, int thread_count);

//销毁一个线程池
void lhz_thread_poll_destroy(lhz_thread_poll** thread_poll);

//往线程池里面添加任务
void lhz_thread_poll_push_task(lhz_thread_poll* thread_poll, lhz_task* task);  
```

**使用流程**

1. 先调用 lhz_thread_poll_create 函数进行初始化
2. 调用 lhz_thread_poll_push_task 往线程池内添加任务
3. 最后调用 lhz_thread_poll_destroy 函数进行资源销毁