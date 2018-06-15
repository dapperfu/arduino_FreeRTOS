#include <Arduino_FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <timers.h>

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

// Duration, in Ticks, for to wait for.
TickType_t __attribute__((section("CFG_TICKS0"))) ticks0 = 1;
TickType_t __attribute__((section("CFG_TICKS1"))) ticks1 = 2;
TickType_t __attribute__((section("CFG_TICKS2"))) ticks2 = 10;
TickType_t __attribute__((section("CFG_TICKS3"))) ticks3 = 100;

void vToggleDelayPin02(void *pvParameters) {
  /* Static variable to store the pin state.
   *
   * Static local variables
   *	Variables declared as static inside a function are
   * 	statically allocated, thus keep their memory cell
   * 	throughout all program execution, while having the
   * 	same scope of visibility as automatic local variables
   * 	(auto and register), meaning remain local to the function.
   * 	Hence whatever values the function puts into its static local
   * 	variables during one call will still be present when the
   * 	function is called again.
   *
   * - https://en.wikipedia.org/wiki/Static_(keyword)
   */
  static bool pin_state = false;

  // Run forever.
  for (;;) {
    // Toggle the pin state.
    pin_state = !pin_state;
    // Write the pin state to the digital pin.
    digitalWrite(2, pin_state);
    // Delay the task by configured number of ticks.
    vTaskDelay(ticks0);
  }
  /* Tasks must not attempt to return from their implementing
  function or otherwise exit.  In newer FreeRTOS port
  attempting to do so will result in an configASSERT() being
  called if it is defined.  If it is necessary for a task to
  exit then have the task call vTaskDelete( NULL ) to ensure
  its exit is clean. */
  vTaskDelete(NULL);
}
// Rinse, repeat.
void vToggleDelayPin03(void *pvParameters) {
  static bool pin_state = false;
  for (;;) {
    pin_state = !pin_state;
    digitalWrite(3, pin_state);
    vTaskDelay(ticks1);
  }
  vTaskDelete(NULL);
}
void vToggleDelayPin04(void *pvParameters) {
  static bool pin_state = false;
  for (;;) {
    pin_state = !pin_state;
    digitalWrite(3, pin_state);
    vTaskDelay(ticks2);
  }
  vTaskDelete(NULL);
}
void vToggleDelayPin05(void *pvParameters) {
  static bool pin_state = false;
  for (;;) {
    pin_state = !pin_state;
    digitalWrite(5, pin_state);
    vTaskDelay(ticks3);
  }
  vTaskDelete(NULL);
}

/* # vTaskDelayUntil

https://www.freertos.org/vtaskdelayuntil.html

void vTaskDelayUntil( TickType_t *pxPreviousWakeTime,
                      const TickType_t xTimeIncrement );


Delay a task until a specified time. This function can be used by periodic tasks to ensure a constant execution frequency.

This function differs from vTaskDelay() in one important aspect: vTaskDelay() specifies a time at which the task wishes to unblock relative to the time at which
vTaskDelay() is called, whereas vTaskDelayUntil() specifies an absolute time at which the task wishes to unblock.

vTaskDelay() will cause a task to block for the specified number of ticks from the time vTaskDelay() is called. It is therefore difficult to use vTaskDelay() by
itself to generate a fixed execution frequency as the time between a task unblocking following a call to vTaskDelay() and that task next calling vTaskDelay()
may not be fixed [the task may take a different path though the code between calls, or may get interrupted or preempted a different number of times each time it
executes].

Whereas vTaskDelay() specifies a wake time relative to the time at which the function is called, vTaskDelayUntil() specifies the absolute (exact) time at which
it wishes to unblock.

*/

void vToggleDelayUntilPin06(void *pvParameters) {
  // Pin Status
  static bool pin_state = false;
  // Initialise the xLastWakeTime variable with the current time.
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  for (;;) {
    // Wait for the next cycle.
    vTaskDelayUntil(&xLastWakeTime, ticks0);
    // Perform action here.
    pin_state = !pin_state;
    digitalWrite(6, pin_state);
  }
}

void vToggleDelayUntilPin07(void *pvParameters) {
  static bool pin_state = false;
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  for (;;) {
    vTaskDelayUntil(&xLastWakeTime, ticks1);
    pin_state = !pin_state;
    digitalWrite(7, pin_state);
  }
}

void vToggleDelayUntilPin08(void *pvParameters) {
  static bool pin_state = false;
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  for (;;) {
    vTaskDelayUntil(&xLastWakeTime, ticks2);
    pin_state = !pin_state;
    digitalWrite(8, pin_state);
  }
}

void vToggleDelayUntilPin09(void *pvParameters) {
  static bool pin_state = false;
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  for (;;) {
    vTaskDelayUntil(&xLastWakeTime, ticks3);
    pin_state = !pin_state;
    digitalWrite(9, pin_state);
  }
}

/*
 * Timer/Callback Method
 */

void vToggleCallback10(TimerHandle_t xTimer) {
  static bool pin_state = false;
  pin_state = !pin_state;
  digitalWrite(10, pin_state);
}

void vToggleCallback11(TimerHandle_t xTimer) {
  static bool pin_state = false;
  pin_state = !pin_state;
  digitalWrite(11, pin_state);
}

void vToggleCallback12(TimerHandle_t xTimer) {
  static bool pin_state = false;
  pin_state = !pin_state;
  digitalWrite(12, pin_state);
}

