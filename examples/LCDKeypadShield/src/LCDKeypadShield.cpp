#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
enum ePins {
  LCD_RS = 8,
  LCD_EN = 9,
  LCD_D4 = 4,
  LCD_D5 = 5,
  LCD_D6 = 6,
  LCD_D7 = 7,
  LCD_BL = 10
}; // define LCD pins
LiquidCrystal lcd(
    LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6,
    LCD_D7); // initialize the library with the numbers of the interface pins

// define two tasks for Blink & AnalogRead
void TaskBlink(void *pvParameters);
void TaskAnalogRead(void *pvParameters);

// the setup function runs once when you press reset or power the board
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  while (!Serial) {
  }
  // Now set up two tasks to run independently.
  xTaskCreate(TaskBlink, (const portCHAR *)"Blink" // A name just for humans
              ,
              128 // This stack size can be checked & adjusted by reading the
                  // Stack Highwater
              ,
              NULL, 2 // Priority, with 3 (configMAX_PRIORITIES - 1) being the
                      // highest, and 0 being the lowest.
              ,
              NULL);

  xTaskCreate(TaskAnalogRead, (const portCHAR *)"AnalogRead", 128 // Stack size
              ,
              NULL, 1 // Priority
              ,
              NULL);

  // Now the task scheduler, which takes over control of scheduling individual
  // tasks, is automatically started.
}

void loop() {
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/



void TaskBlink(void *pvParameters) // This is a task.
{
  (void)pvParameters;
  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(LED_BUILTIN,
                 HIGH); // turn the LED on (HIGH is the voltage level)
    vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
    digitalWrite(LED_BUILTIN,
                 LOW); // turn the LED off by making the voltage LOW
    vTaskDelay(1000 / portTICK_PERIOD_MS); // wait for one second
  }
}

volatile uint8_t sensorValue;
volatile int8_t window = 5;

volatile uint8_t selectValue = 229;
volatile uint8_t leftValue = 248;
volatile uint8_t rightValue = 0;
volatile uint8_t upValue = 144;

volatile uint8_t counter = 250;

void TaskAnalogRead(void *pvParameters) // This is a task.
{
  (void)pvParameters;

  for (;;) {
    sensorValue = analogRead(A0);

    // print out the value you read:
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print(sensorValue);
    
    lcd.setCursor(0, 1);
    
    if (sensorValue == 255) {
      lcd.print("Nothing:");
      Serial.print("Nothing: ");
    } else if ((uint8_t)sensorValue < (uint8_t)(rightValue + (uint8_t)window)) {
      lcd.print("Right:");
      lcd.print((uint8_t)(rightValue + window));
      Serial.print("Right: ");
    } else if ((sensorValue > selectValue-window) & (sensorValue < selectValue+window)) {
      lcd.print("Select:");
      Serial.print("Select: ");
    } else if ((sensorValue > leftValue-window) & (sensorValue < leftValue+window)) {
      lcd.print("Left:");
      Serial.print("Left: ");
    } else if ((sensorValue > (uint8_t)(upValue-window)) & (sensorValue < (uint8_t)(upValue+window))) {
      lcd.print("Up:");
      Serial.print("Up: ");
    } else if ((sensorValue > 63) & (sensorValue < 83)) {
      lcd.print("Down:");
      Serial.print("Down: ");
    } else {
      lcd.print("Unknown:");
      Serial.print("Unknown: ");
    }
    lcd.print(counter++);
    vTaskDelay(500/portTICK_PERIOD_MS); // one tick delay (15ms) in between reads for stability
  }
}
