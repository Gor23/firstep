/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"
#include "usb_device.h"
#include "main.h"
#include "usbd_cdc_if.h"
#include "string.h"



/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim6;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void Error_Handler(void);
static void MX_GPIO_Init(void);
static void MX_TIM6_Init(void);
static void MX_USART2_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

//////////globals//////////
//#define VIDEO_1  0x77;
//#define VIDEO_1  0x72;
#define MAX_FRAME	32

volatile uint32_t timer1;

/////////////// image works/////////////
typedef struct {
   uint32_t size;
   uint16_t xLength;		//bit (pixels)
   uint16_t yLength;			// byte (matrix)
   uint16_t xOffset;
   uint16_t yOffset;
   const uint8_t *imageArrayPtr;
}image;

typedef struct {
   uint32_t size;
   uint16_t xLength;		//bit (pixels)
   uint16_t yLength;			// byte (matrix)
   uint8_t *imageArrayPtr;
}videoBuff;

static const uint8_t lcd_image_ball[128] =
{ 0x00, 0x00, 0x80, 0x00, 0xE0, 0x10, 0x00, 0x04,
  0x00, 0x02, 0x00, 0x80, 0x41, 0x20, 0x00, 0x0E,
  0x0E, 0x1F, 0x1F, 0x1F, 0x3E, 0x3E, 0x3E, 0x3C,
  0x1C, 0x08, 0x20, 0x00, 0x00, 0x80, 0x00, 0x00,
  0x10, 0x02, 0x00, 0xF0, 0xFF, 0xFE, 0xFE, 0xFF,
  0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x80, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xC0, 0xE2,
  0xE0, 0xC0, 0xC0, 0x80, 0x00, 0x01, 0x06, 0x70,
  0x0C, 0x41, 0x00, 0x01, 0x03, 0x07, 0x07, 0x47,
  0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0x7F, 0xFF, 0x1F, 0x01, 0x00, 0x40, 0x0C,
  0x00, 0x00, 0x01, 0x02, 0x00, 0x08, 0x00, 0x38,
  0x3E, 0x7C, 0x78, 0x78, 0xF8, 0xF0, 0xF0, 0x70,
  0x08, 0x00, 0x80, 0x81, 0x00, 0x40, 0x40, 0x00,
  0x00, 0x10, 0x08, 0x04, 0x02, 0x00, 0x00, 0x00};

static const uint8_t lcd_image_mas[256] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
  0x40, 0x20, 0x00, 0x10, 0x08, 0x00, 0x04, 0x00,
  0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80,
  0x80, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00, 0x20,
  0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xC0, 0xF0, 0xEC, 0xF2, 0xAC, 0xE0,
  0x40, 0xE8, 0x48, 0xF0, 0x58, 0x46, 0x51, 0x40,
  0x40, 0x40, 0x40, 0x20, 0x20, 0x20, 0x20, 0x10,
  0x10, 0x18, 0x08, 0x08, 0x04, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00,
  0x40, 0x20, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00,
  0x80, 0x00, 0x88, 0x40, 0xA0, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x07, 0x0F, 0x1F, 0x3F, 0x7E, 0xFF,
  0xBE, 0x3E, 0x73, 0xFF, 0xD8, 0xFA, 0x89, 0xC8,
  0xD9, 0x88, 0xC8, 0xCC, 0x4D, 0xAC, 0x2C, 0x0C,
  0x60, 0x60, 0x28, 0x60, 0x40, 0xA4, 0x88, 0xC8,
  0x88, 0xA8, 0x08, 0x68, 0x38, 0x6A, 0xA8, 0xE8,
  0x4C, 0x74, 0x60, 0x68, 0xD6, 0x54, 0xD4, 0x8C,
  0x5E, 0x06, 0xAC, 0xEC, 0x0F, 0xD6, 0x78, 0x33,
  0x5E, 0x1F, 0x1E, 0x03, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x01, 0x02, 0x03, 0x01, 0x03, 0x07, 0x03,
  0x07, 0x13, 0x07, 0x2F, 0x07, 0x0B, 0x07, 0x0E,
  0x1F, 0x06, 0x1D, 0x0E, 0x0F, 0x06, 0x3B, 0x2D,
  0x0D, 0x3A, 0x1C, 0x06, 0x0F, 0x1F, 0x1F, 0x17,
  0x17, 0x1F, 0x0F, 0x03, 0x0F, 0x07, 0x07, 0x07,
  0x0F, 0x07, 0x01, 0x04, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void put_image (image *imgPtr, videoBuff *videoBuffPtr)
{
	uint32_t y = 0;
	uint32_t x = 0;
	uint32_t temp = 0;


	for (y=0; y < imgPtr->yLength; y++)
	{
		for (x=0; x < imgPtr->xLength; x++)
		{
			videoBuffPtr->imageArrayPtr[x + y*videoBuffPtr->xLength + imgPtr->xOffset + imgPtr->yOffset] = imgPtr->imageArrayPtr[temp++];
		}
	}
}

void move_image (image *imgPtr, videoBuff *videoBuffPtr, uint32_t xMove, uint32_t yMove)
{
	memset (videoBuffPtr->imageArrayPtr, 0x00, videoBuffPtr->size);
	imgPtr->xOffset = xMove;
	imgPtr->yOffset = videoBuffPtr->xLength*yMove;
}

