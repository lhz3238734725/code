/*************************************************************
* windows 驱动详解第一章示例，手写
* autor:lhz
* time :2023-5-25
*************************************************************/
#pragma once

//头文件使用C语言方式编译
#ifdef __cplusplus
extern "C"
{
#endif
#include <ntddk.h>
#ifdef __cplusplus
}
#endif

//定义分页标志，非分页标志，初始化内存块
//相当于汇编里的代码段，参数为段名
#define PAGEDCODE code_seg("PAGE")
#define LOCKEDCODE code_seg()
#define INITCODE code_seg("INIT")

//相当于汇编里的栈段，参数为段名
#define PAGEDDATA data_seg("PAGE")
#define LOCKEDDATA data_seg()
#define INITDATA data_seg("INIT")

//计算一个数组的元素数量，使用数组的总字节数除以单个元素的字节数
#define arraysize(p) (sizeof(p)/sizeof(p[0]))

//定义设备拓展结构体，用于记录和补充设备信息
typedef struct _DEVICE_EXTENSION {
	PDEVICE_OBJECT pDevice;            //设备对象指针
	UNICODE_STRING ustrDeviceName;     //设备名
	UNICODE_STRING ustrSymLinkName;    //符号链接
}DEVICE_EXTENSION, *PDEVICE_EXTENSION;

//函数声明
NTSTATUS CreateDevice(IN PDRIVER_OBJECT pDriverObject);
VOID HelloDDKUnload(IN PDRIVER_OBJECT pDriverObject);
NTSTATUS HelloDDKDispatchRoutime(IN PDEVICE_OBJECT pDevObj,
								 IN PIRP pIrp);
