
#include "edison_serial.h"
#include "udp_server.h"


static struct sockaddr_in target_addr;


int sock_fd = 0;

int linkFlag = 0;

mraa_gpio_context gpioLed;

pthread_t id_serial;

/*******************************************************************
* ���ƣ�                  UART1_Open
* ���ܣ�                �򿪴��ڲ����ش����豸�ļ�����
* ��ڲ�����        fd    :�ļ�������     port :���ں�(ttyS0,ttyS1,ttyS2)
* ���ڲ�����        ��ȷ����Ϊ1�����󷵻�Ϊ0
*******************************************************************/
int UART1_Open(int fd,char* port)
{	
	 int stat = 0;
     fd = open( port, O_RDWR|O_NOCTTY|O_NDELAY);
     if (FALSE == fd)
     {
        perror("Can't Open Serial Port");
        return(FALSE);
     }
	 
     //�ָ�����Ϊ����״̬
     if(fcntl(fd, F_SETFL, 0) < 0)
	 {
        printf("fcntl failed!\n");
        return(FALSE);
     }
     else
     {
     	stat = fcntl(fd, F_SETFL,0);
        //printf("fcntl=%d\n",stat);//test
     }
	 
     //�����Ƿ�Ϊ�ն��豸
     if(0 == isatty(STDIN_FILENO))
     {
        printf("standard input is not a terminal device\n");
        return(FALSE);
     }
  	
	 
  	 //printf("fd->open=%d\n",fd);
  	 puts("Open Serial Port Succeed!");
  return fd;
  
}
/*******************************************************************
* ���ƣ�                UART1_Close
* ���ܣ�                �رմ��ڲ����ش����豸�ļ�����
* ��ڲ�����        fd    :�ļ�������     port :���ں�(ttyS0,ttyS1,ttyS2)
* ���ڲ�����        void
*******************************************************************/

void UART1_Close(int fd)
{
    close(fd);
}

/*******************************************************************
* ���ƣ�                UART1_Set
* ���ܣ�                ���ô�������λ��ֹͣλ��Ч��λ
* ��ڲ�����        fd        �����ļ�������
*                              speed     �����ٶ�
*                              flow_ctrl   ����������
*                           databits   ����λ   ȡֵΪ 7 ����8
*                           stopbits   ֹͣλ   ȡֵΪ 1 ����2
*                           parity     Ч������ ȡֵΪN,E,O,,S
*���ڲ�����          ��ȷ����Ϊ1�����󷵻�Ϊ0
*******************************************************************/
int UART1_Set(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity)
{

      int   i;
         int   status;
         int   speed_arr[] = { B115200, B19200, B9600, B4800, B2400, B1200, B300};
     int   name_arr[] = {115200,  19200,  9600,  4800,  2400,  1200,  300};

    struct termios options;

    /*tcgetattr(fd,&options)�õ���fdָ��������ز������������Ǳ�����options,�ú��������Բ��������Ƿ���ȷ���ô����Ƿ���õȡ������óɹ�����������ֵΪ0��������ʧ�ܣ���������ֵΪ1.
    */
    if  ( tcgetattr( fd,&options)  !=  0)
       {
          perror("SetupSerial 1");
          return(FALSE);
       }

    //���ô������벨���ʺ����������
    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)
                {
                     if  (speed == name_arr[i])
                            {
                                 cfsetispeed(&options, speed_arr[i]);
                                 cfsetospeed(&options, speed_arr[i]);
                            }
              }

    //�޸Ŀ���ģʽ����֤���򲻻�ռ�ô���
    options.c_cflag |= CLOCAL;
    //�޸Ŀ���ģʽ��ʹ���ܹ��Ӵ����ж�ȡ��������
    options.c_cflag |= CREAD;

    //��������������
    switch(flow_ctrl)
    {

       case 0 ://��ʹ��������
              options.c_cflag &= ~CRTSCTS;
              break;

       case 1 ://ʹ��Ӳ��������
              options.c_cflag |= CRTSCTS;
              break;
       case 2 ://ʹ�����������
              options.c_cflag |= IXON | IXOFF | IXANY;
              break;
    }
    //��������λ
    //����������־λ
    options.c_cflag &= ~CSIZE;
    switch (databits)
    {
       case 5    :
                     options.c_cflag |= CS5;
                     break;
       case 6    :
                     options.c_cflag |= CS6;
                     break;
       case 7    :
                 options.c_cflag |= CS7;
                 break;
       case 8:
                 options.c_cflag |= CS8;
                 break;
       default:
                 fprintf(stderr,"Unsupported data size\n");
                 return (FALSE);
    }
    //����У��λ
    switch (parity)
    {
       case 'n':
       case 'N': //����żУ��λ��
                 options.c_cflag &= ~PARENB;
                 options.c_iflag &= ~INPCK;
                 break;
       case 'o':
       case 'O'://����Ϊ��У��
                 options.c_cflag |= (PARODD | PARENB);
                 options.c_iflag |= INPCK;
                 break;
       case 'e':
       case 'E'://����ΪżУ��
                 options.c_cflag |= PARENB;
                 options.c_cflag &= ~PARODD;
                 options.c_iflag |= INPCK;
                 break;
       case 's':
       case 'S': //����Ϊ�ո�
                 options.c_cflag &= ~PARENB;
                 options.c_cflag &= ~CSTOPB;
                 break;
        default:
                 fprintf(stderr,"Unsupported parity\n");
                 return (FALSE);
    }
    // ����ֹͣλ
    switch (stopbits)
    {
       case 1:
                 options.c_cflag &= ~CSTOPB; break;
       case 2:
                 options.c_cflag |= CSTOPB; break;
       default:
                       fprintf(stderr,"Unsupported stop bits\n");
                       return (FALSE);
    }

  //�޸����ģʽ��ԭʼ�������
  options.c_oflag &= ~OPOST;

  options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);//�Ҽӵ�
