/*************************************************************
* windows ��������һ��ʾ������д
* autor:lhz
* time :2023-5-25
*************************************************************/
#pragma once

//ͷ�ļ�ʹ��C���Է�ʽ����
#ifdef __cplusplus
extern "C"
{
#endif
#include <ntddk.h>
#ifdef __cplusplus
}
#endif

//�����ҳ��־���Ƿ�ҳ��־����ʼ���ڴ��
//�൱�ڻ����Ĵ���Σ�����Ϊ����
#define PAGEDCODE code_seg("PAGE")
#define LOCKEDCODE code_seg()
#define INITCODE code_seg("INIT")

//�൱�ڻ�����ջ�Σ�����Ϊ����
#define PAGEDDATA data_seg("PAGE")
#define LOCKEDDATA data_seg()
#define INITDATA data_seg("INIT")

//����һ�������Ԫ��������ʹ����������ֽ������Ե���Ԫ�ص��ֽ���
#define arraysize(p) (sizeof(p)/sizeof(p[0]))

//�����豸��չ�ṹ�壬���ڼ�¼�Ͳ����豸��Ϣ
typedef struct _DEVICE_EXTENSION {
	PDEVICE_OBJECT pDevice;            //�豸����ָ��
	UNICODE_STRING ustrDeviceName;     //�豸��
	UNICODE_STRING ustrSymLinkName;    //��������
}DEVICE_EXTENSION, *PDEVICE_EXTENSION;

//��������
NTSTATUS CreateDevice(IN PDRIVER_OBJECT pDriverObject);
VOID HelloDDKUnload(IN PDRIVER_OBJECT pDriverObject);
NTSTATUS HelloDDKDispatchRoutime(IN PDEVICE_OBJECT pDevObj,
								 IN PIRP pIrp);
