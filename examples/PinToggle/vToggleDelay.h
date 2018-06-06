#include <Arduino_FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <timers.h>

#include "utils.h"

#ifndef VTOGGLEDELAY_H
#define VTOGGLEDELAY_H

void vToggleDelay(void *pvParameters);

void vToggleDelay02(void *pvParameters);
void vToggleDelay03(void *pvParameters);
void vToggleDelay04(void *pvParameters);
void vToggleDelay05(void *pvParameters);

#endif // VTOGGLEDELAY_H
