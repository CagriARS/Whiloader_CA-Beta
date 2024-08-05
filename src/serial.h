#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>

/**
 * @class Serial
 * @brief Handles serial port communication.
 *
 * The Serial class provides functionalities to open, close, read from, and write to a serial port.
 */

class Serial : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Get the singleton instance of the Serial class.
     * @return Reference to the singleton instance of Serial.
     */

    static Serial& instance();
    /**
     * @brief Get the QSerialPort object.
     * @return Pointer to the QSerialPort object.
     */
    QSerialPort* port();
    /**
     * @brief Open a serial port with the specified settings.
     * @param portName The name of the port to open.
     * @param baudRate The baud rate for the connection.
     * @param dataBits The number of data bits in each character.
     * @param parity The parity setting for the connection.
     * @param stopBits The number of stop bits in each character.
     * @param flowControl The flow control setting for the connection.
     */

    void openPort(const QString &portName, int baudRate, QSerialPort::DataBits dataBits,
                  QSerialPort::Parity parity, QSerialPort::StopBits stopBits,
                  QSerialPort::FlowControl flowControl);
    /**
     * @brief Close the currently open serial port.
     */

    void closePort();
    /**
     * @brief Write data to the serial port.
     * @param data The data to write.
     */
    void writeData(const QByteArray &data);
    /**
     * @brief Read data from the serial port.
     * @return The data read from the serial port.
     */

    QByteArray readData();

private:
    /**
     * @brief Constructor for the Serial class.
     * @param parent The parent QObject, default is nullptr.
     */
    explicit Serial(QObject *parent = nullptr);
    /**
     * @brief Destructor for the Serial class.
     */
    ~Serial() override;

    Serial(const Serial&) = delete;
    Serial& operator=(const Serial&) = delete;

    QSerialPort* serialPort;

private slots:
    /**
     * @brief Handle serial port errors.
     * @param error The error code.
     */
    void handleSerialError(QSerialPort::SerialPortError error);

signals:
    /**
     * @brief Signal emitted when a serial port error occurs.
     * @param error The error message.
     */
    void serialError(QString error);
};

#endif // SERIAL_H
