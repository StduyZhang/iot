/*
 ============================================================================
 Name        : iotdk-c-template.c
 Author      : Intel Corporation
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
	 
#include "edison_serial.h"
#include "edison_bluetooth.h"
#include "udp_server.h"
#include "usbhost.h"

int main(void)
{

	//ScanCodeDevice();//ɨ����ѡ�񴮿ڽ��뷽ʽ
	UsbHost();		//ɨ����ѡ��USB�ڽ��뷽ʽ
	
	BluetoothDev();

	UdpServer();
		
	while(1)
	{
		
		sleep(20);

	}
	
	return 0;
}


