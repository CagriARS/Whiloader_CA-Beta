/**
 * @file mainwindow.cpp
 * @brief Implementation of the MainWindow class.
 */
#include "serial.h"
#include <QDebug>


/**
 * @brief Constructor for MainWindow. Initializes user interface components and configures serial port settings.
 *
 * This constructor initializes the UI components, sets default values for the baud rate and other serial port settings,
 * populates the serial port combo box with available ports, and connects UI signals to their respective slots.
 *
 * @param parent Parent widget, typically nullptr for main windows.
 */


Serial& Serial::instance()
{
    static Serial instance; /* Singleton instance, created only once */
    return instance;
}

/**
 * @brief Constructor for the Serial class.
 * @param parent The parent QObject, default is nullptr.
 */
Serial::Serial(QObject *parent) : QObject(parent)
{
    serialPort = new QSerialPort(this);
    connect(serialPort, &QSerialPort::errorOccurred, this, &Serial::handleSerialError);
}

/**
 * @brief Destructor for the Serial class.
 */
Serial::~Serial()
{
    delete serialPort;
}

/**
 * @brief Get the QSerialPort object.
 * @return Pointer to the QSerialPort object.
 */
QSerialPort* Serial::port()
{
    return serialPort;
}

/**
 * @brief Open a serial port with the specified settings.
 * @param portName The name of the port to open.
 * @param baudRate The baud rate for the connection.
 * @param dataBits The number of data bits in each character.
 * @param parity The parity setting for the connection.
 * @param stopBits The number of stop bits in each character.
 * @param flowControl The flow control setting for the connection.
 */
void Serial::openPort(const QString &portName, int baudRate, QSerialPort::DataBits dataBits,
                      QSerialPort::Parity parity, QSerialPort::StopBits stopBits,
                      QSerialPort::FlowControl flowControl)
{
    serialPort->setPortName(portName);
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(dataBits);
    serialPort->setParity(parity);
    serialPort->setStopBits(stopBits);
    serialPort->setFlowControl(flowControl);

    if (serialPort->open(QIODevice::ReadWrite))
    {
        qDebug() << "Serial port successfully opened.";
    }
    else
    {
        qDebug() << "Failed to open serial port:" << serialPort->errorString();
    }
}

/**
 * @brief Close the currently open serial port.
 */
void Serial::closePort()
{
    if (serialPort->isOpen())
    {
        serialPort->close();
    }
}

/**
 * @brief Write data to the serial port.
 * @param data The data to write.
 */
void Serial::writeData(const QByteArray &data)
{
    if (serialPort->isOpen())
    {
        serialPort->write(data);
    }
}

/**
 * @brief Read data from the serial port.
 * @return The data read from the serial port.
 */
QByteArray Serial::readData()
{
    QByteArray data;
    if (serialPort->isOpen() && serialPort->bytesAvailable())
    {
        data = serialPort->readAll();
    }
    return data;
}

/**
 * @brief Handle serial port errors.
 * @param error The error code.
 */
void Serial::handleSerialError(QSerialPort::SerialPortError error)
{
    if (error != QSerialPort::NoError)
    {
        qDebug() << "Serial error:" << serialPort->errorString();
        emit serialError(serialPort->errorString());
    }
}
