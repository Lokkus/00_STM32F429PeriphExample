/*
 * user_startup.cpp
 *
 *  Created on: 18 sty 2018
 *      Author: lokkus
 */

#include <user_startup.h>

Startup::Startup()
{
    //enable clocks
    __HAL_RCC_GPIOG_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();

    // init gpio for error handler (green and red LED for STM32F429xx on DISCO
    GPIO_ErrorHandlerInstance = GPIOG;
    GPIO_ErrorHandlerInit.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_ErrorHandlerInit.Pin = GPIO_PIN_14 | GPIO_PIN_13;
    GPIO_ErrorHandlerInit.Pull = GPIO_NOPULL;
    GPIO_ErrorHandlerInit.Speed = GPIO_SPEED_FAST;

    //Initializes the CPU, AHB and APB busses clocks
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 180;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;


    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
}

void Startup::errorHandler()
{
    HAL_GPIO_WritePin(GPIO_ErrorHandlerInstance, GPIO_ErrorHandlerInit.Pin, GPIO_PIN_SET);
}

void Startup::changeDefaultParams(RCC_OscInitTypeDef _RCC_OscInitStruct, RCC_ClkInitTypeDef _RCC_ClkInitStruct,
        GPIO_TypeDef* _GPIO_ErrorHandlerInstance, GPIO_InitTypeDef _GPIO_ErrorHandlerInit)
{
    RCC_OscInitStruct = _RCC_OscInitStruct;
    RCC_ClkInitStruct = _RCC_ClkInitStruct;
    GPIO_ErrorHandlerInstance = _GPIO_ErrorHandlerInstance;
    GPIO_ErrorHandlerInit = _GPIO_ErrorHandlerInit;
    if(GPIO_ErrorHandlerInstance == GPIOA)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    }
    if(GPIO_ErrorHandlerInstance == GPIOB)
    {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }
    if(GPIO_ErrorHandlerInstance == GPIOC)
    {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }
    if(GPIO_ErrorHandlerInstance == GPIOD)
    {
        __HAL_RCC_GPIOD_CLK_ENABLE();
    }
    if(GPIO_ErrorHandlerInstance == GPIOE)
    {
        __HAL_RCC_GPIOE_CLK_ENABLE();
    }
    if(GPIO_ErrorHandlerInstance == GPIOF)
    {
        __HAL_RCC_GPIOF_CLK_ENABLE();
    }
    if(GPIO_ErrorHandlerInstance == GPIOI)
    {
        __HAL_RCC_GPIOI_CLK_ENABLE();
    }

}

void Startup::enableStartup(uint32_t PreemptPriority, uint32_t SubPriority)
{
    HAL_Init();
    HAL_GPIO_Init(GPIO_ErrorHandlerInstance, &GPIO_ErrorHandlerInit);
    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        errorHandler();
    }
    //Activate the Over-Drive mode
    if (HAL_PWREx_EnableOverDrive() != HAL_OK)
    {
        errorHandler();
    }

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        errorHandler();
    }
    //Configure the Systick interrupt time
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    //Configure the Systick
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    //SysTick_IRQn interrupt configuration
    HAL_NVIC_SetPriority(SysTick_IRQn, PreemptPriority, SubPriority);

}

