/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @author  Ac6
  * @version V1.0
  * @date    02-Feb-2015
  * @brief   Default Interrupt Service Routines.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#ifdef USE_RTOS_SYSTICK
#include <cmsis_os.h>
#endif
#include "stm32f4xx_it.h"
#include "user_logger.h"

extern Logger logger;

/******************************************************************************/
/*            	  	    Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles SysTick Handler, but only if no RTOS defines it.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
#ifdef USE_RTOS_SYSTICK
	osSystickHandler();
#endif
}

extern "C" void USART1_IRQHandler(void)
{
    char c = 0;
    while(logger.getUSARTinstance()->SR & USART_SR_RXNE)
    {
        c = logger.getSingleCharacter();
        logger.sendSingleCharacter(c);
        if(c == '\r')
        {
            logger.addCharacterToReceivedData(c);
            logger.addCharacterToReceivedData('\n');
            logger.addReceivedStringToVector();
            logger.sendData('\n');
        }
        else
        {
            logger.addCharacterToReceivedData(c);
        }
    }
}