int main(void)
{

image ballImage;
videoBuff mainBuffer;

////image properties////////


extern uint8_t UserRxBufferFS[APP_RX_DATA_SIZE];

uint8_t yPosition = 0;
uint8_t frame = 0;
uint8_t init_array[] = {'I', 'N', 1, 1};
uint8_t tranceve_array [MAX_FRAME] [TRANCIEVE_ARRAY_SIZE];
uint8_t videoBuffer[TRANCIEVE_ARRAY_SIZE];

uint8_t recieve_array [10];
char *ptr_char0;

///////////////////// set buffer an images properties
ballImage.xLength = 32;
ballImage.yLength = 4;
ballImage.size = ballImage.xLength*ballImage.yLength*8;
ballImage.xOffset = 0;
ballImage.yOffset = 0;
ballImage.imageArrayPtr = lcd_image_ball;

mainBuffer.xLength = 64;
mainBuffer.yLength = 4;
mainBuffer.size = mainBuffer.xLength * mainBuffer.yLength * 8;
mainBuffer.imageArrayPtr = videoBuffer;
///////////////////////////


memset (&tranceve_array[0][0], 0x01, TRANCIEVE_ARRAY_SIZE);
memset (&tranceve_array[1][0], 0x02, TRANCIEVE_ARRAY_SIZE);
memset (&tranceve_array[2][0], 0x04, TRANCIEVE_ARRAY_SIZE);
memset (&tranceve_array[3][0], 0x08, TRANCIEVE_ARRAY_SIZE);
memset (&tranceve_array[4][0], 0x10, TRANCIEVE_ARRAY_SIZE);
memset (&tranceve_array[5][0], 0x20, TRANCIEVE_ARRAY_SIZE);
memset (&tranceve_array[6][0], 0x40, TRANCIEVE_ARRAY_SIZE);
memset (&tranceve_array[7][0], 0x80, TRANCIEVE_ARRAY_SIZE);
memset (videoBuffer, 0x00, TRANCIEVE_ARRAY_SIZE);

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM6_Init();
  MX_USART2_UART_Init();
  MX_USB_DEVICE_Init();

  HAL_TIM_Base_Start_IT(&htim6);

  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  USER_UART_enable_RX_IT(&huart2);
  USER_UART_clear_rx(&huart2);
  HAL_Delay(100);
  HAL_UART_Transmit_IT(&huart2, (uint8_t*)&init_array, 4);
  HAL_Delay(100);
  while (1)
  {
	  //CDC_Transmit_FS((uint8_t*)"START", strlen("START"));
	  if (timer1 == TIMER_1_STOP_VALUE)
	  {
		 memset (videoBuffer, 0x00, TRANCIEVE_ARRAY_SIZE);
		 move_image(&ballImage, &mainBuffer, frame, 0);
		 HAL_UART_Transmit_IT(&huart2, (uint8_t*)"BUFC", 4);
		 HAL_Delay(1);

		 //HAL_UART_Transmit_IT(&huart2, (uint8_t*)&tranceve_array[frame][0], TRANCIEVE_ARRAY_SIZE);
		 //Strings_put_string ("HELLO", videoBuff, frame, yPosition, 64);

		 put_image(&ballImage, &mainBuffer);

		 HAL_UART_Transmit_IT(&huart2, (uint8_t*)&videoBuffer, TRANCIEVE_ARRAY_SIZE);


		  frame++;
		  if (frame == MAX_FRAME)
		  {
			  if (yPosition>2) yPosition = 0;
			  else yPosition++ ;
			  frame = 0;
		  }
		  timer1 = 0;
	  }



  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/


void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB|RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.USBClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* TIM6 init function */
static void MX_TIM6_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;

  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 7199;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 9;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 256000;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_RS485Ex_Init(&huart2, UART_DE_POLARITY_HIGH, 0, 0) != HAL_OK)
  {
    Error_Handler();
  }

}

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
     PA5   ------> SPI1_SCK
     PA6   ------> SPI1_MISO
     PA7   ------> SPI1_MOSI
     PB6   ------> I2C1_SCL
     PB7   ------> I2C1_SDA
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : DRDY_Pin MEMS_INT3_Pin MEMS_INT4_Pin MEMS_INT1_Pin
                           MEMS_INT2_Pin */
  GPIO_InitStruct.Pin = DRDY_Pin|MEMS_INT3_Pin|MEMS_INT4_Pin|MEMS_INT1_Pin
                          |MEMS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : CS_I2C_SPI_Pin LD4_Pin LD3_Pin LD5_Pin
                           LD7_Pin LD9_Pin LD10_Pin LD8_Pin
                           LD6_Pin */
  GPIO_InitStruct.Pin = CS_I2C_SPI_Pin|LD4_Pin|LD3_Pin|LD5_Pin
                          |LD7_Pin|LD9_Pin|LD10_Pin|LD8_Pin
                          |LD6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PA5 PA6 SPI1_MISO_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|SPI1_MISO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, CS_I2C_SPI_Pin|LD4_Pin|LD3_Pin|LD5_Pin
                          |LD7_Pin|LD9_Pin|LD10_Pin|LD8_Pin
                          |LD6_Pin, GPIO_PIN_RESET);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler */
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */

/**
  * @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
