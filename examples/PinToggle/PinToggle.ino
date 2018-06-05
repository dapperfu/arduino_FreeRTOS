#include <Arduino_FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <mpu_wrappers.h>
#include <semphr.h>
#include <task.h>
#include <timers.h>

// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
// It will be used to ensure only only one Task is accessing this resource at
// any time.
SemaphoreHandle_t xSerialSemaphore;
StaticTimer_t xTimerBuffer13;

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
    vTaskDelay(25);        // wait for one second
    digitalWrite(9, LOW);  // turn the LED off by making the voltage LOW
    vTaskDelay(25);        // wait for one second
  }
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

  xTimer13 = xTimerCreate("Timer13", 25, pdTRUE, (void *)0, vTimerCallback13);
  xTimerStart(xTimer13, 0);

  // Now set up two tasks to run independently.
  xTaskCreate(TaskToggle6, (const portCHAR *)"TaskToggle6", 128, NULL, 2, NULL);
  // Now set up two tasks to run independently.
  xTaskCreate(TaskToggle7, (const portCHAR *)"TaskToggle7", 128, NULL, 2, NULL);
  // Now set up two tasks to run independently.
  xTaskCreate(TaskToggle8, (const portCHAR *)"TaskToggle8", 128, NULL, 2, NULL);
  // Now set up two tasks to run independently.
  xTaskCreate(TaskToggle9, (const portCHAR *)"TaskToggle9", 128, NULL, 2, NULL);

  while (!Serial) {
  }
}

void loop() {
  // Empty. Things are done in Tasks.
}
