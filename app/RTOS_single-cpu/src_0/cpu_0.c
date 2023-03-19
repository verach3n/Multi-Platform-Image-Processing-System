// Skeleton for lab 2
// 
// Task 1 writes periodically RGB-images to the shared memory
//
// No guarantees provided - if bugs are detected, report them in the Issue tracker of the github repository!

#include <stdio.h>
#include <stdlib.h>
#include "altera_avalon_performance_counter.h"
#include "includes.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include "sys/alt_alarm.h"
#include "system.h"
#include "io.h"

#include "images_alt.h"
#include "imageprocessing.h"

#define DEBUG 1

#define QUEUE_SIZE 1024

#define HW_TIMER_PERIOD 100 /* 100ms */

/* Definition of Task Stacks */
#define   TASK_STACKSIZE       2048
//OS_STK    task1_stk[TASK_STACKSIZE];
OS_STK    task2_stk[TASK_STACKSIZE];
OS_STK    task3_stk[TASK_STACKSIZE];
OS_STK    StartTask_Stack[TASK_STACKSIZE]; 

/* Definition of Task Priorities */

#define STARTTASK_PRIO      1
//#define TASK1_PRIORITY      10
#define TASK2_PRIORITY      15
#define TASK3_PRIORITY      16

/* Definition of Task Periods (ms) */
//#define TASK1_PERIOD 10000
#define TASK2_PERIOD 10000
#define TASK3_PERIOD 10000

#define SECTION_1 1

/*
 * Global variables
 */
int delay; // Delay of HW-timer 

/*
 * ISR for HW Timer
 */
alt_u32 alarm_handler(void* context)
{
  OSTmrSignal(); /* Signals a 'tick' to the SW timers */
  
  return delay;
}

// Semaphores
//OS_EVENT *Task1TmrSem;
OS_EVENT *Task2TmrSem;
OS_EVENT *Task3TmrSem;

// Message Queue
OS_EVENT *CommQ;

// SW-Timer
//OS_TMR *Task1Tmr;
OS_TMR *Task2Tmr;
OS_TMR *Task3Tmr;

/* Timer Callback Functions */ 
//void Task1TmrCallback (void *ptmr, void *callback_arg){
//  OSSemPost(Task1TmrSem);
//}

void Task2TmrCallback (void *ptmr, void *callback_arg){
  OSSemPost(Task2TmrSem);
}

void Task3TmrCallback (void *ptmr, void *callback_arg){
  OSSemPost(Task3TmrSem);
}


//Task2: graySDF
void task2(void* pdata)
{
	INT8U err;
	INT8U current_image=0;
	unsigned char* graydata;

	while(1)
	{
		printf("task 2 start!\n");
		/* Extract the x and y dimensions of the picture */
		unsigned char i = *sequence1[current_image];
		unsigned char j = *(sequence1[current_image]+1);

		PERF_RESET(PERFORMANCE_COUNTER_0_BASE);
		PERF_START_MEASURING (PERFORMANCE_COUNTER_0_BASE);
		PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, SECTION_1);

		graydata = malloc((int)i * (int)j *sizeof(unsigned char));
		/* Measurement here */
		grayscale(sequence1[current_image], graydata);
		//printf("pixel: %f, %f, %f\n", (float)graydata[0],(float)graydata[1],(float)graydata[2]);
		err = OSQPost(CommQ, (void *)graydata);
		//if(err == OS_ERR_Q_FULL){printf("queue is full!");}
  		free(graydata);

		OSSemPend(Task2TmrSem, 0, &err);

		/* Increment the image pointer */
		current_image=(current_image+1) % sequence1_length;
	}
}

void task3(void* pdata)
{
	INT8U err;
	void* msg;
	unsigned char* gray;

	while(1)
	{ 
		printf("task 3 start!\n");
		msg = OSQPend(CommQ, 0, &err);
		gray = (unsigned char*) msg;
		//printf("pixel2: %f, %f, %f\n", (float)gray[0],(float)gray[1],(float)gray[2]);
		printAscii(gray, 32, 32);

		PERF_END(PERFORMANCE_COUNTER_0_BASE, SECTION_1);  

		/* Print report */
		perf_print_formatted_report
		(PERFORMANCE_COUNTER_0_BASE,            
		ALT_CPU_FREQ,        // defined in "system.h"
		1,                   // How many sections to print
		"Section 1"        // Display-name of section(s).
		); 
		
		OSSemPend(Task3TmrSem, 0, &err);
	}
}


