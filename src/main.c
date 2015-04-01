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

int main(void)
{
	BluetoothDev();
	
	//ScanCodeDevice();
		
	while(1)
	{
		sleep(20);
	}
	
	return 0;
}


