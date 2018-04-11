/*
 * user_startup.h
 *
 *  Created on: 18 sty 2018
 *      Author: lokkus
 */

#ifndef USER_STARTUP_H_
#define USER_STARTUP_H_

#include "stm32f4xx_hal.h"

class Startup
{
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    GPIO_TypeDef* GPIO_ErrorHandlerInstance;
    GPIO_InitTypeDef GPIO_ErrorHandlerInit;
public:
    Startup();
    void enableGPIOclock(GPIO_TypeDef* GPIO_Instance);
    void changeDefaultParams(RCC_OscInitTypeDef _RCC_OscInitStruct, RCC_ClkInitTypeDef _RCC_ClkInitStruct,
            GPIO_TypeDef* _GPIO_ErrorHandlerInstance, GPIO_InitTypeDef _GPIO_ErrorHandlerInit);
    void errorHandler();
    void enableStartup(uint32_t PreemptPriority = 0, uint32_t SubPriority = 0);

};



#endif /* USER_STARTUP_H_ */
