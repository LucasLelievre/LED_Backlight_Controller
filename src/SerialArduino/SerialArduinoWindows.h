/**
 * @file SerialArduinoWindows.h
 * @author Lucas Lelièvre
 * @brief Based on code example from arduino : https://playground.arduino.cc/Interfacing/CPPWindows/
 * @version 0.1
 * @date 2021-12-11
 * 
 * @copyright Copyright (c) 2021 Arduino.cc
 * 
 */

#pragma once

#ifndef SERIALCLASS_H_INCLUDED
    #define SERIALCLASS_H_INCLUDED
#endif

#define ARDUINO_WAIT_TIME 2000

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "SerialArduino.h"

class SerialArduinoWindows: public SerialArduino {
private:
    //Serial comm handler
    HANDLE hSerial;
    //Get various information about the connection
    COMSTAT status;
    //Keep track of last error
    DWORD errors;
    //Connection status
    bool connected;
public:
    //Initialize Serial communication with the given COM port
    SerialArduinoWindows(const char* portName);
    //Close the connection
    ~SerialArduinoWindows();
    //Read data in a buffer, if nbChar is greater than the
    //maximum number of bytes available, it will return only the
    //bytes available. The function return -1 when nothing could
    //be read, the number of bytes actually read.
    int readData(char* buffer, unsigned int nbChar);
    //Writes data from a buffer through the Serial connection
    //return true on success.
    bool writeData(const char* buffer, unsigned int nbChar);
    //Check if we are actually connected
    bool isConnected();
};