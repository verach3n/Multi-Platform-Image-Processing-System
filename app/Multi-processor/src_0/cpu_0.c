#include <stdio.h>
#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "io.h"

#include "altera_avalon_performance_counter.h"
//#include "includes.h"
#include "sys/alt_irq.h"
#include "sys/alt_alarm.h"

#include "images_alt.h"
#include "sram2sm.h"

#define TRUE 1
#define SECTION_1 1

extern void delay (int millisec);

int main()
{
	//printf("Hello from cpu_0!\n");
	int current_image=0;
	while (1)
	{ 
		PERF_RESET(PERFORMANCE_COUNTER_0_BASE);
		PERF_START_MEASURING (PERFORMANCE_COUNTER_0_BASE);
		PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, SECTION_1);

		sram2sm_p3(sequence1[current_image]);
		delay(750);
		
		PERF_END(PERFORMANCE_COUNTER_0_BASE, SECTION_1); 
		perf_print_formatted_report
		(PERFORMANCE_COUNTER_0_BASE,            
		ALT_CPU_FREQ,        // defined in "system.h"
		1,                   // How many sections to print
		"Section 1"        // Display-name of section(s).
		);   

		current_image = (current_image+1) % sequence1_length;
	}
 	return 0;
}
