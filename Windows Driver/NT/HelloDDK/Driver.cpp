/***************************************************
* 简介：一个最简单的NT式驱动
* @fileName:Driver.cpp
* @autor:lhz
* @time:20230525
***************************************************/

#include <ntddk.h>

/***************************************************
* 函数名称:HelloDDKUnload
* 功能描述:负责驱动程序的卸载操作
* 参数列表:
	  pDriverObject:驱动对象
* 返回 值:返回状态
***************************************************/
void HelloDDKUnload(IN PDRIVER_OBJECT pDriverObject) {

	DbgPrint("HelloDDKUnload.....");

}

/***************************************************
* 函数名称:DriverEntry
* 功能描述:初始化驱动程序，定位和申请硬件资源，创建内核对象
* 参数列表:
	  pDriverObject:从I/O管理器中传进来的驱动对象
	  pRegistryPath:驱动程序在注册表的中的路径
* 返回 值:返回初始化驱动状态
***************************************************/
extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObject,
								IN PUNICODE_STRING pRegistryPath
								) {

	NTSTATUS status = STATUS_SUCCESS;

	DbgPrint("DriverEntry.....");

	//驱动卸载函数
	pDriverObject->DriverUnload = HelloDDKUnload;

	return status;
}