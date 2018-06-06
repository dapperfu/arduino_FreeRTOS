#include "vToggleCallback.h"
#include <Arduino.h>

// Minimal toggle callback.
void vToggleCallback(TimerHandle_t xTimer) {
  static bool pin_state = false;
  uint32_t timer_id;

  // Get the timer ID.
  timer_id = (uint32_t)pvTimerGetTimerID(xTimer);

  pin_state = !pin_state;
  digitalWrite(10, pin_state);
}
