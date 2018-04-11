/*
 * user_logger.cpp
 *
 *  Created on: 1 kwi 2018
 *      Author: lokkus
 */

#include "user_logger.h"
#include "user_startup.h"
extern Startup startup;

using namespace std;

Logger::Logger()
{
    huart.Instance = USART1;
    huart.Init.BaudRate = 9600;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.WordLength = UART_WORDLENGTH_8B;

    initgpio.Alternate = GPIO_AF7_USART1;
    initgpio.Mode = GPIO_MODE_AF_PP;
    initgpio.Pin = GPIO_PIN_9 | GPIO_PIN_10;
    initgpio.Pull = GPIO_NOPULL;
    initgpio.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

}

void Logger::enableLogger()
{
    __HAL_RCC_USART1_CLK_ENABLE();           // PA9 -> UART_TX;     PA10 -> UART_RX
    __HAL_RCC_GPIOA_CLK_ENABLE();              // GPIOA CLK ENABLE

    if(HAL_UART_Init(&huart) != HAL_OK)
    {
        startup.errorHandler();
    }

    HAL_GPIO_Init(GPIOA, &initgpio);

    enableIRQ();
}

void Logger::enableIRQ(uint32_t PreemptPriority, uint32_t SubPriority)
{
    HAL_NVIC_SetPriority(USART1_IRQn, PreemptPriority, SubPriority);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    getUSARTinstance()->CR1 |= USART_CR1_RXNEIE;         // wlaczenie przerwania do odbierania danych
}

USART_TypeDef* Logger::getUSARTinstance()
{
    return huart.Instance;
}
void Logger::send()
{
    for(auto a : dataToSend)
    {
        getUSARTinstance()->DR = a;
        while(!(getUSARTinstance()->SR & USART_SR_TXE));
    }
}

void Logger::sendSingleCharacter(char c)
{
    getUSARTinstance()->DR = c;
}

char Logger::getSingleCharacter()
{
    return getUSARTinstance()->DR;
}

void Logger::addCharacterToReceivedData(char ch)
{
    receivedData.push_back(ch);
}

void Logger::writeToReceivedData()
{
    for(auto a : receivedVecOfStrings)
    {
        sendData(a);
    }
    receivedVecOfStrings.clear();
}

void Logger::writeToReceivedData(uint8_t row)
{
    sendData(receivedVecOfStrings.at(row));
}

void Logger::addReceivedStringToVector()
{
    receivedVecOfStrings.push_back(receivedData);
    receivedData.clear();
}

void Logger::clearScreen()
{
    dataToSend = "\033[2J";
    send();
    dataToSend = "\033[0;0H";
    send();
}

void Logger::setCursorToZero()
{
    dataToSend = "\033[0;0H";
    send();
}

void Logger::setCursor(uint16_t x, uint16_t y)
{
    stringstream oss;
    oss<<"\033["<<x<<";"<<y<<+"H";
    dataToSend = oss.str();
    send();
}



