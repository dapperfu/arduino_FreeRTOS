#include <Arduino_FreeRTOS.h>
#include <timers.h>

#include <semphr.h> // add the FreeRTOS functions for Semaphores (or Flags).

// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
// It will be used to ensure only only one Task is accessing this resource at
// any time.
SemaphoreHandle_t xSerialSemaphore;

void TaskToggle6(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  pinMode(6, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(6, HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay(1);         // wait for one second
    digitalWrite(6, LOW);  // turn the LED off by making the voltage LOW
    vTaskDelay(1);         // wait for one second
  }
}

void TaskToggle7(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  pinMode(7, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(7, HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay(2);         // wait for one second
    digitalWrite(7, LOW);  // turn the LED off by making the voltage LOW
    vTaskDelay(2);         // wait for one second
  }
}

void TaskToggle8(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  pinMode(8, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(8, HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay(5);         // wait for one second
    digitalWrite(8, LOW);  // turn the LED off by making the voltage LOW
    vTaskDelay(5);         // wait for one second
  }
}

void TaskToggle9(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  pinMode(9, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(9, HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay(10);        // wait for one second
    digitalWrite(9, LOW);  // turn the LED off by making the voltage LOW
    vTaskDelay(10);        // wait for one second
  }
}

void vTimerCallback(TimerHandle_t xTimer) {

  uint32_t ulCount;
  /* The number of times this timer has expired is saved as the
  timer's ID.  Obtain the count. */
  ulCount = (uint32_t)pvTimerGetTimerID(xTimer);

  /* Increment the count. */
  ulCount++;

  Serial.print(pcTimerGetName(xTimer));
  Serial.print(": ");
  Serial.println(ulCount);
  /* Store the incremented count back into the timer's ID field
  so it can be read back again the next time this software timer
  expires. */
  vTimerSetTimerID(xTimer, (void *)ulCount);
}

void vTimerCallback10(TimerHandle_t xTimer) {
  static bool pin_state = false;
  pin_state = !pin_state;
  digitalWrite(10, pin_state);
}

void vTimerCallback11(TimerHandle_t xTimer) {
  static bool pin_state = false;
  pin_state = !pin_state;
  digitalWrite(11, pin_state);
}

void vTimerCallback12(TimerHandle_t xTimer) {
  static bool pin_state = false;
  pin_state = !pin_state;
  digitalWrite(12, pin_state);
}

void vTimerCallback13(TimerHandle_t xTimer) {
  static bool pin_state = false;
  pin_state = !pin_state;
  digitalWrite(13, pin_state);
}

TimerHandle_t xTimer;
TimerHandle_t xTimer13;
TimerHandle_t xTimer12;
TimerHandle_t xTimer11;
TimerHandle_t xTimer10;

// the setup function runs once when you press reset or power the board
void setup() {

  Serial.begin(115200);

  if (xSerialSemaphore == NULL) // Check to confirm that the Serial Semaphore
                                // has not already been created.
  {
    xSerialSemaphore = xSemaphoreCreateMutex(); // Create a mutex semaphore we will use to
                                                // manage the Serial Port
    if ((xSerialSemaphore) != NULL)
      xSemaphoreGive((xSerialSemaphore)); // Make the Serial Port available for
                                          // use, by "Giving" the Semaphore.
  }

  xTimer10 = xTimerCreate("Timer10", 1, pdTRUE, (void *)0, vTimerCallback10);
  xTimerStart(xTimer10, 0);

  xTimer11 = xTimerCreate("Timer11", 2, pdTRUE, (void *)0, vTimerCallback11);
  xTimerStart(xTimer11, 0);

  xTimer12 = xTimerCreate("Timer12", 5, pdTRUE, (void *)0, vTimerCallback12);
  xTimerStart(xTimer12, 0);

  xTimer13 = xTimerCreate("Timer13", 5, pdTRUE, (void *)0, vTimerCallback13);
  xTimerStart(xTimer13, 0);

  // Now set up two tasks to run independently.
  xTaskCreate(TaskToggle6,
              (const portCHAR *)"TaskToggle4" // A name just for humans
              ,
              128, NULL, 2, NULL);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO,
      // MICRO, YUN, and other 32u4 based boards.
  }

  xTimer = xTimerCreate("Timer", 100, pdTRUE, (void *)0, vTimerCallback);
  xTimerStart(xTimer, 0);
}

void loop() {
  // Empty. Things are done in Tasks.
}
