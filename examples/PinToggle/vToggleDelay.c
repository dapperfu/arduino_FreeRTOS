#include "vToggleDelay.h"
#include <Arduino.h>

void vToggleDelay(void *pvParameters) // This is a task.
{
  static bool pin_state = false;
  // Task settings
  TaskCFG_t *pxParameters;
  pxParameters = (TaskCFG_t *)pvParameters;
  // Task Setup
  pinMode(pxParameters->pin, OUTPUT);
  // Task Initial Delay
  vTaskDelay(pxParameters->delay);
  for (;;) // A Task shall never return or exit.
  {
    pin_state = !pin_state;
    digitalWrite(pxParameters->pin, pin_state);
    vTaskDelay(pxParameters->ticks);
  }
}

void vToggleDelay02(void *pvParameters) // This is a task.
{
  /*
  static bool pin_state = false;
  // Task settings
  TaskCFG_t *pxParameters;
  pxParameters = (TaskCFG_t *)pvParameters;
  // Task Setup
  pinMode(pxParameters->pin, OUTPUT);
  // Task Initial Delay
  vTaskDelay(pxParameters->delay);
  for (;;) // A Task shall never return or exit.
  {
    pin_state = !pin_state;
    digitalWrite(pxParameters->pin, pin_state);
    vTaskDelay(pxParameters->ticks);
  }
  */

  for (;;) {
    /* Task code goes here. */
  }
}
