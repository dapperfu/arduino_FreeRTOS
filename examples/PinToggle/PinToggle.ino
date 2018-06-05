#include <Arduino_FreeRTOS.h>
#include <timers.h>

// Define tasks for toggling pins.
void TaskToggle(void *pvParameters);
void vCallbackFunction(TimerHandle_t xTimer);

TimerHandle_t xTimer;
TimerHandle_t xTimer2;

void vTimerCallback(TimerHandle_t xTimer) {

  uint32_t ulCount;
  /* The number of times this timer has expired is saved as the
  timer's ID.  Obtain the count. */
  ulCount = (uint32_t)pvTimerGetTimerID(xTimer);

  /* Increment the count. */
  ulCount++;

  Serial.print(pcTimerGetName( xTimer ));
  Serial.print(": ");
  Serial.println(ulCount);
  /* Store the incremented count back into the timer's ID field
  so it can be read back again the next time this software timer
  expires. */
  vTimerSetTimerID(xTimer, (void *)ulCount);
}

void vTimerCallback2(TimerHandle_t xTimer) {
	static bool pin_state = false;
	pin_state=!pin_state;
	digitalWrite(13, pin_state);
}

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(13, OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO,
      // MICRO, YUN, and other 32u4 based boards.
  }

  xTimer = xTimerCreate("Timer", 100, pdTRUE, (void *)0, vTimerCallback);
  xTimerStart(xTimer, 0);
  
  xTimer2 = xTimerCreate("Timer2", 60, pdTRUE, (void *)0, vTimerCallback2);
  xTimerStart(xTimer2, 0);

  // Now set up two tasks to run independently.
  /*
  xTaskCreate(TaskToggle,
              (const portCHAR *)"TaskToggle" // A name just for humans
              ,
              128 // This stack size can be checked & adjusted by reading the
                  // Stack Highwater
              ,
              (void *)9, 3 // Priority, with 3 (configMAX_PRIORITIES - 1) being the
                           // highest, and 0 being the lowest.
              ,
              NULL);*/
}

void loop() {
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/
/*
void TaskToggle(void *pvParameters) // This is a task.
{
(void) pvParameters;
  pinMode(13, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(13,
                 HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay(60);      // wait for one second
    digitalWrite(13,
                 LOW); // turn the LED off by making the voltage LOW
    vTaskDelay(30);     // wait for one second
  }
}
*/
