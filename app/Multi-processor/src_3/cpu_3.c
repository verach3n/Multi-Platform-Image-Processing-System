#include <stdio.h>
#include "system.h"
#include "io.h"

//#include "altera_avalon_performance_counter.h"
//#include "includes.h"
#include "sys/alt_irq.h"
#include "sys/alt_alarm.h"

#include "printAscii.h"

#define TRUE 1
#define dimX 32
#define dimY 32

extern void delay (int millisec);

int main()
{
  //printf("Hello from cpu_3!\n");
	unsigned char* resizedata;
	unsigned char* shared;
	delay(300);
	while (TRUE) 
	{ /* ... */ 
		shared = (unsigned char*) SHARED_ONCHIP_BASE;
		resizedata = shared + dimX*dimY*3 + 3 + dimX*dimY;
		printf("Processed Image:\n");
		printAscii(resizedata, dimX/2, dimY/2);
		delay(1000);
	}
  return 0;
}
