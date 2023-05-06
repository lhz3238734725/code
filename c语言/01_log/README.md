# 手写一个轻量级日志框架

**功能**

本日志框架实现四种日志等级：error，warning，info，debug。实现两种日志输出方式：终端，文件

当输出到终端时，每种日志等级支持不同颜色进行输出，日志框架跨平台功能有待测试，多线程功能有待测试。

**编译**

整体代码使用meson和dpkg进行管理,使用命令

meson build

meson install -C build

进行编译生成动态库，最终生成动态库，头文件，pc文件安装在相应的路径中，可在自己的项目中进行引用

**api**

```c
//日志目标
#define LOG_TARGET_TREMINAL 0
#define LOG_TARGET_FILE 1

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

//日志宏接口
lhz_error(const char* format, ...);
lhz_warning(const char* format, ...);
lhz_info(const char* format, ...);
lhz_debug(const char* format, ...);  
```

**使用流程**

1. 先调用 lhz_log_init 函数进行初始化
2. 调用日志宏接口进行输出日志
3. 最后调用lhz_log_exit函数进行资源销毁