/***************************************************
* ��飺һ����򵥵�NTʽ����
* @fileName:Driver.cpp
* @autor:lhz
* @time:20230525
***************************************************/

#include <ntddk.h>

/***************************************************
* ��������:HelloDDKUnload
* ��������:�������������ж�ز���
* �����б�:
	  pDriverObject:��������
* ���� ֵ:����״̬
***************************************************/
void HelloDDKUnload(IN PDRIVER_OBJECT pDriverObject) {

	DbgPrint("HelloDDKUnload.....");

}

/***************************************************
* ��������:DriverEntry
* ��������:��ʼ���������򣬶�λ������Ӳ����Դ�������ں˶���
* �����б�:
	  pDriverObject:��I/O�������д���������������
	  pRegistryPath:����������ע�����е�·��
* ���� ֵ:���س�ʼ������״̬
***************************************************/
extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT pDriverObject,
								IN PUNICODE_STRING pRegistryPath
								) {

	NTSTATUS status = STATUS_SUCCESS;

	DbgPrint("DriverEntry.....");

	//����ж�غ���
	pDriverObject->DriverUnload = HelloDDKUnload;

	return status;
}