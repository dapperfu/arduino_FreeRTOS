/*
  DHCP-based IP printer

  This sketch uses the DHCP extensions to the Ethernet library
  to get an IP address via DHCP and print the address obtained.
  using an Arduino Wiznet Ethernet shield.

  Circuit:
   Ethernet shield attached to pins 10, 11, 12, 13

  created 12 April 2011
  modified 9 Apr 2012
  by Tom Igoe
  modified 02 Sept 2015
  by Arturo Guadalupi

 */
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h> // add the FreeRTOS functions for Semaphores (or Flags).

SemaphoreHandle_t xSerialSemaphore;

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02
};


void vEthernetMaintenanceTask(void *pvParameters);

void setup() {
  Ethernet.init(10);  // Most Arduino shields

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  // start the Ethernet connection:
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    } else if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // no point in carrying on, so do nothing forevermore:
    while (true) {
      delay(1);
    }
  }
  // print your local IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
  
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
  
  
  
  
  xTaskCreate(vEthernetMaintenanceTask, (const portCHAR *)"EthernetMaintenanceTask", 128 // Stack size
              ,
              NULL, 1 // Priority
              ,
              NULL);
}



void loop() {}




void EthernetMaintain() {
	  switch (Ethernet.maintain()) {
    case 1:
    
      Serial.println("");
      //renewed fail
      Serial.println("Error: renewed fail");
      break;

    case 2:
      Serial.println("");
      //renewed success
      Serial.println("Renewed success");
      //print your local IP address:
      Serial.print("My IP address: ");
      Serial.println(Ethernet.localIP());
      break;

    case 3:
      Serial.println("");
      //rebind fail
      Serial.println("Error: rebind fail");
      break;

    case 4:
      Serial.println("");
      //rebind success
      Serial.println("Rebind success");
      //print your local IP address:
      Serial.print("My IP address: ");
      Serial.println(Ethernet.localIP());
      break;

    default:
      //nothing happened
      Serial.print(".");
  }
	
}

void vEthernetMaintenanceTask(void *pvParameters
                     __attribute__((unused))) // This is a Task.
{
	const TickType_t xDelay = 500 / portTICK_PERIOD_MS;
  for (;;) // A Task shall never return or exit.
  {

    // See if we can obtain or "Take" the Serial Semaphore.
    // If the semaphore is not available, wait 5 ticks of the Scheduler to see
    // if it becomes free.
    if (xSemaphoreTake(xSerialSemaphore, (TickType_t)5) == pdTRUE) {
      // We were able to obtain or "Take" the semaphore and can now access the
      // shared resource. We want to have the Serial Port for us alone, as it
      // takes some time to print, so we don't want it getting stolen during the
      // middle of a conversion. print out the state of the button:
      EthernetMaintain();
      xSemaphoreGive(
          xSerialSemaphore); // Now free or "Give" the Serial Port for others.
    }

    vTaskDelay(xDelay); // one tick delay (15ms) in between reads for stability
  }
  
  delay(500);
}
