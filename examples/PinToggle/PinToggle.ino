#include <Arduino_FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <timers.h>

#include "utils.h"

#include "vToggleCallback.h"
#include "vToggleDelay.h"
#include "vToggleDelayUntil.h"

/*

# vTaskDelay Method

https://www.freertos.org/a00127.html

void vTaskDelay( const TickType_t xTicksToDelay );

Delay a task for a given number of ticks. The actual time that the task remains blocked depends on the tick rate. The constant portTICK_PERIOD_MS can be used to
calculate real time from the tick rate - with the resolution of one tick period.

vTaskDelay() specifies a time at which the task wishes to unblock relative to the time at which vTaskDelay() is called. For example, specifying a block period
of 100 ticks will cause the task to unblock 100 ticks after vTaskDelay() is called. vTaskDelay() does not therefore provide a good method of controlling the
frequency of a periodic task as the path taken through the code, as well as other task and interrupt activity, will effect the frequency at which vTaskDelay()
gets called and therefore the time at which the task next executes. See vTaskDelayUntil() for an alternative API function designed to facilitate fixed frequency
execution. It does this by specifying an absolute time (rather than a relative time) at which the calling task should unblock.

*/

// Thread configuration
// Duration, in Ticks, for to wait for.
TickType_t __attribute__((section("CFG_TICKS0"))) ticks0 = 1;
TickType_t __attribute__((section("CFG_TICKS1"))) ticks1 = 2;
TickType_t __attribute__((section("CFG_TICKS2"))) ticks2 = 10;
TickType_t __attribute__((section("CFG_TICKS3"))) ticks3 = 100;
// Duration, in Ticks, to offset the start of the tasks.
TickType_t __attribute__((section("CFG_TICK_DELAY0"))) tick_delay0 = 0;
TickType_t __attribute__((section("CFG_TICK_DELAY1"))) tick_delay1 = 1;
TickType_t __attribute__((section("CFG_TICK_DELAY2"))) tick_delay2 = 2;
TickType_t __attribute__((section("CFG_TICK_DELAY3"))) tick_delay3 = 3;
// Duration, in Ticks, to offset the start of the tasks.
TaskCFG_t __attribute__((section("CFG_TASK_CFG1"))) task_cfg1 = {2, ticks0, tick_delay0};
TaskCFG_t __attribute__((section("CFG_TASK_CFG2"))) task_cfg2 = {3, ticks1, tick_delay1};
TaskCFG_t __attribute__((section("CFG_TASK_CFG3"))) task_cfg3 = {4, ticks2, tick_delay2};
TaskCFG_t __attribute__((section("CFG_TASK_CFG4"))) task_cfg4 = {5, ticks3, tick_delay3};

TickType_t __attribute__((section("CFG_TICKS"))) ticks[4] = {1, 2, 10, 100};
TickType_t __attribute__((section("CFG_TICK_DELAYS"))) tick_delays[4] = {0, 1, 2, 3};
TaskCFG_t __attribute__((section("CFG_TASK_CFGS"))) task_cfgs[4] = {
    {6, ticks[0], tick_delays[0]},
    {7, ticks[1], tick_delays[1]},
    {8, ticks[2], tick_delays[2]},
    {9, ticks[3], tick_delays[3]},
};

void vToggleDelay02(void *pvParameters) {
  static bool pin_state = false;
  // TaskCFG_t cfg;

  // cfg = ((TaskCFG_t)pvParameters);

  for (;;) {
    pin_state = !pin_state;
    digitalWrite(2, pin_state);
    vTaskDelay(1);
  }
  /* Tasks must not attempt to return from their implementing
  function or otherwise exit.  In newer FreeRTOS port
  attempting to do so will result in an configASSERT() being
  called if it is defined.  If it is necessary for a task to
  exit then have the task call vTaskDelete( NULL ) to ensure
  its exit is clean. */
  vTaskDelete(NULL);
}

void vToggleDelay03(void *pvParameters) {
  static bool pin_state = false;
  configASSERT(((uint32_t)pvParameters) == 1);
  for (;;) {
    pin_state = !pin_state;
    digitalWrite(3, pin_state);
    vTaskDelay(2);
  }
  /* Tasks must not attempt to return from their implementing
  function or otherwise exit.  In newer FreeRTOS port
  attempting to do so will result in an configASSERT() being
  called if it is defined.  If it is necessary for a task to
  exit then have the task call vTaskDelete( NULL ) to ensure
  its exit is clean. */
  vTaskDelete(NULL);
}

