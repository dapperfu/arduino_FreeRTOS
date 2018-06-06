#include <Arduino.h>

#include "vToggleDelayUntil.h"

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

void vToggleDelayUntil(void *pvParameters) {
  // Pin Status
  static bool pin_state = false;

  // Task Parameters
  TaskCFG_t *pxParameters;
  pxParameters = (TaskCFG_t *)pvParameters;

  // Initialise the xLastWakeTime variable with the current time.
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    // Wait for the next cycle.
    vTaskDelayUntil(&xLastWakeTime, pxParameters->ticks);

    // Perform action here.
    pin_state = !pin_state;
    digitalWrite(pxParameters->pin, pin_state);
  }
}
