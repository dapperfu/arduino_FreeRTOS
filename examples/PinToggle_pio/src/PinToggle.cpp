#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h> // add the FreeRTOS functions for Semaphores (or Flags).

// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
// It will be used to ensure only only one Task is accessing this resource at
// any time.
SemaphoreHandle_t xSerialSemaphore;

void vToggleDelayUntil(void *pvParameters) {
  // Pin Status
  static bool pin_state = false;
  (void)pvParameters;

  // Initialise the xLastWakeTime variable with the current time.
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    // Wait for the next cycle.
    vTaskDelayUntil(&xLastWakeTime, 1000 / portTICK_PERIOD_MS);

    // Perform action here.
    pin_state = !pin_state;
    digitalWrite(13, pin_state);
  }
}

void vTaskDigitalCounter(void *pvParameters
                         __attribute__((unused))) // This is a Task.
{
  /*
    TaskDigitalCounter
    * 8 bit counter.
  */

  for (;;) // A Task shall never return or exit.
  {
    // read the input pin:
    char counter = 0x00;

    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see
    // if it becomes free.
    if (xSemaphoreTake(xSerialSemaphore, (TickType_t)0) == pdTRUE) {
      // We were able to obtain or "Take" the semaphore and can now access the
      // shared resource. We want to have the Serial Port for us alone, as it
      // takes some time to print, so we don't want it getting stolen during the
      // middle of a conversion. print out the state of the button:
      Serial.println(counter++);
      xSemaphoreGive(
          xSerialSemaphore); // Now free or "Give" the Serial Port for others.
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS); // one tick delay (15ms) in between
                                           // reads for stability
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  while (!Serial) {
  }
  Serial.println("Hello World");

  // Semaphores are useful to stop a Task proceeding, where it should be paused
  // to wait,
  // because it is sharing a resource, such as the Serial port.
  // Semaphores should only be used whilst the scheduler is running, but we can
  // set it up here.
  if (xSerialSemaphore == NULL) // Check to confirm that the Serial Semaphore
                                // has not already been created.
  {
    xSerialSemaphore =
        xSemaphoreCreateMutex(); // Create a mutex semaphore we will use to
                                 // manage the Serial Port
    if ((xSerialSemaphore) != NULL)
      xSemaphoreGive((xSerialSemaphore)); // Make the Serial Port available for
                                          // use, by "Giving" the Semaphore.
  }

  // Now set up two tasks to run independently.
  xTaskCreate(vToggleDelayUntil,
              (const portCHAR *)"Blink" // A name just for humans
              ,
              128 // This stack size can be checked & adjusted by reading the
                  // Stack Highwater
              ,
              NULL, 2 // Priority, with 3 (configMAX_PRIORITIES - 1) being the
                      // highest, and 0 being the lowest.
              ,
              NULL);

  // Now set up two tasks to run independently.
  xTaskCreate(vTaskDigitalCounter,
              (const portCHAR *)"Counter" // A name just for humans
              ,
              128 // This stack size can be checked & adjusted by reading the
                  // Stack Highwater
              ,
              NULL, 2 // Priority, with 3 (configMAX_PRIORITIES - 1) being the
                      // highest, and 0 being the lowest.
              ,
              NULL);
}

void loop() {}
