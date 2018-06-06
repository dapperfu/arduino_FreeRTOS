#include <Arduino_FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <timers.h>

#include "utils.h"

#ifndef VTOGGLECALLBACK_H
#define VTOGGLECALLBACK_H

void vToggleCallback(TimerHandle_t xTimer);

void vToggleCallback10(TimerHandle_t xTimer);
void vToggleCallback11(TimerHandle_t xTimer);
void vToggleCallback12(TimerHandle_t xTimer);
void vToggleCallback13(TimerHandle_t xTimer);

#endif // VTOGGLECALLBACK_H
