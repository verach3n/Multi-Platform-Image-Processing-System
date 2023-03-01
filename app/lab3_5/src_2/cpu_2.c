#include <stdio.h>
#include "system.h"
#include "io.h"

//#include "altera_avalon_performance_counter.h"
//#include "includes.h"
#include "sys/alt_irq.h"
#include "sys/alt_alarm.h"

#include "resize.h"

#define TRUE 1
#define dimX 32
#define dimY 32

extern void delay (int millisec);


int main()
{
  //printf("Hello from cpu_2!\n");
	unsigned char* graydata;
	unsigned char* resizedata;
	unsigned char* shared;
	delay(200);
	while (TRUE) 
	{ /* ... */ 
		shared = (unsigned char*) SHARED_ONCHIP_BASE;
		graydata = shared + dimX*dimY*3 + 3;
		resizedata = graydata + dimX*dimY;
		resize(graydata, resizedata, dimX, dimY);
		delay(1000);
	}
  return 0;
}
