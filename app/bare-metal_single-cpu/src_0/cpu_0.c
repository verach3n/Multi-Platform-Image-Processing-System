#include "altera_avalon_performance_counter.h"
#include "system.h"
#include <stdio.h>
#include "imageprocessing.h"
#include "images_alt.h"

#define SECTION_1 1
//#define SECTION_2 2
//#define SECTION_3 3

#define dimX 32
#define dimY 32


int main()
{ 
  int current_image=0;
  unsigned char* graydata;
  while(1)
  {
	PERF_RESET(PERFORMANCE_COUNTER_0_BASE);
	PERF_START_MEASURING (PERFORMANCE_COUNTER_0_BASE);
	PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, SECTION_1);

	graydata = malloc(dimX * dimY *sizeof(unsigned char));
	grayscale(sequence1[current_image], graydata);
	printf("current image is: %d\n", current_image);
	printAscii(graydata, dimX, dimY);

	PERF_END(PERFORMANCE_COUNTER_0_BASE, SECTION_1);  

	/* Print report */
	perf_print_formatted_report
	(PERFORMANCE_COUNTER_0_BASE,            
	ALT_CPU_FREQ,        // defined in "system.h"
	1,                   // How many sections to print
	"Section 1"        // Display-name of section(s).
	);   

	current_image=(current_image+1) % sequence1_length;	
  }
  return 0;
}
