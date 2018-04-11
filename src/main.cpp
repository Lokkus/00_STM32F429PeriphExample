/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "user_startup.h"
#include "user_logger.h"
#include "stm32f4xx.h"
#include "stm32f429xx.h"
#include <vector>
#include <cstdlib>

Startup startup;
Logger logger;

char znaktest;
std::string s;
std::vector<std::string> testowy;

int licznik = 0;


int main(void)
{
    startup.enableStartup();
    logger.enableIRQ(1, 1);
    logger.enableLogger();
    logger.clearScreen();
    HAL_Delay(500);
    logger.sendData<double,10>(132.6665);
    HAL_Delay(500);
    logger.setCursor(20, 20);
    while(1)
    {

    }

	return 0;
}


