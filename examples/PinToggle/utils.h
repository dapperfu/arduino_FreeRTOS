#include <Arduino_FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <timers.h>

#ifndef UTILS_H
#define UTILS_H

// A configuration struct for each task.
typedef struct TaskCFG {
  uint8_t pin;      // Digital Pin
  TickType_t ticks; // Period
  TickType_t delay; // Phase
} TaskCFG_t;

#endif // UTILS_H
