#include<stdio.h>
#include <stdarg.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "semphr.h"
#include "main.h"
#include "cmsis_os.h"
#define TRUE  1
#define FALSE 0

TaskHandle_t task1handle;
TaskHandle_t task2handle;
TaskHandle_t task3handle;
TaskHandle_t task4handle;
TaskHandle_t task5handle;
TaskHandle_t task6handle;
TaskHandle_t task7handle;
TaskHandle_t task8handle;
TaskHandle_t task9handle;
TaskHandle_t task10handle;
TaskHandle_t task11handle;
TaskHandle_t task12handle;
TaskHandle_t task13handle;

UART_HandleTypeDef huart2;


struct Command_Info info;


char msg[64];
uint8_t bit;
uint8_t Received = FALSE;
uint32_t count = 0;

void Error_Handler(void);
static void MX_USART2_UART_Init(void);
void GPIO_INIT(void);
void printc(char *format, ...);
void Decode_CMD(char *msg);


void task1(void *p)
 {
	TickType_t tick;
	while (1) {
		vTaskSuspend(NULL);

		if (info.relay_no == 1 && strcmp(info.status, "ON") == 0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			tick = xTaskGetTickCount();
			long time = info.tim;
			while (xTaskGetTickCount() - tick < time * configTICK_RATE_HZ / 1000)
			{
				if (info.relay_no == 1 && strcmp(info.status, "OFF") == 0)
				{
					goto off;
				}
			}

			off: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			if(info.tim > 0 && strcmp(info.status, "OFF") == 0 ){
				tick = xTaskGetTickCount();
				vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ / 1000);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
				info.relay_no =0;
			}
			info.relay_no =0;

		}
		if(info.relay_no == 1 && strcmp(info.status, "OFF") == 0 && info.tim == 0)
		{
			 HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
		}
		if(info.relay_no == 1 && strcmp(info.status, "OFF") == 0 && info.tim > 0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			tick = xTaskGetTickCount();
			vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ / 1000);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
		}

		vTaskDelayUntil(&tick, 1900 * configTICK_RATE_HZ / 1000);
	}
}

