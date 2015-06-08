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

	//ScanCodeDevice();//扫描器选择串口接入方式
	UsbHost();		//扫描器选择USB口接入方式
	
	BluetoothDev();

	UdpServer();
		
	while(1)
	{
		
		sleep(20);

	}
	
	return 0;
}


