// SPDX-FileCopyrightText: 2000 Argonne National Laboratory
//
// SPDX-License-Identifier: EPICS

/* NIUSB6501Main.cpp */
/* Author:  Marty Kraimer Date:    17MAR2000 */

#include <stddef.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#include "epicsExit.h"
#include "epicsThread.h"
#include "iocsh.h"
#include <usb.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include "niusb6501.h"
struct usb_device *niusb_dev;
struct usb_dev_handle *niusb_handle;
bool NoUSB6501;
unsigned char niusb_port0,niusb_port1,niusb_port2;
unsigned char port0_mode, port1_mode, port2_mode;
unsigned char port0_RB, port1_RB, port2_RB;


int main(int argc,char *argv[])
{
    NoUSB6501=false;
	if(niusb6501_list_devices(&niusb_dev, 1) != 1)
	{
		fprintf(stderr, "Device not found\n");
		NoUSB6501=true;
	}
    if(NoUSB6501==false ) {
        niusb_handle = niusb6501_open_device(niusb_dev);
        if (niusb_handle == NULL)
        {
            fprintf(stderr, "Unable to open the USB device: %s\n", strerror(errno));
    		NoUSB6501=true;
        }
    }
    FILE *fp;
    fp=fopen("hwstatus.txt","wt");
    if(fp==NULL) {
        printf("Unable to open file!");
        return 0;
    }
    port0_mode=0xff;
    port1_mode=0xff;
    port2_mode=0xff;
    if(NoUSB6501==false) {
        niusb6501_set_io_mode(niusb_handle, 0xff, 0xff, 0xff);
        fprintf(fp,"epicsEnvSet HasNIUSB6501 Yes\n");
    }
    else {
        fprintf(fp,"epicsEnvSet HasNIUSB6501 No\n");
    }
    fclose(fp);
    
    if(argc>=2) {
        iocsh(argv[1]);
        epicsThreadSleep(.2);
    }
    iocsh(NULL);
    epicsExit(0);
	niusb6501_close_device(niusb_handle);
    
    return(0);
}


extern "C" {
void SetBVal(int ChIndx,long val);
long GetBVal(int ChIndx);
void SetDirection(int ChIndx,long val);

void SetDirection(int ChIndx, long val)
{
    unsigned char mask,mask1;
    int port,pos;
    port= floor(ChIndx /8);
    pos=ChIndx % 8;
    mask=1<<pos;
    mask1=~mask;
    switch (port) {
        case 0:
            if(val==0) {
                port0_mode &= mask1 ;
            }
            else {
                port0_mode |= mask;
            }
            break;
        case 1:
            if(val==0) {
                port1_mode &= mask1 ;
            }
            else {
                port1_mode |= mask;
            }
            break;
        case 2:
            if(val==0) {
                port2_mode &= mask1 ;
            }
            else {
                port2_mode |= mask;
            }
            break;
        default:;
    }
	niusb6501_set_io_mode(niusb_handle, port0_mode, port1_mode, port2_mode);
    return ;    
}
	


void SetBVal(int ChIndx,long val) 
{
    unsigned char mask,mask1;
    int port,pos;
    port= floor(ChIndx /8);
    pos=ChIndx % 8;
    mask=1<<pos;
    mask1=~mask;
    switch (port) {
        case 0:
            if(val==0) {
                niusb_port0 &= mask1 ;
            }
            else {
                niusb_port0 |= mask;
            }
            niusb6501_write_port(niusb_handle,0,niusb_port0);
            break;
        case 1:
            if(val==0) {
                niusb_port1 &= mask1 ;
            }
            else {
                niusb_port1 |= mask;
            }
            niusb6501_write_port(niusb_handle,1,niusb_port1);
            break;
        case 2:
            if(val==0) {
                niusb_port2 &= mask1 ;
            }
            else {
                niusb_port2 |= mask;
            }
            niusb6501_write_port(niusb_handle,2,niusb_port2);
            break;
        default:;
    }
//    printf("%x, %x, %x\n", niusb_port0,niusb_port1,niusb_port2);
    return ;    
}

long GetBVal(int ChIndx)
{
    unsigned char mask,rval;
    int port,pos;
    int status;
    port= floor(ChIndx /8);
    
    pos=ChIndx % 8;
    mask=1<<pos;
    if(ChIndx<0) {
            status=niusb6501_read_port(niusb_handle,0,&port0_RB);
            if(status)
			{
				fprintf(stderr, "error write port 0: %s\n", strerror(-status));
			}

            status=niusb6501_read_port(niusb_handle,1,&port1_RB);
            if(status)
			{
				fprintf(stderr, "error write port 1: %s\n", strerror(-status));
			}
            status=niusb6501_read_port(niusb_handle,2,&port2_RB);
            if(status)
			{
				fprintf(stderr, "error write port 2: %s\n", strerror(-status));
			}
			return 0;
	}
			
    switch (port) {
        case 0:
            rval=port0_RB & mask;
            break;
        case 1:
            rval=port1_RB & mask;
            break;
        case 2:
            rval=port2_RB & mask;
            break;
        default:
            rval=0;
        }
    return rval;        
}
    
}
