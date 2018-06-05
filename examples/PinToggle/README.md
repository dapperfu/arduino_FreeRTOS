# Pin Toggle.

Toggle digital pins on the Arduino using FreeRTOS various tasks and timers:

- [vTaskDelay](https://www.freertos.org/a00127.html)
- [vTaskDelayUntil](https://www.freertos.org/vtaskdelayuntil.html)
- [xTimerCreate](https://www.freertos.org/FreeRTOS-timers-xTimerCreate.html)

Each task simply toggles a pin on the Arduino board. You can view the timing output on a logic analyzer or oscilloscope.


> FreeRTOS has a multitude of configuration options, which can be specified from within the FreeRTOSConfig.h file. To keep commonality with all of the Arduino hardware options, some sensible defaults have been selected.

> The AVR Watchdog Timer is used to generate 15ms time slices, but Tasks that finish before their allocated time will hand execution back to the Scheduler. This does not affect the use of any of the normal Timer functions in Arduino.

> Time slices can be selected from 15ms up to 500ms. Slower time slicing can allow the Arduino MCU to sleep for longer, without the complexity of a Tickless idle.

This example project is configured to use: ```WDTO_15MS``` or 1 tick = 15 ms = 0.015 s.

Digital pins 6-9 are toggled in a FreeRTOS task with vTaskDelay.

Example:

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

| Pin | vTaskDelay ticks | ```WDTO_15MS``` Duration (ms) |
|-----|------------------|-------------------------------|
| 6   | 1                | 15                            |
| 7   | 2                | 30                            |
| 8   | 5                | 75                            |
| 9   | 10               | 150                           |





## Reference:


> **void vTaskDelay( const TickType_t xTicksToDelay );**

> Delay a task for a given number of ticks. The actual time that the task remains blocked depends on the tick rate. The constant portTICK_PERIOD_MS can be used to calculate real time from the tick rate - with the resolution of one tick period.

> vTaskDelay() specifies a time at which the task wishes to unblock relative to the time at which vTaskDelay() is called. For example, specifying a block period of 100 ticks will cause the task to unblock 100 ticks after vTaskDelay() is called. vTaskDelay() does not therefore provide a good method of controlling the frequency of a periodic task as the path taken through the code, as well as other task and interrupt activity, will effect the frequency at which vTaskDelay() gets called and therefore the time at which the task next executes. See vTaskDelayUntil() for an alternative API function designed to facilitate fixed frequency execution. It does this by specifying an absolute time (rather than a relative time) at which the calling task should unblock. 
