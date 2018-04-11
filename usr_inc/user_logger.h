/*
 * user_logger.h
 *
 *  Created on: 1 kwi 2018
 *      Author: lokkus
 */

#ifndef USER_LOGGER_H_
#define USER_LOGGER_H_

#include "stm32f4xx_hal.h"
#include <string>
#include <sstream>
#include <vector>

class Logger
{
    UART_HandleTypeDef huart;
    GPIO_InitTypeDef initgpio;
    std::string dataToSend;
    std::string receivedData;
    std::vector<std::string> receivedVecOfStrings;
    template<typename T>
    void sendFun(T data,  std::streamsize str = 5, std::ios_base::fmtflags f = std::ios_base::dec)
    {
        std::stringstream ss;
        ss.precision(str);
        ss.flags(f);
        ss<<data;
        dataToSend = ss.str();
        if(dataToSend.find('\n') == std::string::npos)
            dataToSend += '\n';
        if(dataToSend.find('\r') == std::string::npos)
            dataToSend +='\r';
        send();
    }
    void send();
public:
    Logger();
    void enableIRQ(uint32_t PreemptPriority = 0, uint32_t SubPriority = 0);
    USART_TypeDef* getUSARTinstance();
    //std::string getDataToSend() const;
    void enableLogger();
    void writeToReceivedData();
    void writeToReceivedData(uint8_t row);
    void addCharacterToReceivedData(char ch);
    void sendSingleCharacter(char c);
    char getSingleCharacter();
    void addReceivedStringToVector();
    void clearScreen();
    void setCursorToZero();
    void setCursor(uint16_t x, uint16_t y);
    //void moveCursorUp(uint8_t lines);
    template<typename T, std::streamsize str = 5, std::ios_base::fmtflags f = std::ios_base::dec>
    void sendData(T data)
    {
        sendFun(data, str, f);
    }

    template<typename T, std::streamsize str = 5, std::ios_base::fmtflags f = std::ios_base::dec>
    Logger& operator<<(T data)
    {
        sendFun(data, str, f);
        return *this;
    }

};


#endif /* USER_LOGGER_H_ */
