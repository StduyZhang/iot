


//���л�edison������Ŀ��أ����ó�����ģʽ

#include "usbhost.h"
#include "udp_server.h"
#include "stdbool.h"


#include "my_sqlite.h"






/*�����
void led_init( mraa_gpio_context gpio)
{
   gpio = mraa_gpio_init(13);
   mraa_gpio_dir(gpio, MRAA_GPIO_OUT);
}

void led_blink(mraa_gpio_context gpio)
{
	static int ledstate = 0;
	ledstate = !ledstate;
	mraa_gpio_write(gpio, ledstate);
}
*/






unsigned char NumToChar(int value)
{
   	unsigned char tmp = 0;

   	switch(value)
   	{
   	case  KEY_0:	tmp = '0'; break;
   	case  KEY_1:	tmp = '1'; break;
   	case  KEY_2:	tmp = '2'; break;
   	case  KEY_3:	tmp = '3'; break;
   	case  KEY_4:	tmp = '4'; break;
   	case  KEY_5:	tmp = '5'; break;
   	case  KEY_6:	tmp = '6'; break;
   	case  KEY_7:	tmp = '7'; break;
   	case  KEY_8:	tmp = '8'; break;
   	case  KEY_9:	tmp = '9'; break;
	
   	case  KEY_A:	tmp = 'a'; break;
   	case  KEY_B:	tmp = 'b'; break;
   	case  KEY_C:	tmp = 'c'; break;
   	case  KEY_D:	tmp = 'd'; break;
   	case  KEY_E:	tmp = 'e'; break;
   	case  KEY_F:	tmp = 'f'; break;
   	case  KEY_G:	tmp = 'g'; break;
	
	case  KEY_H:	tmp = 'h'; break;
   	case  KEY_I:	tmp = 'i'; break;
   	case  KEY_J:	tmp = 'j'; break;
   	case  KEY_K:	tmp = 'k'; break;
   	case  KEY_L:	tmp = 'l'; break;
   	case  KEY_M:	tmp = 'm'; break;
   	case  KEY_N:	tmp = 'n'; break;

 	case  KEY_O:	tmp = 'o'; break;
   	case  KEY_P:	tmp = 'p'; break;
   	case  KEY_Q:	tmp = 'q'; break;
   	case  KEY_R:	tmp = 'r'; break;
   	case  KEY_S:	tmp = 's'; break;
   	case  KEY_T:	tmp = 't'; break;
	
   	case  KEY_U:	tmp = 'u'; break;
	case  KEY_V:	tmp = 'v'; break;
   	case  KEY_W:	tmp = 'w'; break;
   	case  KEY_X:	tmp = 'x'; break;
   	case  KEY_Y:	tmp = 'y'; break;
   	case  KEY_Z:	tmp = 'z'; break;
	

	case  KEY_MINUS:		tmp = '-'; break;
	case  KEY_EQUAL:		tmp = '='; break;
	case  KEY_SPACE:		tmp = ' '; break;

	case  KEY_LEFTBRACE:	tmp = '['; break;
	case  KEY_RIGHTBRACE:	tmp = ']'; break;
	
	case  KEY_BACKSLASH:	tmp = '\\'; break;//ת��	
	case  KEY_APOSTROPHE:	tmp = '\''; break;//ת��
	case  KEY_ENTER:		tmp = '\r'; break;//�س�

	case  KEY_SEMICOLON:	tmp = ';'; break;
	case  KEY_COMMA:		tmp = ','; break;	
	case  KEY_DOT:			tmp = '.'; break;
	case  KEY_SLASH:		tmp = '/'; break;
	
	case  KEY_GRAVE:		tmp = '`'; break;


	//KEY_LEFTSHIFT
	//KEY_RIGHTSHIFT

	default: 				tmp = ' '; break;//

   	}
	return tmp;
}

