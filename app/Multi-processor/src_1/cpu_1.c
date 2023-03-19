#include <stdio.h>
#include "system.h"
#include "io.h"

//#include "altera_avalon_performance_counter.h"
//#include "includes.h"
#include "sys/alt_irq.h"
#include "sys/alt_alarm.h"

#include "grayscale.h"

#define TRUE 1
#define dimX 32
#define dimY 32

extern void delay (int millisec);


int main()
{
  	//printf("Hello from cpu_1!\n");
	unsigned char* graydata;
	unsigned char* shared;
	delay(100);
	while (TRUE) 
	{
		shared = (unsigned char*) SHARED_ONCHIP_BASE;
		graydata = shared + dimX*dimY*3 + 3;
		grayscale(shared, graydata);
		delay(1000);
	}
  return 0;
}