void task2(void *p)
{
	TickType_t tick;
		while (1) {
			vTaskSuspend(NULL);

			if (info.relay_no == 2 && strcmp(info.status, "ON") == 0)
			{
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, SET);
				tick = xTaskGetTickCount();
				uint32_t time = info.tim;
				while (xTaskGetTickCount() - tick < time * configTICK_RATE_HZ / 1000)
				{
					if (info.relay_no == 2 && strcmp(info.status, "OFF") == 0)
					{
						goto off;
					}
				}

				off: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, RESET);
				if(info.tim > 0 && strcmp(info.status, "OFF") == 0 ){
					tick = xTaskGetTickCount();
					vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ / 1000);
					HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, SET);
					info.relay_no =0;
				}
				info.relay_no =0;

			}
			if(info.relay_no == 2 && strcmp(info.status, "OFF") == 0 && info.tim == 0)
			{
				 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, RESET);
			}

			vTaskDelayUntil(&tick, 1900 * configTICK_RATE_HZ / 1000);
		}
}
void task4(void *p)
{
	TickType_t tick;
	while (1) {
		vTaskSuspend(NULL);

		if (info.relay_no == 4 && strcmp(info.status, "ON") == 0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, SET);
			tick = xTaskGetTickCount();
			uint32_t time = info.tim;
			while (xTaskGetTickCount() - tick < time * configTICK_RATE_HZ / 1000)
			{
				if (info.relay_no == 4 && strcmp(info.status, "OFF") == 0)
				{
					goto off;
				}
			}

			off: HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
			if (info.tim > 0 && strcmp(info.status, "OFF") == 0 ) {
				tick = xTaskGetTickCount();
				vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ / 1000);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, SET);
				info.relay_no =0;
			}
			info.relay_no =0;

		}
		if (info.relay_no == 4 && strcmp(info.status, "OFF") == 0 && info.tim == 0) {
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, RESET);
		}

		vTaskDelayUntil(&tick, 1300 * configTICK_RATE_HZ / 1000);
	}

}
void task5(void *p)
{
	TickType_t tick;
	while(1)
	{vTaskSuspend(NULL);

		if(info.relay_no ==1 && strcmp(info.status,"ON")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			tick = xTaskGetTickCount();
			while(xTaskGetTickCount()-tick < info.tim * configTICK_RATE_HZ/1000)
			{
				if(info.relay_no == 1 && strcmp(info.status,"OFF")==0 && info.tim != 0)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					tick = xTaskGetTickCount();
					vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
					vTaskSuspend(NULL);

				}
				else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
						{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					vTaskSuspend(NULL);

				}
			}
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			tick = xTaskGetTickCount();
			vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
				{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no = 0;

		}

		vTaskDelayUntil(&tick, 1900 * configTICK_RATE_HZ/1000);
	}
}
void task6(void *p)
{
	TickType_t tick;
	while(1)
	{vTaskSuspend(NULL);

		if(info.relay_no ==1 && strcmp(info.status,"ON")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			tick = xTaskGetTickCount();
			while(xTaskGetTickCount()-tick < info.tim * configTICK_RATE_HZ/1000)
			{
				if(info.relay_no == 1 && strcmp(info.status,"OFF")==0 && info.tim != 0)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					tick = xTaskGetTickCount();
					vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
					vTaskSuspend(NULL);

				}
				else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
						{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					vTaskSuspend(NULL);

				}
			}
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			tick = xTaskGetTickCount();
			vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
				{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no = 0;

		}

		vTaskDelayUntil(&tick, 2800 * configTICK_RATE_HZ/1000);
	}
}
void task7(void *p)
{
	TickType_t tick;
	while(1)
	{vTaskSuspend(NULL);

		if(info.relay_no ==1 && strcmp(info.status,"ON")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			tick = xTaskGetTickCount();
			while(xTaskGetTickCount()-tick < info.tim * configTICK_RATE_HZ/1000)
			{
				if(info.relay_no == 1 && strcmp(info.status,"OFF")==0 && info.tim != 0)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					tick = xTaskGetTickCount();
					vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
					vTaskSuspend(NULL);

				}
				else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
						{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					vTaskSuspend(NULL);

				}
			}
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			tick = xTaskGetTickCount();
			vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
				{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no = 0;

		}

		vTaskDelayUntil(&tick, 1100 * configTICK_RATE_HZ/1000);
	}
}
void task8(void *p)
{
	TickType_t tick;
	while(1)
	{vTaskSuspend(NULL);

		if(info.relay_no ==1 && strcmp(info.status,"ON")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			tick = xTaskGetTickCount();
			while(xTaskGetTickCount()-tick < info.tim * configTICK_RATE_HZ/1000)
			{
				if(info.relay_no == 1 && strcmp(info.status,"OFF")==0 && info.tim != 0)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					tick = xTaskGetTickCount();
					vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
					vTaskSuspend(NULL);

				}
				else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
						{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					vTaskSuspend(NULL);

				}
			}
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			tick = xTaskGetTickCount();
			vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
				{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no = 0;

		}

		vTaskDelayUntil(&tick, 2800 * configTICK_RATE_HZ/1000);
	}
}
void task9(void *p)
{
	TickType_t tick;
	while(1)
	{vTaskSuspend(NULL);

		if(info.relay_no ==1 && strcmp(info.status,"ON")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			tick = xTaskGetTickCount();
			while(xTaskGetTickCount()-tick < info.tim * configTICK_RATE_HZ/1000)
			{
				if(info.relay_no == 1 && strcmp(info.status,"OFF")==0 && info.tim != 0)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					tick = xTaskGetTickCount();
					vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
					vTaskSuspend(NULL);

				}
				else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
						{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					vTaskSuspend(NULL);

				}
			}
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			tick = xTaskGetTickCount();
			vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
				{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no = 0;

		}

		vTaskDelayUntil(&tick, 2600 * configTICK_RATE_HZ/1000);
	}
}
void task13(void *p)
{
	//uint8_t b;
	TickType_t tick;
	tick = xTaskGetTickCount();
	while(1)
	{
		while(Received != TRUE)
		{
			HAL_UART_Receive_IT(&huart2, &bit, 1);
		}
		vTaskDelayUntil(&tick, 1000 * configTICK_RATE_HZ/1000);
	}
}
void task10(void *p)
{
	TickType_t tick;
	while(1)
	{vTaskSuspend(NULL);

		if(info.relay_no ==1 && strcmp(info.status,"ON")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			tick = xTaskGetTickCount();
			while(xTaskGetTickCount()-tick < info.tim * configTICK_RATE_HZ/1000)
			{
				if(info.relay_no == 1 && strcmp(info.status,"OFF")==0 && info.tim != 0)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					tick = xTaskGetTickCount();
					vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
					vTaskSuspend(NULL);

				}
				else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
						{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					vTaskSuspend(NULL);

				}
			}
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			tick = xTaskGetTickCount();
			vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
				{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no = 0;

		}

		vTaskDelayUntil(&tick, 2400 * configTICK_RATE_HZ/1000);
	}

}
void task11(void *p)
{
	TickType_t tick;
	while(1)
	{vTaskSuspend(NULL);

		if(info.relay_no ==1 && strcmp(info.status,"ON")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			tick = xTaskGetTickCount();
			while(xTaskGetTickCount()-tick < info.tim * configTICK_RATE_HZ/1000)
			{
				if(info.relay_no == 1 && strcmp(info.status,"OFF")==0 && info.tim != 0)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					tick = xTaskGetTickCount();
					vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
					vTaskSuspend(NULL);

				}
				else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
						{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					vTaskSuspend(NULL);

				}
			}
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			tick = xTaskGetTickCount();
			vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
				{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no = 0;

		}

		vTaskDelayUntil(&tick, 2100 * configTICK_RATE_HZ/1000);
	}

}
void task12(void *p)
{
	TickType_t tick;
	while(1)
	{vTaskSuspend(NULL);

		if(info.relay_no ==1 && strcmp(info.status,"ON")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			tick = xTaskGetTickCount();
			while(xTaskGetTickCount()-tick < info.tim * configTICK_RATE_HZ/1000)
			{
				if(info.relay_no == 1 && strcmp(info.status,"OFF")==0 && info.tim != 0)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					tick = xTaskGetTickCount();
					vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
					vTaskSuspend(NULL);

				}
				else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
						{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					vTaskSuspend(NULL);

				}
			}
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			tick = xTaskGetTickCount();
			vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
				{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no = 0;

		}

		vTaskDelayUntil(&tick, 1800 * configTICK_RATE_HZ/1000);
	}
}
void task3(void *p)
{
	TickType_t tick;
	while(1)
	{vTaskSuspend(NULL);

		if(info.relay_no ==1 && strcmp(info.status,"ON")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			tick = xTaskGetTickCount();
			while(xTaskGetTickCount()-tick < info.tim * configTICK_RATE_HZ/1000)
			{
				if(info.relay_no == 1 && strcmp(info.status,"OFF")==0 && info.tim != 0)
				{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					tick = xTaskGetTickCount();
					vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
					vTaskSuspend(NULL);

				}
				else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
						{
					HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
					vTaskSuspend(NULL);

				}
			}
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			tick = xTaskGetTickCount();
			vTaskDelayUntil(&tick, info.tim * configTICK_RATE_HZ/1000);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
			info.relay_no =0;

		}
		else if(info.relay_no ==1 && strcmp(info.status,"OFF")==0 && info.tim == 0)
				{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
			info.relay_no = 0;

		}

		vTaskDelayUntil(&tick, 1500 * configTICK_RATE_HZ/1000);
	}
}
int main()
{
	HAL_Init();
	GPIO_INIT();
	MX_USART2_UART_Init();
	//gatekeeper = xSemaphoreCreateBinary();
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
	xTaskCreate(task1, "task1", 100, (void*)0,tskIDLE_PRIORITY, &task1handle);
	xTaskCreate(task2, "task2", 100, (void*)0,tskIDLE_PRIORITY, &task2handle);
	xTaskCreate(task3, "task3", 100, (void*)0,tskIDLE_PRIORITY, &task3handle);
	xTaskCreate(task4, "task4", 100, (void*)0,tskIDLE_PRIORITY, &task4handle);
	xTaskCreate(task5, "task5", 100, (void*)0,tskIDLE_PRIORITY, &task5handle);
	xTaskCreate(task6, "task6", 100, (void*)0,tskIDLE_PRIORITY, &task6handle);
	xTaskCreate(task7, "task7", 100, (void*)0,tskIDLE_PRIORITY, &task7handle);
	xTaskCreate(task8, "task8", 100, (void*)0,tskIDLE_PRIORITY, &task8handle);
	xTaskCreate(task9, "task9", 100, (void*)0,tskIDLE_PRIORITY , &task9handle);
	xTaskCreate(task10,"task10", 100, (void*)0,tskIDLE_PRIORITY, &task10handle);
	xTaskCreate(task11,"task11", 100, (void*)0,tskIDLE_PRIORITY, &task11handle);
	xTaskCreate(task12,"task12", 100, (void*)0,tskIDLE_PRIORITY, &task12handle);
	xTaskCreate(task13,"task13", 100, (void*)0,tskIDLE_PRIORITY, &task13handle);

	printc("|||******************Nucleo-64 STMF446RE(online)******************|||\r\nCommand:~$ ");

	vTaskStartScheduler();
	while(1);
}