void vToggleDelay04(void *pvParameters) {
  static bool pin_state = false;
  configASSERT(((uint32_t)pvParameters) == 1);
  for (;;) {
    pin_state = !pin_state;
    digitalWrite(3, pin_state);
    vTaskDelay(100);
  }
  /* Tasks must not attempt to return from their implementing
  function or otherwise exit.  In newer FreeRTOS port
  attempting to do so will result in an configASSERT() being
  called if it is defined.  If it is necessary for a task to
  exit then have the task call vTaskDelete( NULL ) to ensure
  its exit is clean. */
  vTaskDelete(NULL);
}

void vToggleDelay05(void *pvParameters) {
  static bool pin_state = false;
  configASSERT(((uint32_t)pvParameters) == 1);
  for (;;) {
    pin_state = !pin_state;
    digitalWrite(5, pin_state);
    vTaskDelay(1000);
  }
  /* Tasks must not attempt to return from their implementing
  function or otherwise exit.  In newer FreeRTOS port
  attempting to do so will result in an configASSERT() being
  called if it is defined.  If it is necessary for a task to
  exit then have the task call vTaskDelete( NULL ) to ensure
  its exit is clean. */
  vTaskDelete(NULL);
}

void vToggleDelayUntil06(void *pvParameters) {
  // Pin Status
  static bool pin_state = false;

  // Initialise the xLastWakeTime variable with the current time.
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  uint32_t ticks;
  ticks = ((uint32_t)pvParameters);

  for (;;) {
    // Wait for the next cycle.
    vTaskDelayUntil(&xLastWakeTime, ticks);

    // Perform action here.
    pin_state = !pin_state;
    digitalWrite(6, pin_state);
  }
}

void vToggleDelayUntil07(void *pvParameters) {
  // Pin Status
  static bool pin_state = false;

  // Initialise the xLastWakeTime variable with the current time.
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  uint32_t ticks;
  ticks = ((uint32_t)pvParameters);

  for (;;) {
    // Wait for the next cycle.
    vTaskDelayUntil(&xLastWakeTime, ticks);

    // Perform action here.
    pin_state = !pin_state;
    digitalWrite(7, pin_state);
  }
}

void vToggleDelayUntil08(void *pvParameters) {
  // Pin Status
  static bool pin_state = false;

  // Initialise the xLastWakeTime variable with the current time.
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  uint32_t ticks;
  ticks = ((uint32_t)pvParameters);

  for (;;) {
    // Wait for the next cycle.
    vTaskDelayUntil(&xLastWakeTime, ticks);

    // Perform action here.
    pin_state = !pin_state;
    digitalWrite(8, pin_state);
  }
}

void vToggleDelayUntil09(void *pvParameters) {
  // Pin Status
  static bool pin_state = false;

  // Initialise the xLastWakeTime variable with the current time.
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  uint32_t ticks;
  ticks = ((uint32_t)pvParameters);

  for (;;) {
    // Wait for the next cycle.
    vTaskDelayUntil(&xLastWakeTime, ticks);

    // Perform action here.
    pin_state = !pin_state;
    digitalWrite(9, pin_state);
  }
}

void vToggleCallback10(TimerHandle_t xTimer) {

  /* Optionally do something if the pxTimer parameter is NULL. */
  configASSERT(pxTimer);
  static bool pin_state = false;
  // Get the timer ID.
  configASSERT((uint32_t)pvTimerGetTimerID(xTimer) == 10);

  pin_state = !pin_state;
  digitalWrite(10, pin_state);
}

void vToggleCallback11(TimerHandle_t xTimer) {

  /* Optionally do something if the pxTimer parameter is NULL. */
  configASSERT(pxTimer);

  static bool pin_state = false;

  configASSERT((uint32_t)pvTimerGetTimerID(xTimer) == 11);

  pin_state = !pin_state;
  digitalWrite(11, pin_state);
}

void vToggleCallback12(TimerHandle_t xTimer) {

  /* Optionally do something if the pxTimer parameter is NULL. */
  configASSERT(pxTimer);
  static bool pin_state = false;

  configASSERT((uint32_t)pvTimerGetTimerID(xTimer) == 12);

  pin_state = !pin_state;
  digitalWrite(12, pin_state);
}

void vToggleCallback13(TimerHandle_t xTimer) {

  /* Optionally do something if the pxTimer parameter is NULL. */
  configASSERT(pxTimer);
  static bool pin_state = false;

  // Get the timer ID.
  configASSERT((uint32_t)pvTimerGetTimerID(xTimer) == 13);

  pin_state = !pin_state;
  digitalWrite(13, pin_state);
}

TaskHandle_t xHandle = NULL;

