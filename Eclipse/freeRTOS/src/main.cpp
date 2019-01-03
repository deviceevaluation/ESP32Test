/*
 * main.cpp
 *
 *  Created on: 2019/01/03
 *      Author: Shuji
 */
#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void taskFunc(void* arg);

TaskHandle_t hTask1;
TaskHandle_t hTask2;

void setup()
{
	Serial.begin(115200);
	xTaskCreatePinnedToCore(taskFunc, "Task1", 4096, NULL, 10, &hTask1, 0);
	xTaskCreatePinnedToCore(taskFunc, "Task2", 4096, NULL, 20, &hTask2, 1);

}
void loop()
{

}

void taskFunc(void* arg)
{

	while(1){

		Serial.print("task ");
		Serial.print(pcTaskGetTaskName(NULL));
		Serial.println("run.");
		delay(1000);
	}
}