//options.c_lflag &= ~(ISIG | ICANON);

    //���õȴ�ʱ�����С�����ַ�
    options.c_cc[VTIME] = 1; /* ��ȡһ���ַ��ȴ�1*(1/10)s */
    options.c_cc[VMIN] = 1; /* ��ȡ�ַ������ٸ���Ϊ1 */

    //�����������������������ݣ����ǲ��ٶ�ȡ ˢ���յ������ݵ��ǲ���
    tcflush(fd,TCIFLUSH);

    //�������� (���޸ĺ��termios�������õ������У�
    if (tcsetattr(fd,TCSANOW,&options) != 0)
           {
               perror("com set error!\n");
              return (FALSE);
           }
    return (TRUE);
}
/*******************************************************************
* ���ƣ�                UART1_Init()
* ���ܣ�                ���ڳ�ʼ��
* ��ڲ�����        fd       :  �ļ�������
*               speed  :  �����ٶ�
*                              flow_ctrl  ����������
*               databits   ����λ   ȡֵΪ 7 ����8
*                           stopbits   ֹͣλ   ȡֵΪ 1 ����2
*                           parity     Ч������ ȡֵΪN,E,O,,S
*
* ���ڲ�����        ��ȷ����Ϊ1�����󷵻�Ϊ0
*******************************************************************/
int UART1_Init(int fd, int speed,int flow_ctrl,int databits,int stopbits,int parity)
{
    int err;
    //���ô�������֡��ʽ
    if (UART1_Set(fd,speed, flow_ctrl, databits, stopbits,parity) == FALSE)
       {
        return FALSE;
       }
    else
       {
               return  TRUE;
        }
}

