/*
 * edison_bluetooth.c
 *  Created on: 2015年3月25日
 *  Author: Mr.Zhang
 */

#include "edison_bluetooth.h"

#define CMD_LEN  5

int sd = 0;

int measure_flag = 0;

unsigned char handshake_cmd[] 		= {0xBE,0xB0,0x01,0xb0,0xce};//handshake   check online
unsigned char start_measure_cmd[] 	= {0XBE,0XB0,0X01,0Xc0,0X36};//start measure
unsigned char stop_measure_cmd[]	= {0XBE,0XB0,0X01,0Xc1,0X68};//stop measure
unsigned char sys_sleep[]			= {0XBE,0XB0,0X01,0Xd0,0Xab};//system sleep

void SetBtMeasureFlag(void)
{
	measure_flag = 1;
}

void ClrBtMeasureFlag(void)
{
	measure_flag = 0;
}

int GetBtMeasureFlag(void)
{
	return measure_flag;
}

int SendDataToBtDev(int fd, const unsigned char* data, int len)
{
	return ( send(fd, data, len, 0) );//write(s, "hello!", 6);
}

int RecvDataFromBtDev(int fd, unsigned char* data, int len)
{
	memset(data,0,len);
	return ( recv(fd, data, len, 0) );
}

int CheckResp(unsigned char* data)//暂时不使用CRC8，因为发现没有收到这个数据
{
	if ((data[0]==0xd0) && (data[1]==0xc2))
	{
		if ((data[2]==0x02) && (data[3]==0x00) && (data[4]==0x00))
		{
			puts("Normal response!");
			return 1;
		}

		if ((data[2]==0x02) && (data[3]==0xFF) && (data[4]==0xFF))
		{
			puts("Error resp: Slave is busy, cann't process!");
		}
		
		if ((data[2]==0x02) && (data[3]==0x00) && (data[4]==0xFF))
		{
			puts("Error resp: Cmd is invalid!");
		}
		
		if ((data[2]==0x05) && (data[3]==0xCC))
		{
			puts("Measure finished!");
			return 3;
		}			

		
	}
	else
	{
		puts("Error resp: Data head is incorrect!");
	}
	
	return 0;
	
}


void BtRecvThread(void)
{
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	int i = 0;
	unsigned char data_buffer[16] = { 0 };
	
	while(1)
	{
		puts("Recving measure result:");
		RecvDataFromBtDev(sd, data_buffer, sizeof(data_buffer));//阻塞接收测量数据
		
		#if 1
		puts("Recv data:");
		for (i=0; i<sizeof(data_buffer); i++)
		{
			printf("%x \n",data_buffer[i]);
		}
		#endif


		if (CheckResp(data_buffer) == 3)//measure succeed
		{
			printf("H:%d L:%d Heart:%d HeartHZ:%d \n",
				data_buffer[4],data_buffer[5],data_buffer[6],data_buffer[7]);
			//发送数据到客户端服务器
		}
		
		sleep(1);
		
	}
	
}


int BluetoothThread(void)
{
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	    
	int status = 0;
    char dest[18] = BT_MAC;
	struct sockaddr_rc addr = { 0 };
    
    sd = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);// allocate a socket

    // set the connection parameters (who to connect to)
    addr.rc_family = AF_BLUETOOTH;
    addr.rc_channel = (uint8_t) 1;//how to choose?
    str2ba( dest, &addr.rc_bdaddr );
 
 puts("bluetooth test!");
	SetBtMeasureFlag();//test

	while(1) 
	{
		if (GetBtMeasureFlag() == 1)
		{
			status = connect(sd, (struct sockaddr *)&addr, sizeof(addr));
			if( status == 0 )// connect to server
			{
				//if (SendCmd(sd, handshake_cmd, CMD_LEN) == 1)//测试发现没收到设备响应
				{							
					SendDataToBtDev(sd, start_measure_cmd, CMD_LEN);
				}
			}

			else if( status < 0 )
			{
				perror("Connect bluetooth device failed!");
			}
		
			ClrBtMeasureFlag();//measure over,  clear flag
		}
		sleep(2);
	}

    close(sd);

    //if (pthread_cancel( id_blue_tooth) != 0)   puts("Thread Bluetooth cancel failed!");
    
    return 0;
}


int BluetoothDev(void)
{
	pthread_t id_bt;
	pthread_t id_bt_recv;

	if(pthread_create(&id_bt,NULL, (void*(*)(void*))BluetoothThread, NULL))
	{
		 return(PrintError("create Thread_Bluetooth error"));
	}
	pthread_detach(id_bt);


	if(pthread_create(&id_bt_recv,NULL, (void*(*)(void*))BtRecvThread, NULL))
	{
		 return(PrintError("create BtRecvThread error"));
	}
	pthread_detach(id_bt_recv);

	
	return 0;
}