static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }

}

void printc(char *format, ...) {
		char str[80];
		va_list args;
		va_start(args, format);
		vsprintf(str, format, args);
		HAL_UART_Transmit(&huart2, (uint8_t*) str, strlen(str), HAL_MAX_DELAY);
		//cannot use _IT since interrupt time is very low so only some of message will get printed and interrupt will be triggered
		va_end(args);
	}


void GPIO_INIT(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitTypeDef ledgpio , buttongpio;

	ledgpio.Pin = GPIO_PIN_5;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&ledgpio);

	ledgpio.Pin = GPIO_PIN_2;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB,&ledgpio);

	ledgpio.Pin = GPIO_PIN_8;
	ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA,&ledgpio);

	buttongpio.Pin = GPIO_PIN_13;
	buttongpio.Mode = GPIO_MODE_IT_FALLING;
	buttongpio.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOC,&buttongpio);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn,10,0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);


}

void EXTI15_10_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
	HAL_UART_Receive(&huart2, (uint8_t*)msg, 15, HAL_MAX_DELAY);

	Decode_CMD(msg);
	 printc("Relay is %d, status is %s, time is %d \r\n", info.relay_no, info.status,info.tim);

	if(info.relay_no ==1 )
	{
		BaseType_t checkforresume;
		checkforresume = xTaskResumeFromISR(task1handle);
		portYIELD_FROM_ISR(checkforresume);

	}
	else if(info.relay_no ==2 )
	{
		BaseType_t checkforresume;
		checkforresume = xTaskResumeFromISR(task2handle);
		portYIELD_FROM_ISR(checkforresume);
	}
	else if(info.relay_no ==3 )
	{
		BaseType_t checkforresume;
		checkforresume = xTaskResumeFromISR(task3handle);
		portYIELD_FROM_ISR(checkforresume);
	}
	else if(info.relay_no ==4 )
	{
		BaseType_t checkforresume;
		checkforresume = xTaskResumeFromISR(task4handle);
		portYIELD_FROM_ISR(checkforresume);
	}
	else if(info.relay_no ==5 )
	{
		BaseType_t checkforresume;
		checkforresume = xTaskResumeFromISR(task5handle);
		portYIELD_FROM_ISR(checkforresume);
	}
	else if(info.relay_no ==6 )
	{
		BaseType_t checkforresume;
		checkforresume = xTaskResumeFromISR(task6handle);
		portYIELD_FROM_ISR(checkforresume);
	}
	else if(info.relay_no ==7 )
	{
		BaseType_t checkforresume;
		checkforresume = xTaskResumeFromISR(task7handle);
		portYIELD_FROM_ISR(checkforresume);
	}
	else if(info.relay_no ==8 )
	{
		BaseType_t checkforresume;
		checkforresume = xTaskResumeFromISR(task8handle);
		portYIELD_FROM_ISR(checkforresume);
	}
	else if(info.relay_no ==9 )
	{
		BaseType_t checkforresume;
		checkforresume = xTaskResumeFromISR(task9handle);
		portYIELD_FROM_ISR(checkforresume);
	}
	else if(info.relay_no ==10 )
	{
		BaseType_t checkforresume;
		checkforresume = xTaskResumeFromISR(task10handle);
		portYIELD_FROM_ISR(checkforresume);
	}
	else if(info.relay_no ==11 )
	{
		BaseType_t checkforresume;
		checkforresume = xTaskResumeFromISR(task11handle);
		portYIELD_FROM_ISR(checkforresume);
	}
	else if(info.relay_no ==12 )
	{
		BaseType_t checkforresume;
		checkforresume = xTaskResumeFromISR(task12handle);
		portYIELD_FROM_ISR(checkforresume);
	}

}