/*******************************************************************
* ���ƣ�                  UART1_Recv
* ���ܣ�                ���մ�������
* ��ڲ�����        fd                  :�ļ�������
*                              rcv_buf     :���մ��������ݴ���rcv_buf��������
*                              data_len    :һ֡���ݵĳ���
* ���ڲ�����        ��ȷ����Ϊ1�����󷵻�Ϊ0
*******************************************************************/
int UART1_Recv(int fd, char *rcv_buf,int data_len)
{
    int len,fs_sel;
    fd_set fs_read;

    struct timeval time;

    FD_ZERO(&fs_read);
    FD_SET(fd,&fs_read);

    time.tv_sec = 10;
    time.tv_usec = 0;

    //ʹ��selectʵ�ִ��ڵĶ�·ͨ��
    fs_sel = select(fd+1,&fs_read,NULL,NULL,&time);
    if(fs_sel)
       {
              len = read(fd,rcv_buf,data_len);
          printf("I am right!(version1.2) len = %d fs_sel = %d\n",len,fs_sel);
              return len;
       }
    else
       {
          //puts("Didn't get data!");
              return FALSE;
       }
}
/********************************************************************
* ���ƣ�                  UART1_Send
* ���ܣ�                ��������
* ��ڲ�����        fd                  :�ļ�������
*                              send_buf    :��Ŵ��ڷ�������
*                              data_len    :һ֡���ݵĸ���
* ���ڲ�����        ��ȷ����Ϊ1�����󷵻�Ϊ0
*******************************************************************/
int UART1_Send(int fd, char *send_buf,int data_len)
{
    int len = 0;

    len = write(fd,send_buf,data_len);
    if (len == data_len )
              {
                     return len;
              }
    else
        {

                tcflush(fd,TCOFLUSH);
                return FALSE;
        }

}






int PrintError(char * err)
{
	 fprintf(stderr,"%s:%s\n",err,strerror(errno));
	 return -1;
}

int TcpSocketInit(const char *ip,const char *port)
{
	 
	 struct timeval timeout={5,0};//5s  struct timeval{ long tv_sec; long tv_usec; };

	 if((sock_fd=socket(AF_INET,SOCK_STREAM,0))<0)
	 { return (PrintError("Socket Error")); }

	 memset(&target_addr,0,sizeof(struct sockaddr_in));
     target_addr.sin_family=AF_INET;
	 target_addr.sin_port=htons(atoi(port));
	 target_addr.sin_addr.s_addr=inet_addr(ip);

	 if(setsockopt(sock_fd, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout))!=0) //����������ʱ
	 { return (PrintError("setsockopt_send error!\n")); }

	 if(setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout))!=0)
	 { return (PrintError("setsockopt_recv error!\n")); }

	 return sock_fd;


}

int TcpGetConnect(int socket)
{
	 if(connect(socket,(struct sockaddr *)&target_addr,sizeof(struct sockaddr))==-1)
	 {
	 	PrintError("Connect Error");
		return -1;
	 }
	 else
	 {
	 	fprintf(stderr,"Client has connect to %s \n\n",inet_ntoa(target_addr.sin_addr));
	 }
	 return 0;
}


int SendDataToServer( char* buffer,int len)
{
	return(send(sock_fd,buffer,len,0));
}

int RecvDataFromServer(char* buffer, int len)
{
	memset(buffer,0,len);
	return(recv(sock_fd, buffer, len, 0));
}




int ScanCodeDevice(void)
{
	if(pthread_create(&id_serial,NULL, (void*(*)(void*))ThreadSerialScanCode, NULL))
	{
		 return(PrintError("create ThreadSerialScanCode error"));
	}
	pthread_detach(id_serial);
	return 0;
}


int ThreadSerialScanCode(void)
{
	 char serial_buf[100] = "hello";
	 int fd = 0;                            //�ļ�������
	 int err = 0;                           //���ص��ú�����״̬
	 int len = 0;

	 fd = UART1_Open(fd,SERIAL_DEV); //�򿪴��ڣ������ļ�������

	 do{
		   err = UART1_Init(fd,115200,0,8,1,'N');
		   puts("Serial initial success!\n");

	   }while(FALSE == err || FALSE == fd);
	 
/*
	    len = UART1_Send(fd,serial_buf,5);
	    
	    if(len > 0)
		     printf(" send data  successful\n");
	    else
		     printf("send data failed!\n");
*/



	puts("Serial scan device is running!\n");

	while(1)
	{		
	    len = UART1_Recv(fd, serial_buf,100);//���ڽ���100�ֽ�
	    if(len > 0)
	    {
		   serial_buf[len] = '\0';
	       printf("Received scan data : %s,len = %d\n",serial_buf,len);

		   SendMessData(serial_buf);
        }

		sleep(1);
	}

	//  UART1_Close(fd);
	return 0;

}


