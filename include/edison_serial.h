/*
 * serial.h
 *
 *  Created on: 2015年3月16日
 *      Author: jh
 */

#ifndef EDISON_SERIAL_H_
#define EDISON_SERIAL_H_


#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>      /*文件控制定义*/
#include <termios.h>    /*PPSIX 终端控制定义*/
#include <errno.h>      /*错误号定义*/
#include <string.h>

#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <bits/sockaddr.h>

#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <time.h>

#include "mraa/gpio.h"
#include "mraa.h"



#define SERIAL_DEV  "/dev/ttyMFD1"





#define LED_PORT   13  //edison开发板J2B1 端子13号引脚




int UART1_Open(int fd,char* port);

void UART1_Close(int fd);

int UART1_Set(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity);

int UART1_Init(int fd, int speed,int flow_ctrl,int databits,int stopbits,int parity);

int UART1_Recv(int fd, char *rcv_buf,int data_len);

int UART1_Send(int fd, char *send_buf,int data_len);


int ThreadSerialScanCode(void);
int ScanCodeDevice(void);




#endif /* SERIAL_H_ */