void vToggleCallback13(TimerHandle_t xTimer) {
  static bool pin_state = false;
  pin_state = !pin_state;
  digitalWrite(13, pin_state);
}
// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);

  TaskHandle_t xHandle2 = NULL;
  TaskHandle_t xHandle3 = NULL;
  TaskHandle_t xHandle4 = NULL;
  TaskHandle_t xHandle5 = NULL;
  TaskHandle_t xHandle6 = NULL;
  TaskHandle_t xHandle7 = NULL;
  TaskHandle_t xHandle8 = NULL;
  TaskHandle_t xHandle9 = NULL;

  xTaskCreate(vToggleDelayPin02,    /* Function that implements the task. */
              "vToggleDelayTask02", /* Text name for the task. */
              128,                  /* Stack size in words, not bytes. */
              (void *)0,             /* Parameter passed into the task. */
              tskIDLE_PRIORITY,     /* Priority at which the task is created. */
              &xHandle2);           /* Used to pass out the created task's handle. */
  xTaskCreate(vToggleDelayPin03,    /* Function that implements the task. */
              "vToggleDelayTask03", /* Text name for the task. */
              128,                  /* Stack size in words, not bytes. */
              (void *)0,             /* Parameter passed into the task. */
              tskIDLE_PRIORITY,     /* Priority at which the task is created. */
              &xHandle3);           /* Used to pass out the created task's handle. */
  xTaskCreate(vToggleDelayPin04,    /* Function that implements the task. */
              "vToggleDelayTask04", /* Text name for the task. */
              128,                  /* Stack size in words, not bytes. */
              (void *)0,             /* Parameter passed into the task. */
              tskIDLE_PRIORITY,     /* Priority at which the task is created. */
              &xHandle4);           /* Used to pass out the created task's handle. */
  xTaskCreate(vToggleDelayPin05,    /* Function that implements the task. */
              "vToggleDelayTask05", /* Text name for the task. */
              128,                  /* Stack size in words, not bytes. */
              (void *)0,             /* Parameter passed into the task. */
              tskIDLE_PRIORITY,     /* Priority at which the task is created. */
              &xHandle5);           /* Used to pass out the created task's handle. */
              
              
  xTaskCreate(vToggleDelayUntilPin06, /* Function that implements the task. */
              "vToggleDelayTask06",   /* Text name for the task. */
              128,                    /* Stack size in words, not bytes. */
              (void *)0,               /* Parameter passed into the task. */
              tskIDLE_PRIORITY,       /* Priority at which the task is created. */
              &xHandle6);             /* Used to pass out the created task's handle. */              
              
  xTaskCreate(vToggleDelayUntilPin07, /* Function that implements the task. */
              "vToggleDelayTask07",   /* Text name for the task. */
              128,                    /* Stack size in words, not bytes. */
              (void *)0,               /* Parameter passed into the task. */
              tskIDLE_PRIORITY,       /* Priority at which the task is created. */
              &xHandle7);             /* Used to pass out the created task's handle. */
              
                        
              
  xTaskCreate(vToggleDelayUntilPin08, /* Function that implements the task. */
              "vToggleDelayTask08",   /* Text name for the task. */
              128,                    /* Stack size in words, not bytes. */
              (void *)0,               /* Parameter passed into the task. */
              tskIDLE_PRIORITY,       /* Priority at which the task is created. */
              &xHandle8);             /* Used to pass out the created task's handle. */
              
              
  xTaskCreate(vToggleDelayUntilPin09, /* Function that implements the task. */
              "vToggleDelayTask06",   /* Text name for the task. */
              128,                    /* Stack size in words, not bytes. */
              (void *)0,               /* Parameter passed into the task. */
              tskIDLE_PRIORITY,       /* Priority at which the task is created. */
              &xHandle9);             /* Used to pass out the created task's handle. */
  // Timers
  TimerHandle_t xTimer10;
  xTimer10 = xTimerCreate(/* Just a text name, not used by the RTOS
                   kernel. */
                          "vToggleTimer10",
                          /* The timer period in ticks, must be
                          greater than 0. */
                          ticks0,
                          /* The timers will auto-reload themselves
                          when they expire. */
                          pdTRUE,
                          /* The ID */
                          (void *)0,
                          /* Each timer calls the same callback when
                          it expires. */
                          vToggleCallback10);

  TimerHandle_t xTimer11;
  xTimer11 = xTimerCreate(/* Just a text name, not used by the RTOS
                   kernel. */
                          "vToggleTimer11",
                          /* The timer period in ticks, must be
                          greater than 0. */
                          ticks1,
                          /* The timers will auto-reload themselves
                          when they expire. */
                          pdTRUE,
                          /* The ID */
                          (void *)0,
                          /* Each timer calls the same callback when
                          it expires. */
                          vToggleCallback11);

  TimerHandle_t xTimer12;
  xTimer12 = xTimerCreate("vToggleTimer12",  // Just a text name, not used by the RTOS kernel
                          ticks2,            // The timer period in ticks, must be greater than 0.
                          pdTRUE,            // The timers will auto-reload themselveswhen they expire.
                          (void *)12,        // The ID
                          vToggleCallback12  // Each timer calls the same callback when it expires.
  );

  TimerHandle_t xTimer13;
  xTimer13 = xTimerCreate(/* Just a text name, not used by the RTOS
                  kernel. */
                          "vToggleTimer13",
                          /* The timer period in ticks, must be
                          greater than 0. */
                          ticks3,
                          /* The timers will auto-reload themselves
                          when they expire. */
                          pdTRUE,
                          /* The ID */
                          (void *)0,
                          /* Each timer calls the same callback when
                          it expires. */
                          vToggleCallback13);

  xTimerStart(xTimer10, 0);
  xTimerStart(xTimer11, 0);
  xTimerStart(xTimer12, 0);
  xTimerStart(xTimer13, 0);

vTaskStartScheduler();

  while (!Serial) {
  }
}

void loop() {}