unsigned char ShiftNumToChar(int value)  //���������ϵ������ַ�
{
   	unsigned char tmp = 0;

   	switch(value)
   	{
   	case  KEY_0:	tmp = ')'; break;
   	case  KEY_1:	tmp = '!'; break;
   	case  KEY_2:	tmp = '@'; break;
   	case  KEY_3:	tmp = '#'; break;
   	case  KEY_4:	tmp = '$'; break;
   	case  KEY_5:	tmp = '%'; break;
   	case  KEY_6:	tmp = '^'; break;
   	case  KEY_7:	tmp = '&'; break;
   	case  KEY_8:	tmp = '*'; break;
   	case  KEY_9:	tmp = '('; break;
		
   	case  KEY_A:	tmp = 'A'; break;
   	case  KEY_B:	tmp = 'B'; break;
   	case  KEY_C:	tmp = 'C'; break;
   	case  KEY_D:	tmp = 'D'; break;
   	case  KEY_E:	tmp = 'E'; break;
   	case  KEY_F:	tmp = 'F'; break;
   	case  KEY_G:	tmp = 'G'; break;
	
	case  KEY_H:	tmp = 'H'; break;
   	case  KEY_I:	tmp = 'I'; break;
   	case  KEY_J:	tmp = 'J'; break;
   	case  KEY_K:	tmp = 'K'; break;
   	case  KEY_L:	tmp = 'L'; break;
   	case  KEY_M:	tmp = 'M'; break;
   	case  KEY_N:	tmp = 'N'; break;

 	case  KEY_O:	tmp = 'O'; break;
   	case  KEY_P:	tmp = 'P'; break;
   	case  KEY_Q:	tmp = 'Q'; break;
   	case  KEY_R:	tmp = 'R'; break;
   	case  KEY_S:	tmp = 'S'; break;
   	case  KEY_T:	tmp = 'T'; break;
	
   	case  KEY_U:	tmp = 'U'; break;
	case  KEY_V:	tmp = 'V'; break;
   	case  KEY_W:	tmp = 'W'; break;
   	case  KEY_X:	tmp = 'X'; break;
   	case  KEY_Y:	tmp = 'Y'; break;
   	case  KEY_Z:	tmp = 'Z'; break;

	case  KEY_MINUS:		tmp = '_'; break;
	case  KEY_EQUAL:		tmp = '+'; break;
	

	case  KEY_LEFTBRACE:	tmp = '{'; break;
	case  KEY_RIGHTBRACE:	tmp = '}'; break;
	
	case  KEY_BACKSLASH:	tmp = '|'; break;//ת��	
	case  KEY_APOSTROPHE:	tmp = '"'; break;//ת��
	
	case  KEY_SEMICOLON:	tmp = ':'; break;
	case  KEY_COMMA:		tmp = '<'; break;	
	case  KEY_DOT:			tmp = '>'; break;
	case  KEY_SLASH:		tmp = '?'; break;

	case  KEY_GRAVE:		tmp = '~'; break;

	//KEY_LEFTSHIFT
	//KEY_RIGHTSHIFT

	default: 				tmp = ' '; break;//

   	}
	return tmp;
}




save_client_infor(const char *p)
{		 
	 sqlite_update_tcp_table("area",  p); 	
	 puts("save area information OK!");
}