typedef struct cfg_xTaskCreate {
  TaskFunction_t pvTaskCode;
  const char *const pcName;
  unsigned short usStackDepth;
  void *pvParameters;
  UBaseType_t uxPriority;
  TaskHandle_t *pxCreatedTask;
} cfg_xTaskCreate_t;

BaseType_t xTaskCreateCreate(cfg_xTaskCreate_t task) {
  BaseType_t xReturned;
  xReturned = xTaskCreate(task.pvTaskCode, task.pcName, task.usStackDepth, task.pvParameters, task.uxPriority, task.pxCreatedTask);
  return xReturned;
}

cfg_xTaskCreate_t cfg_task_create02 = {
    vToggleDelay02, (const portCHAR *)"vToggleDelay02", 128, (void *)1, 0, &xHandle,
};

cfg_xTaskCreate_t cfg_task_create03 = {
    vToggleDelay03, (const portCHAR *)"vToggleDelay03", 128, (void *)1, 0, &xHandle,
};

cfg_xTaskCreate_t cfg_task_create04 = {
    vToggleDelay04, (const portCHAR *)"vToggleDelay04", 128, (void *)1, 0, &xHandle,
};

cfg_xTaskCreate_t cfg_task_create05 = {
    vToggleDelay05, (const portCHAR *)"vToggleDelay05", 128, (void *)1, 0, &xHandle,
};

cfg_xTaskCreate_t __attribute__((section("CFG_TASK_CREATE06"))) cfg_task_create06 = {
    vToggleDelayUntil06, (const portCHAR *)"vToggleDelayUntil06", 128, (void *)ticks0, 2, &xHandle,
};

cfg_xTaskCreate_t __attribute__((section("CFG_TASK_CREATE07"))) cfg_task_create07 = {
    vToggleDelayUntil07, (const portCHAR *)"vToggleDelayUntil07", 128, (void *)ticks1, 2, &xHandle,
};

cfg_xTaskCreate_t __attribute__((section("CFG_TASK_CREATE08"))) cfg_task_create08 = {
    vToggleDelayUntil08, (const portCHAR *)"vToggleDelayUntil08", 128, (void *)ticks[2], 2, &xHandle,
};

cfg_xTaskCreate_t __attribute__((section("CFG_TASK_CREATE09"))) cfg_task_create09 = {
    vToggleDelayUntil09, (const portCHAR *)"vToggleDelayUntil09", 128, (void *)ticks[3], 2, &xHandle,
};

/*
 *
 *
 */

typedef struct cfg_xTimerCreate {
  const char *const pcTimerName;
  const TickType_t xTimerPeriod;
  const UBaseType_t uxAutoReload;
  void *const pvTimerID;
  TimerCallbackFunction_t pxCallbackFunction;
} cfg_xTimerCreate_t;

TimerHandle_t xTimerCreateCreate(cfg_xTimerCreate_t timer) {
  TimerHandle_t xTimer;
  xTimer = xTimerCreate(timer.pcTimerName, timer.xTimerPeriod, timer.uxAutoReload, timer.pvTimerID, timer.pxCallbackFunction);
  return xTimer;
}

cfg_xTimerCreate_t __attribute__((section("CFG_TIMER_CREATE10"))) cfg_timer_create10 = {
    "Timer10", ticks[0], pdTRUE, (void *)10, vToggleCallback10,
};

cfg_xTimerCreate_t __attribute__((section("CFG_TIMER_CREATE11"))) cfg_timer_create11 = {
    "Timer11", ticks[1], pdTRUE, (void *)11, vToggleCallback11,
};

cfg_xTimerCreate_t __attribute__((section("CFG_TIMER_CREATE12"))) cfg_timer_create12 = {
    "Timer12", ticks2, pdTRUE, (void *)12, vToggleCallback12,
};

cfg_xTimerCreate_t __attribute__((section("CFG_TIMER_CREATE13"))) cfg_timer_create13 = {
    "Timer13", ticks3, pdTRUE, (void *)13, vToggleCallback13,
};

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);

  xTaskCreateCreate(cfg_task_create02);
  xTaskCreateCreate(cfg_task_create03);
  xTaskCreateCreate(cfg_task_create04);
  xTaskCreateCreate(cfg_task_create05);

  xTaskCreateCreate(cfg_task_create06);
  xTaskCreateCreate(cfg_task_create07);
  xTaskCreateCreate(cfg_task_create08);
  xTaskCreateCreate(cfg_task_create09);

  xTimerCreateCreate(cfg_timer_create10);
  xTimerCreateCreate(cfg_timer_create11);
  xTimerCreateCreate(cfg_timer_create12);
  xTimerCreateCreate(cfg_timer_create13);

  while (!Serial) {
  }
}

void loop() {}
