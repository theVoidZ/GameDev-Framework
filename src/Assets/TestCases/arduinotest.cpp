#include "arduinotest.h"

#include "Assets/TestCases/simulatorcomponent.h"
#include "time_management/timewinder.h"

ArduinoTest::ArduinoTest()
{

}

void ArduinoTest::update(sf::Time dt){

}

void ArduinoTest::onBecameVisible(){
//    std::cout << "Visible" << std::endl;
    serial.setPortName("/dev/ttyACM0");
    serial.open(QIODevice::ReadWrite);
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    if (serial.isOpen() && serial.isWritable())
    {
        QByteArray ba("R");
        serial.write(ba);
        serial.flush();
        serial.close();
    }
}

void ArduinoTest::onBecameInvisible(){
//    std::cout << "Invisible" << std::endl;
    serial.setPortName("/dev/ttyACM0");
    serial.open(QIODevice::ReadWrite);
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    if (serial.isOpen() && serial.isWritable())
    {
        QByteArray ba("R");
        serial.write(ba);
        serial.flush();
        serial.close();
    }
}

void ArduinoTest::spam(){
    std::cout << "Spam from ArduinoTest: gameObject= " << game_object()->name() << std::endl;
}
