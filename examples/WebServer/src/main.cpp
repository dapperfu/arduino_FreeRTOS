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
#include <Arduino_FreeRTOS.h>
#include <Ethernet.h>
#include <SPI.h>
#include <semphr.h> // add the FreeRTOS functions for Semaphores (or Flags).

SemaphoreHandle_t xSerialSemaphore;

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};

EthernetServer server(80);
void vRunWebserver(void *pvParameters);

void setup() {
  Ethernet.init(10); // Most Arduino shields

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
      Serial.println("Ethernet shield was not found.  Sorry, can't run without "
                     "hardware. :(");
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
/*
  xTaskCreate(
	vRunWebserver,
	(const portCHAR *)"vRunWebserver",
    1024, // Stack size
	NULL,
	1, // Priority
	,NULL);
	*/
}

void WebServer();
void loop() {
	WebServer();
	}

void WebServer() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println(
              "Connection: close"); // the connection will be closed after
                                    // completion of the response
          client.println(
              "Refresh: 5"); // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

void vRunWebserver(void *pvParameters
                   __attribute__((unused))) // This is a Task.
{
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
      WebServer();
      xSemaphoreGive(xSerialSemaphore);
    }
    vTaskDelay(1); // one tick delay (15ms) in between reads for stability
  }
}