int ThreadUsbHost(void)
{	
	struct input_event buff;
	int usb_fd;

	time_t t_start = 0, t_tmp = 0, t_date = 0;
	struct tm *local_t;
	
	int   ledstate = 0;
	bool scan_flag = FALSE;	

	char *ptr = NULL;
	char info_str[256] = {0};			
	char area_str[50] = "unknown area!please scan area code!";
	
	
	mraa_gpio_context gpio;
	gpio = mraa_gpio_init(13);
	mraa_gpio_dir(gpio, MRAA_GPIO_OUT);

	init_table();  //////////////



	usb_fd = open("/dev/input/event2", O_RDONLY|O_NONBLOCK);//������
       if (usb_fd < 0)
       {
           perror("can not open device usbkeyboard!");
           exit(1);
       }
   		
       puts("Usb scan device is running!\n");


    while(1)
    {
       if(read(usb_fd,&buff,sizeof(buff)) == sizeof(buff))//��������
       {	
       		if (scan_flag == FALSE)
       		{
       			scan_flag = TRUE;//ɨ���¼�����
       			t_start = time(NULL);				
			memset(info_str, 0, sizeof(info_str));	
			snprintf(info_str, sizeof(info_str), "info:");
       		}
			
       	   //printf("type:%d code:%d value:%d\n",buff.type,buff.code,buff.value);
       	   //��USB�ӿ��յ�������ת�����ַ���
    	      if ( (buff.type == EV_KEY) && (buff.value == 1) )//push down
    	     {
    	   	  if ((buff.code != KEY_LEFTSHIFT) && (buff.code != KEY_RIGHTSHIFT))//����shift ��
    	   	  {
    		  		//printf( "%c",NumToChar(buff.code));
					snprintf(info_str+strlen(info_str), sizeof(info_str), "%c", NumToChar(buff.code));
    	   	  }
			  
		  if ((buff.code == KEY_LEFTSHIFT) || (buff.code == KEY_RIGHTSHIFT))//����shift���Ľ���
		  {		 						
			while (1)
			{
			  	if (read(usb_fd, &buff, sizeof(buff)) == sizeof(buff)) 
			  	{					  		
					//printf("type:%d code:%d value:%d\n",buff.type,buff.code,buff.value);
					if ((buff.code != KEY_LEFTSHIFT) && (buff.code != KEY_RIGHTSHIFT) && (buff.type == EV_KEY) && (buff.value == 1) )//push down
		    	   		{
		    		  		//printf( "%c",ShiftNumToChar(buff.code));
						snprintf(info_str+strlen(info_str), sizeof(info_str), "%c", ShiftNumToChar(buff.code));
					}

					if (((buff.code == KEY_LEFTSHIFT) || (buff.code == KEY_RIGHTSHIFT)) && (buff.type == EV_KEY) && (buff.value == 0) )//shift key is up
					{
						break;
					}							
				 }
			}					
    	           }
    	       }		   
          }

	   
	   if (scan_flag == TRUE)//��ɨ������
	   {
		   if((time(NULL) - t_start) > 1) //ɨ����ɣ�   ��������ַ�����ʱ������2��
		   {
		   		scan_flag = FALSE;					
				//puts(info_str);
				
				//ɨ�����Ϣ��λ���룬���浱��λ����Ϣ				
				//if (strstr(info_str, "info:area") != NULL)//��ַ��Ϣ�趨��area��ͷ�����ַ����в���"info:area" ��
				if ((ptr=strstr(info_str, "FZED") )!= NULL)//test
				{
					//���뱾�����ݿ�
					memset(area_str, 0, sizeof(area_str));	
					snprintf(area_str, sizeof(area_str), "%s",ptr+4);//��ʱ�浽�ڴ�,��ַ��Ϣȥ��FZED����ptr+4��ʼ
					printf("Scanned area information!  area: %s\n",area_str);
					
					save_client_infor(area_str);
					
				}
				
				else//ɨ�������Ʒ��Ϣ������ʱ��ص���Ϣ�����͵���Դƽ̨
				{
					t_date = time(NULL);
					local_t = localtime(&t_date);

					snprintf(info_str+strlen(info_str), sizeof(info_str),
						"\ntime:%d.%d.%d %d:%d:%d\narea:%s\n",
						local_t->tm_year+1900, local_t->tm_mon+1,local_t->tm_mday,
						local_t->tm_hour, local_t->tm_min, local_t->tm_sec,
						area_str);//��ʱ���λ����Ϣ���뵽��Ʒ��Ϣ��
						
					puts(info_str);
					SendMessData(info_str);
				}
		   }
	   }
	   
	  if( (time(NULL) - t_tmp) > 1)//���2����˸
	   {
	   	  
		   t_tmp =  time(NULL);
		   ledstate = !ledstate;
		   mraa_gpio_write(gpio, ledstate);

	   }	 



    	   /*
    	   if ( (buff.type == EV_KEY) && ((buff.value == 0)||(buff.value == 1)) )
    	   {
    		   printf("key %d %s\n", buff.code, (buff.value) ? "Pressed" : "Released");
    		   //printf("type:%d code:%d value:%d\n",buff.type,buff.code,buff.value);
    		  // if (buff.code == KEY_ESC) break;
    	   }*/
        

       

    }

    close(usb_fd);
    return 1;
}



int UsbHost(void)
{
	pthread_t id_usb;

	if(pthread_create(&id_usb,NULL, (void*(*)(void*))ThreadUsbHost, NULL))
	{
		 puts("create ThreadUsbHost error");
	}
	pthread_detach(id_usb);
	return 0;
}



