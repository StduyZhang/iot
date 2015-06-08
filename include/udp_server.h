/*
 * udp_server.h
 *
 *  Created on: 2015Äê4ÔÂ1ÈÕ
 *      Author: jh
 */

#ifndef UDP_SERVER_H_
#define UDP_SERVER_H_





#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define UDP_SERVER_PORT 8086
#define MAX_MSG_SIZE 1024

#define BUF_SIZE    1024




#define SERVER_IP       "10.10.1.244"
#define SERVER_PORT     "8080"


int UdpServer(void);

int SendMessData(char* inBuffer);

int SendKeyValueData(char* inBuffer);




#endif /* UDP_SERVER_H_ */
