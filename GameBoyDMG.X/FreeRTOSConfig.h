/*
 * FreeRTOS Kernel V10.0.0
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software. If you wish to use our Amazon
 * FreeRTOS name, please do so in a fair use way that does not cause confusion.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*
 * #define TCB_t to avoid conflicts between the
 * FreeRTOS task control block type (TCB_t) and the
 * AVR Timer Counter B type (TCB_t)
 */
#define TCB_t avrTCB_t
#include <avr/io.h>
#undef TCB_t

#define configUSE_PREEMPTION 1
#define configCPU_CLOCK_HZ 20e6
#define configTICK_RATE_HZ 1000
#define configMAX_PRIORITIES 4
#define configMINIMAL_STACK_SIZE 115
#define configMAX_TASK_NAME_LEN 8
#define configUSE_16_BIT_TICKS 1
#define configIDLE_SHOULD_YIELD 1
#define configUSE_TASK_NOTIFICATIONS 1
#define configUSE_MUTEXES 1
#define configUSE_RECURSIVE_MUTEXES 0
#define configUSE_COUNTING_SEMAPHORES 0
#define configQUEUE_REGISTRY_SIZE 0
#define configUSE_QUEUE_SETS 0
#define configUSE_TIME_SLICING 1
#define configUSE_NEWLIB_REENTRANT 0
#define configENABLE_BACKWARD_COMPATIBILITY 0
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 0

/* Memory allocation related definitions. */
#define configSUPPORT_STATIC_ALLOCATION 0
#define configSUPPORT_DYNAMIC_ALLOCATION 1
#define configTOTAL_HEAP_SIZE 0x600
#define configAPPLICATION_ALLOCATED_HEAP 0

/* Hook function related definitions. */
#define configUSE_IDLE_HOOK 0
#define configUSE_TICK_HOOK 0
#define configCHECK_FOR_STACK_OVERFLOW 1
#define configUSE_MALLOC_FAILED_HOOK 0
#define configUSE_DAEMON_TASK_STARTUP_HOOK 0

/* Run time and task stats gathering related definitions. */
#define configGENERATE_RUN_TIME_STATS 0
#define configUSE_TRACE_FACILITY 0
#define configUSE_STATS_FORMATTING_FUNCTIONS 0

/* Co-routine related definitions. */
#define configUSE_CO_ROUTINES 0
#define configMAX_CO_ROUTINE_PRIORITIES 1

/* Software timer related definitions. */
#define configUSE_TIMERS 0
#define configTIMER_TASK_PRIORITY 3
#define configTIMER_QUEUE_LENGTH 10
#define configTIMER_TASK_STACK_DEPTH configMINIMAL_STACK_SIZE

/* Define to trap errors during development. */
//#define configASSERT(  x  ) if( ( x ) == 0 ) { asm volatile ("cli"); while(1){ asm volatile ("BREAK"); } }

/* Optional functions - most linkers will remove unused functions anyway. */
#define INCLUDE_vTaskPrioritySet 0
#define INCLUDE_uxTaskPriorityGet 0
#define INCLUDE_vTaskDelete 1
#define INCLUDE_vTaskSuspend 1
#define INCLUDE_xResumeFromISR 0
#define INCLUDE_vTaskDelayUntil 0
#define INCLUDE_vTaskDelay 1
#define INCLUDE_xTaskGetSchedulerState 0
#define INCLUDE_xTaskGetCurrentTaskHandle 0
#define INCLUDE_uxTaskGetStackHighWaterMark 0
#define INCLUDE_xTaskGetIdleTaskHandle 0
#define INCLUDE_eTaskGetState 0
#define INCLUDE_xEventGroupSetBitFromISR 0
#define INCLUDE_xTimerPendFunctionCall 0
#define INCLUDE_xTaskAbortDelay 0
#define INCLUDE_xTaskGetHandle 0
#define INCLUDE_xTaskResumeFromISR 0

#define pdMS_TO_TICKS(xTimeInMs) ((TickType_t)(((uint32_t)(xTimeInMs) * (uint32_t)configTICK_RATE_HZ) / (uint32_t)1000))

#endif /* FREERTOS_CONFIG_H */