void StartTask(void* pdata)
{
  INT8U err;
  void* context;
  void* CommMsg[QUEUE_SIZE];

  static alt_alarm alarm;     /* Is needed for timer ISR function */
  
  /* Base resolution for SW timer : HW_TIMER_PERIOD ms */
  delay = alt_ticks_per_second() * HW_TIMER_PERIOD / 1000; 
  printf("delay in ticks %d\n", delay);

  /* 
   * Create Hardware Timer with a period of 'delay' 
   */
  if (alt_alarm_start (&alarm,
      delay,
      alarm_handler,
      context) < 0)
      {
          printf("No system clock available!n");
      }

  /* 
   * Create and start Software Timer 
   */

   //Create Task1 Timer
   /*Task1Tmr = OSTmrCreate(0, //delay
                            TASK1_PERIOD/HW_TIMER_PERIOD, //period
                            OS_TMR_OPT_PERIODIC,
                            Task1TmrCallback, //OS_TMR_CALLBACK
                            (void *)0,
                            "Task1Tmr",
                            &err);*/
   Task2Tmr = OSTmrCreate(0, //delay
                            TASK2_PERIOD/HW_TIMER_PERIOD, //period
                            OS_TMR_OPT_PERIODIC,
                            Task2TmrCallback, //OS_TMR_CALLBACK
                            (void *)0,
                            "Task2Tmr",
                            &err);
   Task3Tmr = OSTmrCreate(0, //delay
                            TASK3_PERIOD/HW_TIMER_PERIOD, //period
                            OS_TMR_OPT_PERIODIC,
                            Task3TmrCallback, //OS_TMR_CALLBACK
                            (void *)0,
                            "Task3Tmr",
                            &err);
   

   /*
    * Start timers
    */
   
   //start Task1 Timer
   //OSTmrStart(Task1Tmr, &err);
   OSTmrStart(Task2Tmr, &err);
   OSTmrStart(Task3Tmr, &err);

   /*
   * Creation of Kernel Objects
   */
  // Semaphore
  //Task1TmrSem = OSSemCreate(0);
  Task2TmrSem = OSSemCreate(0);
  Task3TmrSem = OSSemCreate(0); 

  // Message Queue
  CommQ = OSQCreate(&CommMsg[0], QUEUE_SIZE);    

  /*
   * Create statistics task
   */

  OSStatInit();

  /* 
   * Creating Tasks in the system 
   */

  /*err=OSTaskCreateExt(task1,
                  NULL,
                  (void *)&task1_stk[TASK_STACKSIZE-1],
                  TASK1_PRIORITY,
                  TASK1_PRIORITY,
                  task1_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);*/

  err=OSTaskCreateExt(task2,
                  NULL,
                  (void *)&task2_stk[TASK_STACKSIZE-1],
                  TASK2_PRIORITY,
                  TASK2_PRIORITY,
                  task2_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
  
  err=OSTaskCreateExt(task3,
                  NULL,
                  (void *)&task3_stk[TASK_STACKSIZE-1],
                  TASK3_PRIORITY,
                  TASK3_PRIORITY,
                  task3_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

  printf("All Tasks and Kernel Objects generated!\n");

  /* Task deletes itself */

  OSTaskDel(OS_PRIO_SELF);
}


int main(void) {

  printf("MicroC/OS-II-Vesion: %1.2f\n", (double) OSVersion()/100.0);
     
  OSTaskCreateExt(
	 StartTask, // Pointer to task code
         NULL,      // Pointer to argument that is
                    // passed to task
         (void *)&StartTask_Stack[TASK_STACKSIZE-1], // Pointer to top
						     // of task stack 
         STARTTASK_PRIO,
         STARTTASK_PRIO,
         (void *)&StartTask_Stack[0],
         TASK_STACKSIZE,
         (void *) 0,  
         OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
         
  OSStart();
  
  return 0;
}
