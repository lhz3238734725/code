/*************************************************************
* windows 驱动详解第一章示例，手写
* autor:lhz
* time :2023-5-25
*************************************************************/
#include "Driver.h"

#define DEVICE_NAME L"\\Device\\MyDDKDevice"
#define DEVICE_SYMLINKNAME L"\\??\\HelloDDk"

/*************************************************************
* 函数名称:CreateDevice
* 功能描述:初始化设备对象
* 参数列表:
	  pDriverObject:从I/O管理器中传进来的驱动对象
* 返回 值:返回初始化状态
*************************************************************/
#pragma PAGEDCODE 
NTSTATUS CreateDevice(IN PDRIVER_OBJECT pDriverObject)
{
	NTSTATUS status = STATUS_SUCCESS;
	//设备对象指针
	PDEVICE_OBJECT pDevObj = NULL;
	//设备拓展结构
	PDEVICE_EXTENSION pDevExt = NULL;

	//设备名称
	UNICODE_STRING devName;
	RtlInitUnicodeString(&devName, DEVICE_NAME);

	//创建一个设备对象
	status = IoCreateDevice(pDriverObject, sizeof(DEVICE_EXTENSION), &devName, FILE_DEVICE_UNKNOWN, 0, TRUE, &pDevObj);
	if (!NT_SUCCESS(status))
	{
		return status;
	}

	//表明设备的内存操作方式为缓冲区方式
	pDevObj->Flags |= DO_BUFFERED_IO;
	//给设备拓展对象赋值
	pDevExt = (PDEVICE_EXTENSION)pDevObj->DeviceExtension;
	pDevExt->pDevice = pDevObj;
	pDevExt->ustrDeviceName = devName;

	//设备符号链接
	UNICODE_STRING symLinkName;
	RtlInitUnicodeString(&symLinkName, DEVICE_SYMLINKNAME);

	//给设备拓展对象赋值
	pDevExt->ustrSymLinkName = symLinkName;

	//为设备创建符号链接
	status = IoCreateSymbolicLink(&symLinkName, &devName);
	if (!NT_SUCCESS(status))
	{
		//删除设备
		IoDeleteDevice(pDevObj);
		return status;
	}

	return STATUS_SUCCESS;
}

/*************************************************************
* 函数名称:HelloDDKUnload
* 功能描述:负责驱动程序的卸载操作
* 参数列表:
	  pDriverObject:驱动对象
* 返回 值:返回状态
*************************************************************/
#pragma PAGEDCODE
VOID HelloDDKUnload(IN PDRIVER_OBJECT pDriverObject)
{
	PDEVICE_OBJECT pNextObj;
	DbgPrint("Enter HelloDDKUnload");
	pNextObj = pDriverObject->DeviceObject;

	while (pNextObj != NULL)
	{

		PDEVICE_EXTENSION pDevExt = (PDEVICE_EXTENSION)pNextObj->DeviceExtension;

		//删除符号链接
		UNICODE_STRING symLinkName = pDevExt->ustrSymLinkName;
		IoDeleteSymbolicLink(&symLinkName);

		pNextObj = pNextObj->NextDevice;

		//删除设备
		IoDeleteDevice(pDevExt->pDevice);
	}
}


/*************************************************************
* 函数名称:HelloDDKDispatchRoutine
* 功能描述:对读IRP进行处理
* 参数列表:
	  pDevObj:功能设备对象
	  pIrp:从IO请求包
* 返回 值:返回状态
*************************************************************/
#pragma PAGEDCODE
NTSTATUS HelloDDKDispatchRoutime(IN PDEVICE_OBJECT pDevObj, IN PIRP pIrp)
{
	NTSTATUS status = STATUS_SUCCESS;
	DbgPrint("Enter HelloDDKDispatchRoutime");

	pIrp->IoStatus.Status = status;      //irp的状态
	pIrp->IoStatus.Information = 0;      //irp操作的字节数
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	DbgPrint("Leave HelloDDKDispatchRoutime");
	return status;
}


/*************************************************************
*函数名称:DriverEntry
* 功能描述:初始化驱动程序，定位和申请硬件资源，创建内核对象
* 参数列表:
*      pDriverObject:从I/O管理器中传进来的驱动对象
*      pRegistryPath:驱动程序在注册表的中的路径
* 返回 值:返回初始化驱动状态
*************************************************************/
//加载到INIT内存区域，即加载完函数后，可以清空内存
#pragma INITCODE  
extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObject,
								IN PUNICODE_STRING pRegistryPath) {

	NTSTATUS status = STATUS_SUCCESS;
	DbgPrint("Enter DriverEntry");

	//设置驱动的卸载函数
	pDriverObject->DriverUnload = HelloDDKUnload;
	//设置驱动的各种派遣函数
	pDriverObject->MajorFunction[IRP_MJ_CREATE] = HelloDDKDispatchRoutime;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = HelloDDKDispatchRoutime;
	pDriverObject->MajorFunction[IRP_MJ_WRITE] = HelloDDKDispatchRoutime;
	pDriverObject->MajorFunction[IRP_MJ_READ] = HelloDDKDispatchRoutime;

	status = CreateDevice(pDriverObject);

	DbgPrint("DriverEntry End");
	return status;
}