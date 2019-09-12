#include "Arduino_FreeRTOS.h"

void TaskSerial_Print1(void *pvParameters);
void TaskSerial_Print2(void *pvParameters);
void TaskBlink(void *pvParameters);

void setup()
{
  Serial.begin(9600);

  xTaskCreate(
    TaskBlink
    ,(const portCHAR*)"Blink"
    ,128
    ,NULL
    ,1
    ,NULL);

  xTaskCreate(
    TaskSerial_Print1
    ,(const portCHAR*)"TaskSerial_Print1"
    ,128
    ,NULL
    ,4
    ,NULL);
  
  xTaskCreate(
    TaskSerial_Print2
    ,(const portCHAR*)"TaskSerial_Print2"
    ,128
    ,NULL
    ,2
    ,NULL);
}

void loop()
{
  //taskENTER_CRITICAL();
  //Serial.print("This is loop! time:");
  //Serial.println(millis());
  //taskEXIT_CRITICAL();
  //delay(1000);
}

void TaskBlink(void *pvParameters)
{
  (void) pvParameters;

  pinMode(LED_BUILTIN,OUTPUT);

  while (1)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    digitalWrite(LED_BUILTIN, LOW);
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void TaskSerial_Print1(void *pvParameters)
{
  vTaskDelay(3000/portTICK_PERIOD_MS);
  while(1)
  {
    Serial.print("This is Print1! time:");
    Serial.println(millis());
    vTaskDelay(300/portTICK_PERIOD_MS);
  }
}

void TaskSerial_Print2(void *pvParameters)
{
  while(1)
  {
    taskENTER_CRITICAL();
    Serial.print("This is Print2! time:");
    Serial.println(millis());
    taskEXIT_CRITICAL();
    vTaskDelay(150/portTICK_PERIOD_MS);
  }
}