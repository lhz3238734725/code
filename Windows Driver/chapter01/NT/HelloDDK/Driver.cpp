/*************************************************************
* windows ��������һ��ʾ������д
* autor:lhz
* time :2023-5-25
*************************************************************/
#include "Driver.h"

#define DEVICE_NAME L"\\Device\\MyDDKDevice"
#define DEVICE_SYMLINKNAME L"\\??\\HelloDDk"

/*************************************************************
* ��������:CreateDevice
* ��������:��ʼ���豸����
* �����б�:
	  pDriverObject:��I/O�������д���������������
* ���� ֵ:���س�ʼ��״̬
*************************************************************/
#pragma PAGEDCODE 
NTSTATUS CreateDevice(IN PDRIVER_OBJECT pDriverObject)
{
	NTSTATUS status = STATUS_SUCCESS;
	//�豸����ָ��
	PDEVICE_OBJECT pDevObj = NULL;
	//�豸��չ�ṹ
	PDEVICE_EXTENSION pDevExt = NULL;

	//�豸����
	UNICODE_STRING devName;
	RtlInitUnicodeString(&devName, DEVICE_NAME);

	//����һ���豸����
	status = IoCreateDevice(pDriverObject, sizeof(DEVICE_EXTENSION), &devName, FILE_DEVICE_UNKNOWN, 0, TRUE, &pDevObj);
	if (!NT_SUCCESS(status))
	{
		return status;
	}

	//�����豸���ڴ������ʽΪ��������ʽ
	pDevObj->Flags |= DO_BUFFERED_IO;
	//���豸��չ����ֵ
	pDevExt = (PDEVICE_EXTENSION)pDevObj->DeviceExtension;
	pDevExt->pDevice = pDevObj;
	pDevExt->ustrDeviceName = devName;

	//�豸��������
	UNICODE_STRING symLinkName;
	RtlInitUnicodeString(&symLinkName, DEVICE_SYMLINKNAME);

	//���豸��չ����ֵ
	pDevExt->ustrSymLinkName = symLinkName;

	//Ϊ�豸������������
	status = IoCreateSymbolicLink(&symLinkName, &devName);
	if (!NT_SUCCESS(status))
	{
		//ɾ���豸
		IoDeleteDevice(pDevObj);
		return status;
	}

	return STATUS_SUCCESS;
}

/*************************************************************
* ��������:HelloDDKUnload
* ��������:�������������ж�ز���
* �����б�:
	  pDriverObject:��������
* ���� ֵ:����״̬
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

		//ɾ����������
		UNICODE_STRING symLinkName = pDevExt->ustrSymLinkName;
		IoDeleteSymbolicLink(&symLinkName);

		pNextObj = pNextObj->NextDevice;

		//ɾ���豸
		IoDeleteDevice(pDevExt->pDevice);
	}
}


/*************************************************************
* ��������:HelloDDKDispatchRoutine
* ��������:�Զ�IRP���д���
* �����б�:
	  pDevObj:�����豸����
	  pIrp:��IO�����
* ���� ֵ:����״̬
*************************************************************/
#pragma PAGEDCODE
NTSTATUS HelloDDKDispatchRoutime(IN PDEVICE_OBJECT pDevObj, IN PIRP pIrp)
{
	NTSTATUS status = STATUS_SUCCESS;
	DbgPrint("Enter HelloDDKDispatchRoutime");

	pIrp->IoStatus.Status = status;      //irp��״̬
	pIrp->IoStatus.Information = 0;      //irp�������ֽ���
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);

	DbgPrint("Leave HelloDDKDispatchRoutime");
	return status;
}


/*************************************************************
*��������:DriverEntry
* ��������:��ʼ���������򣬶�λ������Ӳ����Դ�������ں˶���
* �����б�:
*      pDriverObject:��I/O�������д���������������
*      pRegistryPath:����������ע�����е�·��
* ���� ֵ:���س�ʼ������״̬
*************************************************************/
//���ص�INIT�ڴ����򣬼������꺯���󣬿�������ڴ�
#pragma INITCODE  
extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObject,
								IN PUNICODE_STRING pRegistryPath) {

	NTSTATUS status = STATUS_SUCCESS;
	DbgPrint("Enter DriverEntry");

	//����������ж�غ���
	pDriverObject->DriverUnload = HelloDDKUnload;
	//���������ĸ�����ǲ����
	pDriverObject->MajorFunction[IRP_MJ_CREATE] = HelloDDKDispatchRoutime;
	pDriverObject->MajorFunction[IRP_MJ_CLOSE] = HelloDDKDispatchRoutime;
	pDriverObject->MajorFunction[IRP_MJ_WRITE] = HelloDDKDispatchRoutime;
	pDriverObject->MajorFunction[IRP_MJ_READ] = HelloDDKDispatchRoutime;

	status = CreateDevice(pDriverObject);

	DbgPrint("DriverEntry End");
	return status;
}