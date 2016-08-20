#ifndef ARDUINOTEST_H
#define ARDUINOTEST_H

#include <iostream>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include "Core/System/monobehavior.h"

//! NOTE: Arduino Behavior, Is abstract because it MUST contain its own logic.

class ArduinoTest : public MonoBehavior
{
    Q_OBJECT
    public:
        ArduinoTest();

    public:
        void update(sf::Time dt);

        void onBecameVisible();
        void onBecameInvisible();


        void spam();
    private:
        QSerialPort serial;
};

#endif // ARDUINOTEST_H
