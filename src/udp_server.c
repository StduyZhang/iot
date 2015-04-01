/*
 * udp_server.c

 *
 *  Created on: 2015年4月1日
 *      Author: Mr.Zhang
 */

#include "udp_server.h"
#include "edison_bluetooth.h"




int SendMessData(char* inBuffer)
{
	int ret = 0;
	char len_str[10];//存放一个数:数据的长度
	char str1[BUF_SIZE*4];
	char str2[BUF_SIZE];
	char buf[BUF_SIZE];
	int len = 0;
	   
	   int sock_fd = 0;

	   sock_fd = TcpSocketInit(SERVER_IP, SERVER_PORT);//初始化套接口

	   if (TcpGetConnect(sock_fd) == 0)
	   {
		   puts("Link server succeed");
	   }
	   else
	   {
	   	   return -1;
	   }
		//发送数据
	   memset(str2, 0, sizeof(str2));
	   sprintf(str2, "obj_id=0&title=book&content=%s&ispush=1", inBuffer);//  //obj_id    title    content
	   len = strlen(str2);

	   sprintf(len_str, "%d", len);

	   memset(str1, 0, sizeof(str1));
	   strcat(str1, "POST http://10.10.1.125:8080/NiotService/msg/addMsg.do HTTP/1.1\n");
	   strcat(str1, "Host: 10.10.1.125\n");
	   strcat(str1, "Content-Type: application/x-www-form-urlencoded\n");
	   strcat(str1, "Content-Length: ");
	   strcat(str1, len_str);
	   strcat(str1, "\n\n");

	   strcat(str1, str2);
	   strcat(str1, "\r\n\r\n");

	   printf("[Send scan data]:\n%s\n\n",str1);

	   ret = SendDataToServer(str1,strlen(str1));
	   if (ret < 0) {
			   printf("消息发送失败！错误代码:%d，错误信息:'%s'\n",errno, strerror(errno));
			   exit(0);
	   }else{
			   printf("消息发送成功，共发送 %d 字节！\n\n", ret);
	   }


	   return 0;
}



int SendKeyValueData(char* inBuffer)
{
	int ret = 0;
	char len_str[10];//存放一个数:数据的长度
	char str1[BUF_SIZE*4];
	char str2[BUF_SIZE];
	char buf[BUF_SIZE];
	int len = 0;

	   
	   int sock_fd = 0;

	   sock_fd = TcpSocketInit(SERVER_IP, SERVER_PORT);//初始化套接口
	   if (TcpGetConnect(sock_fd) == 0)		   puts("Link server succeed");

		//发送数据
	   memset(str2, 0, sizeof(str2));
	   sprintf(str2, "obj_id=11&k=bp_meter&v=Hp=%d,Lp=%d,Heart=%d,Hab=%d&type=AR", inBuffer[4],inBuffer[5],inBuffer[6],inBuffer[7]);//  //obj_id    title    content
	   len = strlen(str2);

	   sprintf(len_str, "%d", len);

	   memset(str1, 0, sizeof(str1));
	   strcat(str1, "POST http://10.10.1.125:8080/NiotService/kv/addKV.do HTTP/1.1\n");
	   strcat(str1, "Host: 10.10.1.125\n");
	   strcat(str1, "Content-Type: application/x-www-form-urlencoded\n");
	   strcat(str1, "Content-Length: ");
	   strcat(str1, len_str);
	   strcat(str1, "\n\n");

	   strcat(str1, str2);
	   strcat(str1, "\r\n\r\n");

	   printf("[Send scan data]:\n%s\n\n",str1);

	   ret = SendDataToServer(str1,strlen(str1));
	   if (ret < 0) {
			   printf("消息发送失败！错误代码:%d，错误信息:'%s'\n",errno, strerror(errno));
			   exit(0);
	   }else{
			   printf("消息发送成功，共发送 %d 字节！\n\n", ret);
	   }


	   return 0;
}



void UdpRecvMessage(int sockfd)
{
	 struct sockaddr_in addr;
	 int addrlen = 0;
	 int n = 0;
	 char msg[MAX_MSG_SIZE] = {0};

	 addrlen = sizeof(struct sockaddr);
	 
	 puts("UdpServer running!");
	 
	 while(1)
	 { 
		  bzero(msg,sizeof(msg)); // 初始化,清零		  
		  n=recvfrom(sockfd,msg,MAX_MSG_SIZE,0,(struct sockaddr*)&addr,&addrlen); // 从客户端接收消息
		  msg[n]=0; //添加结束符'\0'
		  fprintf(stdout,"UdpServer has received: %s \n",msg); // 显示接收的消息
		  
		  if (strcmp(msg,"device=bpmeter&method=measure") == 0)
		  {
		  	SetBtMeasureFlag(); 
		  }
	 }
}


int ThreadUdpServer(void)
{
	 int sockfd = 0;
	 struct sockaddr_in addr;
	 
	 sockfd = socket(AF_INET,SOCK_DGRAM,0);
	 if (sockfd < 0)
	 {
		  fprintf(stderr,"Socket Error:%s\n",strerror(errno));
		  exit(1);
	 }
	 
	 // 服务器端填充 sockaddr结构
	 bzero(&addr,sizeof(struct sockaddr_in));
	 addr.sin_family=AF_INET;
	 addr.sin_addr.s_addr=htonl(INADDR_ANY);
	 addr.sin_port=htons(UDP_SERVER_PORT);
	 
	 // 捆绑sockfd描述符 
	 if(bind(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) < 0)
	 {
		  fprintf(stderr,"Bind Error:%s\n",strerror(errno));
		  exit(1);
	 }
	 
	 UdpRecvMessage(sockfd); // 进行读写操作

	 close(sockfd);

	 return 0;
}



int UdpServer(void)
{
	int id_udp_server;
	if(pthread_create(&id_udp_server,NULL, (void*(*)(void*))ThreadUdpServer, NULL))
	{
		 return(PrintError("create ThreadSerialScanCode error"));
	}
	pthread_detach(id_udp_server);
	return 0;
}




