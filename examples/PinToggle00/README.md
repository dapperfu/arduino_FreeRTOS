# Pin Toggle.

Toggle digital pins on the Arduino using FreeRTOS various tasks and timers:

- [vTaskDelay](https://www.freertos.org/a00127.html)
- [vTaskDelayUntil](https://www.freertos.org/vtaskdelayuntil.html)
- [xTimerCreate](https://www.freertos.org/FreeRTOS-timers-xTimerCreate.html)

Each task simply toggles a pin on the Arduino board. You can view the timing output on a logic analyzer or oscilloscope. It will also let you check timings.

**This example project is configured to use: ```WDTO_15MS``` or 1 tick = 15 ms = 0.015 s.**


> FreeRTOS has a multitude of configuration options, which can be specified from within the FreeRTOSConfig.h file. To keep commonality with all of the Arduino hardware options, some sensible defaults have been selected.

> The AVR Watchdog Timer is used to generate 15ms time slices, but Tasks that finish before their allocated time will hand execution back to the Scheduler. This does not affect the use of any of the normal Timer functions in Arduino.

> Time slices can be selected from 15ms up to 500ms. Slower time slicing can allow the Arduino MCU to sleep for longer, without the complexity of a Tickless idle.


By default the project is configured as such:

| Arduino Digital Pin | Method          | Period Ticks | Delay (Ticks) | Duration (ms) | Duration (s) |
|---------------------|-----------------|--------------|---------------|---------------|--------------|
| 2                   | vTaskDelay      | 1            | 0             | 15            | 0.015        |
| 3                   | vTaskDelay      | 2            | 1             | 30            | 0.03         |
| 4                   | vTaskDelay      | 10           | 2             | 150           | 0.15         |
| 5                   | vTaskDelay      | 100          | 3             | 1500          | 1.5          |
| 6                   | vTaskDelayUntil | 1            | 0             | 15            | 0.015        |
| 7                   | vTaskDelayUntil | 2            | 1             | 30            | 0.03         |
| 8                   | vTaskDelayUntil | 10           | 2             | 150           | 0.15         |
| 9                   | vTaskDelayUntil | 100          | 3             | 1500          | 1.5          |
| 10                  | xTimerCreate    | 1            | 0             | 15            | 0.015        |
| 11                  | xTimerCreate    | 2            | 1             | 30            | 0.03         |
| 12                  | xTimerCreate    | 10           | 2             | 150           | 0.15         |
| 13                  | xTimerCreate    | 100          | 3             | 1500          | 1.5          |


## Reference:

**vTaskDelay**:

>     void vTaskDelay( const TickType_t xTicksToDelay );

> Delay a task for a given number of ticks. The actual time that the task remains blocked depends on the tick rate. The constant portTICK_PERIOD_MS can be used to calculate real time from the tick rate - with the resolution of one tick period.

> vTaskDelay() specifies a time at which the task wishes to unblock relative to the time at which vTaskDelay() is called. For example, specifying a block period of 100 ticks will cause the task to unblock 100 ticks after vTaskDelay() is called. vTaskDelay() does not therefore provide a good method of controlling the frequency of a periodic task as the path taken through the code, as well as other task and interrupt activity, will effect the frequency at which vTaskDelay() gets called and therefore the time at which the task next executes. See vTaskDelayUntil() for an alternative API function designed to facilitate fixed frequency execution. It does this by specifying an absolute time (rather than a relative time) at which the calling task should unblock. 

**vTaskDelayUntil**:

>     void vTaskDelayUntil( TickType_t *pxPreviousWakeTime,
>                           const TickType_t xTimeIncrement );

> INCLUDE_vTaskDelayUntil must be defined as 1 for this function to be available. See the RTOS Configuration documentation forr more information.

> Delay a task until a specified time. This function can be used by periodic tasks to ensure a constant execution frequency. 

**xTimerCreate**:

>     TimerHandle_t xTimerCreate
>                     ( const char * const pcTimerName,
>                       const TickType_t xTimerPeriod,
>                       const UBaseType_t uxAutoReload,
>                       void * const pvTimerID,
>                       TimerCallbackFunction_t pxCallbackFunction );