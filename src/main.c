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

int main(void)
{
	ScanCodeDevice();
	
	BluetoothDev();	

	UdpServer();
		
	while(1)
	{
		sleep(20);
	}
	
	return 0;
}


