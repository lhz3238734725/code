#ifndef __LHZ_LOG_H__
#define __LHZ_LOG_H__

#include <stdio.h>
#include <pthread.h>

//颜色控制开始与结束
#define COLOR_CONTROL_START "\033[0;"
#define COLOR_CONTROL_END "\033[0m"

//字体颜色
#define COLOR_BLACK "30m"
#define COLOR_RED "31m"
#define COLOR_BLUE "32m"
#define COLOR_YELLOW "33m"
#define COLOR_GREEN "34m"
#define COLOR_PURPLE "35m"
#define COLOR_DARK_GREEN "36m"
#define COLOR_WHITE "37m"

//日志等级
#define LOG_LEVEL_ERROR 0
#define LOG_LEVEL_WARNING 1
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_DEBUG 3
#define LOG_LEVEL_DEFAULT LOG_LEVEL_INFO

//日志目标
#define LOG_TARGET_TREMINAL 0
#define LOG_TARGET_FILE 1

#define LOG_DEFAULT_FILE_PATH "./lhz-test.log"

//缓冲区最大日志条数
#define FILE_LOG_MAX_BUFFER_SIZE 30


//日志结构体
typedef struct _LhzSimpleLog LhzSimpleLog;

struct _LhzSimpleLog {
    int log_level;
    int target;
    FILE* fp;
    char* path;
    int log_size;
    pthread_mutex_t mutex;
};

//日志初始化
int lhz_log_init(int log_level, int target, char* path);

//日志退出
void lhz_log_exit();

//设置日志等级
void lhz_log_set_level(int log_level);

//设置日志目标
void lhz_log_set_target(int target);

//获取日志等级
char* lhz_log_get_level();

//日志接口
void lhz_log(int log_level, const char* format, ...);


//定义四种日志等级输出宏
#define lhz_error(format, ...) \
        lhz_log(LOG_LEVEL_ERROR, "[%s][%s--%s--%d]:"format, "Error", __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#define lhz_warning(format, ...) \
        lhz_log(LOG_LEVEL_WARNING, "[%s][%s--%s--%d]:"format, "WARNING", __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#define lhz_info(format, ...) \
        lhz_log(LOG_LEVEL_INFO, "[%s][%s--%s--%d]:"format, "INFO", __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#define lhz_debug(format, ...) \
        lhz_log(LOG_LEVEL_DEBUG, "[%s][%s--%s--%d]:"format, "DEBUG", __FILE__, __func__, __LINE__, ##__VA_ARGS__)
#endif