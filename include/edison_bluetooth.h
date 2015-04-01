/*
 * edison_bluetooth.h
 *
 *  Created on: 2015Äê3ÔÂ25ÈÕ
 *      Author: jh
 */

#ifndef EDISON_BLUETOOTH_H_
#define EDISON_BLUETOOTH_H_




#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>



#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#define BT_MAC "98:D3:31:B3:38:A2" //BOLUTEK
//#define BT_MAC "F8:A4:5F:04:46:06" //zhq


void SetBtMeasureFlag(void);

void ClrBtMeasureFlag(void);

int BluetoothDev(void);




#endif /* EDISON_BLUETOOTH_H_ */
