/*
 * usbhost.h
 *
 *  Created on: 2015年4月29日
 *      Author: admin
 */


//包括gpio设备


#ifndef USBHOST_H_
#define USBHOST_H_




#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include <pthread.h>


#include "mraa/gpio.h"
#include "mraa.h"

#define TRUE   1
#define FALSE  0


int UsbHost(void);

void led_init( mraa_gpio_context gpio);

void led_blink(mraa_gpio_context gpio);


#endif /* USBHOST_H_ */
