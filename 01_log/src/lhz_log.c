#include "lhz_log.h"
#include "config.h"
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

static void printf_current_time();
static int log_target_file_init(int target, char* path);

LhzSimpleLog* globalLog = NULL;

//获取当前时间
static void printf_current_time(){
    //获取时间戳
    time_t timep;
    time (&timep);
    
    //localtime() 将时间戳转换成当前时间
    struct tm* local = localtime(&timep);
    switch (globalLog->target)
    {
    case LOG_TARGET_TREMINAL:
        printf("[%04d-%02d-%02d %02d:%02d:%02d]", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);
        break;
    case LOG_TARGET_FILE:
        if (globalLog->fp == NULL)
        {
            return;
        }
        fprintf(globalLog->fp,"[%04d-%02d-%02d %02d:%02d:%02d]", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);
        break;
    default:
        break;
    }
}

//日志初始化
int lhz_log_init(int log_level, int target, char* path){

    int globalLog_size = sizeof(LhzSimpleLog);
    globalLog = (LhzSimpleLog*)malloc(globalLog_size);
    memset(globalLog, 0, sizeof(globalLog_size));
    if(globalLog == NULL){
        printf("lhz_log_init error\n");
        return -1;
    } 

    if(log_level >= LOG_LEVEL_ERROR && log_level <= LOG_LEVEL_DEBUG){
        globalLog->log_level = log_level;
    }else{
        globalLog->log_level = LOG_LEVEL_DEFAULT;
    }

    if(target == LOG_TARGET_FILE){
        int r = log_target_file_init(target, path);
        if(r < 0) return -1;
    }else{
        globalLog->target = LOG_TARGET_TREMINAL;
    }
    return 0;
}

//输出目的为文件时，进行文件流初始化
static int log_target_file_init(int target, char* path){

    globalLog->target = LOG_TARGET_FILE;

    if(path == NULL){
        globalLog->path = LOG_DEFAULT_FILE_PATH;
    }else{
        globalLog->path = path;
    }

    globalLog->fp = fopen(globalLog->path, "w");
    if(globalLog->fp == NULL){
        printf("初始化文件流错误\n");
        free(globalLog);
        return -1;
    }
    return 0;
}

//日志退出
void lhz_log_exit(){

    if (globalLog == NULL)
    {
        printf("请先初始化日志上下文\n");
        return;
    }

    if (globalLog->target == LOG_TARGET_FILE)
    {
        fclose(globalLog->fp);
    }
    
    free(globalLog);
}

//设置日志等级
void lhz_log_set_level(int log_level){

    if(globalLog == NULL) {
        printf("请先初始化日志上下文\n");
        return;
    }

    if (LOG_LEVEL_ERROR < globalLog->log_level && globalLog->log_level < LOG_LEVEL_DEBUG)
    {
        printf("请输入正确的日志等级\n");
        return;
    }
    
    globalLog->log_level = log_level;
}

//获取日志目标
void lhz_log_set_target(int target){
    
    if(globalLog == NULL) {
        printf("请先初始化日志上下文\n");
        return;
    }
    if (target >= LOG_TARGET_TREMINAL && target <= LOG_TARGET_FILE)
    {
        printf("请输入正确的日志目标\n");
        return;
    }
    globalLog->target = target;
}

//获取日志等级
char* lhz_log_get_level(){

    if(globalLog == NULL) {
        printf("请先初始化日志上下文\n");
        return NULL;
    }

    return globalLog->log_level == 0 ? "ERROR" : \
           globalLog->log_level == 1 ? "WARNING" : \
           globalLog->log_level == 2 ? "INFO" : \
           globalLog->log_level == 3 ? "DEBUG" : "UNKNOWN" ;
}

//日志接口
void lhz_log(int log_level, const char* format, ...){

    if (globalLog == NULL)
    {
        printf("请先初始化日志上下文\n");
        return;
    }
      
    if(log_level <= globalLog->log_level){
        if (globalLog->target == LOG_TARGET_TREMINAL)
        {
            va_list args;
            va_start(args, format);
            switch (log_level)
            {
            case LOG_LEVEL_ERROR:
                printf(COLOR_CONTROL_START COLOR_RED);
                printf_current_time();
                vprintf(format, args);
                printf(COLOR_CONTROL_END);
                break;
            case LOG_LEVEL_WARNING:
                printf(COLOR_CONTROL_START COLOR_GREEN);
                printf_current_time();
                vprintf(format, args);
                printf(COLOR_CONTROL_END);
                break;
            case LOG_LEVEL_INFO:
                printf(COLOR_CONTROL_START COLOR_DARK_GREEN);
                printf_current_time();
                vprintf(format, args);
                printf(COLOR_CONTROL_END);
                break;
            case LOG_LEVEL_DEBUG:
                printf(COLOR_CONTROL_START COLOR_PURPLE);
                printf_current_time();
                vprintf(format, args);
                printf(COLOR_CONTROL_END);
                break;
            default:
                break;
            }
            va_end(args);
        }else{
            printf_current_time();
            va_list args;
            va_start(args, format);
            vfprintf(globalLog->fp , format, args);
            va_end(args);

            globalLog->log_size++;

            // 到达缓冲区最大日志条数将日志写入文件
            if(globalLog->log_size >= FILE_LOG_MAX_BUFFER_SIZE) fflush(globalLog->fp);
        }
    }
}