void Decode_CMD(char *msg) {

	char msg_read[10][10];
	uint32_t i = 0;

	char *token = strtok(msg, "SR().,\r\n ");
	while (token != NULL) {
		strcpy(msg_read[i], token);
		token = strtok(NULL, "SR().,\r\n ");
		i++;
	}
	memset(&info,0,sizeof(info));
	sscanf(msg_read[0], "%ld", &info.relay_no);
	strcpy(info.status, msg_read[1]);
	sscanf(msg_read[2], "%ld", &info.tim);
	info.count =0;
	memset(&msg,0,sizeof(msg));
}

void USART2_IRQHandler(void)
{
	HAL_UART_IRQHandler(&huart2);
//	HAL_UART_Receive(&huart2, (uint8_t*)msg, 14, HAL_MAX_DELAY);
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

	if(bit == '\r')
		 {
			 Received = TRUE;
			 msg[info.count++]='\r';
			 printc("%s",msg);

			 Decode_CMD(msg);
			 printc("Relay is %d, status is %s, time is %d \r\n", info.relay_no, info.status,info.tim);
			 printc("Command:~$ ");
			 if(info.relay_no ==1 )
			 	{
			 		BaseType_t checkforresume;
			 		checkforresume = xTaskResumeFromISR(task1handle);
			 		portYIELD_FROM_ISR(checkforresume);
			 	}
			 	else if(info.relay_no ==2 )
			 	{
			 		BaseType_t checkforresume;
			 		checkforresume = xTaskResumeFromISR(task2handle);
			 		portYIELD_FROM_ISR(checkforresume);
			 	}
			 	else if(info.relay_no ==3 )
			 	{
			 		BaseType_t checkforresume;
			 		checkforresume = xTaskResumeFromISR(task3handle);
			 		portYIELD_FROM_ISR(checkforresume);
			 	}
			 	else if(info.relay_no ==4 )
			 	{
			 		BaseType_t checkforresume;
			 		checkforresume = xTaskResumeFromISR(task4handle);
			 		portYIELD_FROM_ISR(checkforresume);
			 	}
			 	else if(info.relay_no ==5 )
			 	{
			 		BaseType_t checkforresume;
			 		checkforresume = xTaskResumeFromISR(task5handle);
			 		portYIELD_FROM_ISR(checkforresume);
			 	}
			 	else if(info.relay_no ==6 )
			 	{
			 		BaseType_t checkforresume;
			 		checkforresume = xTaskResumeFromISR(task6handle);
			 		portYIELD_FROM_ISR(checkforresume);
			 	}
			 	else if(info.relay_no ==7 )
			 	{
			 		BaseType_t checkforresume;
			 		checkforresume = xTaskResumeFromISR(task7handle);
			 		portYIELD_FROM_ISR(checkforresume);
			 	}
			 	else if(info.relay_no ==8 )
			 	{
			 		BaseType_t checkforresume;
			 		checkforresume = xTaskResumeFromISR(task8handle);
			 		portYIELD_FROM_ISR(checkforresume);
			 	}
			 	else if(info.relay_no ==9 )
			 	{
			 		BaseType_t checkforresume;
			 		checkforresume = xTaskResumeFromISR(task9handle);
			 		portYIELD_FROM_ISR(checkforresume);
			 	}
			 	else if(info.relay_no ==10 )
			 	{
			 		BaseType_t checkforresume;
			 		checkforresume = xTaskResumeFromISR(task10handle);
			 		portYIELD_FROM_ISR(checkforresume);
			 	}
			 	else if(info.relay_no ==11 )
			 	{
			 		BaseType_t checkforresume;
			 		checkforresume = xTaskResumeFromISR(task11handle);
			 		portYIELD_FROM_ISR(checkforresume);
			 	}
			 	else if(info.relay_no ==12 )
			 	{
			 		BaseType_t checkforresume;
			 		checkforresume = xTaskResumeFromISR(task12handle);
			 		portYIELD_FROM_ISR(checkforresume);
			 	}
			 	else
			 	{
			 		printc("Invalid Command\r\n");
			 	}


			 Received = FALSE;
			 info.count = 0;
			 memset(&msg,0,sizeof(msg));
		 }
		 else
		 {
			 msg[info.count++] = bit;
		 }
}
void Error_Handler(void)
{
	printc("Error Occurred\r\n");
	while(1);
}
