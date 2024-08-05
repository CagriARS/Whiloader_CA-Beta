/**
 * @file mainwindow.cpp
 * @brief Implementation of the MainWindow class.
 */

#include "mainwindow.h"
#include "qthread.h"
#include "ui_mainwindow.h"
#include "codeeditor.h"
#include "crc32.h"
#include "crc32.h"

/**
 * @brief Constructor for MainWindow. Initializes user interface components and configures serial port settings.
 *
 * This constructor initializes the UI components, sets default values for the baud rate and other serial port settings,
 * populates the serial port combo box with available ports, and connects UI signals to their respective slots.
 *
 * @param parent Parent widget, typically nullptr for main windows.
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    serial(Serial::instance()),
    isConnected(false),
    isEnlarged(false),
    originalWidth(600),
    enlargedWidth(1150)
{
    ui->setupUi(this);


    auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &port : ports)
    {
        ui->select->addItem(port.portName());
    }

    auto baudRates = QSerialPortInfo::standardBaudRates();
    for (int rate : baudRates)
    {
        ui->Baudrate->addItem(QString::number(rate));
    }
    ui->Baudrate->setEditable(true);
    ui->Baudrate->setValidator(new QIntValidator(300, 4000000, this));
    ui->Baudrate->setCurrentText("115200");

    ui->databits->addItems({"5", "6", "7", "8"});
    ui->databits->setCurrentText("8");

    ui->bits->addItems({"1 Bit", "1.5 Bits", "2 Bits"});
    ui->paritySelect->addItems({"No Parity", "Even Parity", "Odd Parity", "Mark Parity", "Space Parity"});
    ui->flowControl->addItems({"No Flow Control", "Hardware Flow Control", "Software Flow Control"});

    connect(ui->Baudrate->lineEdit(), &QLineEdit::editingFinished, this, &MainWindow::updateBaudRate);
    connect(serial.port(), &QSerialPort::readyRead, this, &MainWindow::receiveMessage);
    connect(ui->pushButton_Rferesh, &QPushButton::clicked, this, &MainWindow::on_pushButton_Refresh_clicked);
    connect(ui->lineEdit_2, &QLineEdit::returnPressed, this, &MainWindow::on_pushButton_Send_clicked);

    timer = new QTimer(this);
    timer->start(1000);
    connect(timer, &QTimer::timeout, this, &MainWindow::on_pushButton_Refresh_clicked);
    connect(&serial, &Serial::serialError, this, &MainWindow::errorHandler);

    ui->pushButton_Connect->setCheckable(true);

    for(int i = 8; i <= 512; i *= 2)
    {
        ui->comboBox_packetsize->addItem(QString::number(i));
    }

    QTimer *statusTimer = new QTimer(this);
    connect(statusTimer, &QTimer::timeout, this, &MainWindow::checkDeviceStatus);
    statusTimer->start(1000);

    ui->lineEdit_2->setEnabled(false);
    ui->pushButton_Send->setEnabled(false);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenHeight = screenGeometry.height();

    this->resize(originalWidth, screenHeight - 100);
    this->setMaximumHeight(screenHeight - 100);

    QRect frameGeometry = this->frameGeometry();
    frameGeometry.moveCenter(screen->availableGeometry().center());
    this->move(frameGeometry.topLeft());
}

/**
 * @brief Destructor for MainWindow.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Updates the baud rate based on user input from the UI.
 *
 * This function retrieves the custom baud rate entered by the user in the baud rate combo box
 * and updates the serial port settings if the port is open.
 */
void MainWindow::updateBaudRate()
{
    int customBaudRate = ui->Baudrate->currentText().toInt();
    if (serial.port()->isOpen())
    {
        serial.port()->setBaudRate(customBaudRate);
    }
}

/**
 * @brief Handles connection and disconnection setup based on user-selected port and settings.
 *
 * This function retrieves the selected serial port name and user-specified settings (baud rate, data bits, stop bits, parity, flow control)
 * from the UI and uses them to open the serial port with the specified parameters.
 *
 * And disconnects the connected port with the second push
 *
 * And disables changing the selected parameters while connected
 *
 * @param checked Indicates whether the connect button is checked (true) or not (false).
 */

void MainWindow::on_pushButton_Connect_toggled(bool checked)
{
    if(checked == true) /* With first press */
    {
        QString portName = ui->select->currentText(); /*Gets the selected port name*/
        int baudRate = ui->Baudrate->currentText().toInt(); /*Gets the selected baud rate as integer*/

        QSerialPort::DataBits dataBits;
        int databitsNum = ui->databits->currentText().toInt(); /*Changes the data bit chosen to int*/
        if (databitsNum == 5) /*If data bit is 5*/
        {
            dataBits = QSerialPort::Data5; /*Initializes data bit as 5*/
        }
        else if (databitsNum == 6) /*If data bit is 6*/
        {
            dataBits = QSerialPort::Data6; /*Initializes data bit as 6*/
        }
        else if (databitsNum == 7) /*If data bit is 7*/
        {
            dataBits = QSerialPort::Data7; /*Initializes data bit as 7*/
        }
        else /*If data bit is 8*/
        {
            dataBits = QSerialPort::Data8; /*Initializes data bit as 8*/
        }

        QSerialPort::StopBits stopBits;
        QString stopbitText = ui->bits->currentText();
        if (stopbitText == "1 Bit")
        {
            stopBits = QSerialPort::OneStop;
        }
        else if (stopbitText == "1.5 Bits")
        {
            stopBits = QSerialPort::OneAndHalfStop;
        }
        else
        {
            stopBits = QSerialPort::TwoStop;
        }

        QSerialPort::Parity parity;
        QString parityText = ui->paritySelect->currentText();
        if (parityText == "No Parity")
        {
            parity = QSerialPort::NoParity;
        }
        else if (parityText == "Even Parity")
        {
            parity = QSerialPort::EvenParity;
        }
        else if (parityText == "Odd Parity")
        {
            parity = QSerialPort::OddParity;
        }
        else if (parityText == "Mark Parity")
        {
            parity = QSerialPort::MarkParity;
        }
        else
        {
            parity = QSerialPort::SpaceParity;
        }

        QSerialPort::FlowControl flowControl;
        QString flowcontrolText = ui->flowControl->currentText();
        if (flowcontrolText == "No Flow Control")
        {
            flowControl = QSerialPort::NoFlowControl;
        }
        else if (flowcontrolText == "Hardware Flow Control")
        {
            flowControl = QSerialPort::HardwareControl;
        }
        else
        {
            flowControl = QSerialPort::SoftwareControl;
        }

        QSerialPortInfo portInfo(portName);
        int vendorId = portInfo.hasVendorIdentifier() ? portInfo.vendorIdentifier() : 0;
        int productId = portInfo.hasProductIdentifier() ? portInfo.productIdentifier() : 0;

        SerialPortParameters params = {portName, baudRate, dataBits, parity, stopBits, flowControl, vendorId, productId};

        connectToDevice(params);

        if(serial.port()->isOpen())
        {
            ui->pushButton_Connect->setStyleSheet("background-color : green");  /*Changes the push button color to green after connection*/
            ui->pushButton_Connect->setText("Connected");

            lastConnectedParams = currentParams;
            currentParams = params;

            /*
             * Disables changing selected parameters after connection
             **/

            ui->Baudrate->setEnabled(false);
            ui->paritySelect->setEnabled(false);
            ui->select->setEnabled(false);
            ui->databits->setEnabled(false);
            ui->bits->setEnabled(false);
            ui->flowControl->setEnabled(false);

            ui->lineEdit_2->setEnabled(true);
            ui->pushButton_Send->setEnabled(true);

            qDebug() << "Connection happened";
        }
    }
    else /* With the second press */
    {
        if(serial.port()->isOpen())
        {
            ui->pushButton_Connect->setStyleSheet("background-color : red"); /*Shows the disconnection with turning button color to red */
            ui->pushButton_Connect->setText("Disconnected");

            qDebug() << "Disconnection happened";
        }
        serial.closePort();/* Closes the connection */

        /*
         * Enables changing selected parameters after disconnection
         * */
        ui->Baudrate->setEnabled(true);
        ui->paritySelect->setEnabled(true);
        ui->select->setEnabled(true);
        ui->databits->setEnabled(true);
        ui->bits->setEnabled(true);
        ui->flowControl->setEnabled(true);

        ui->lineEdit_2->setEnabled(false);
        ui->pushButton_Send->setEnabled(false);

        isConnected = false;
    }
}

/**
 * @brief Sends user-entered message to the connected device.
 *
 * This function retrieves the message entered by the user in the input field,
 * appends CR+LF if the corresponding checkbox is checked, and sends the message through the serial port.
 * It also appends a control-Z character if the corresponding checkbox is checked.
 */
void MainWindow::on_pushButton_Send_clicked()
{
    if(ui->checkBox_protocol->isChecked())
    {
        ProtocolMessage msg;
        msg.machineId = ui->lineEdit_MachinID->text().toInt();
        msg.customId = ui->lineEdit_CustomID->text().toInt();
        msg.messageSeqNum = ui->lineEdit_MessageSeq->text().toUInt();
        msg.messagePacketId = ui->lineEdit_MessagPacket->text().toInt();
        msg.commandType = ui->lineEdit_CommandT->text().toInt();
        msg.serviceCommandType = ui->lineEdit_ServiceComman->text().toInt();

        QByteArray messageData;
        messageData.append(reinterpret_cast<const char*>(&msg.machineId), sizeof(msg.machineId));
        messageData.append(reinterpret_cast<const char*>(&msg.customId), sizeof(msg.customId));
        messageData.append(reinterpret_cast<const char*>(&msg.messageSeqNum), sizeof(msg.messageSeqNum));
        messageData.append(reinterpret_cast<const char*>(&msg.messagePacketId), sizeof(msg.messagePacketId));
        messageData.append(reinterpret_cast<const char*>(&msg.commandType), sizeof(msg.commandType));
        messageData.append(reinterpret_cast<const char*>(&msg.serviceCommandType), sizeof(msg.serviceCommandType));

        QByteArray data = ui->lineEdit_2->text().toUtf8();
        msg.dataLength = data.size();
        messageData.append(reinterpret_cast<const char*>(&msg.dataLength), sizeof(msg.dataLength));
        messageData.append(data);

        if (ui->checkBox_Crc->isChecked())
        {
            msg.crc = getCRC32(data, msg.dataLength);
            qDebug() << "Calculated CRC: " << msg.crc;
            messageData.append(reinterpret_cast<const char*>(&msg.crc), sizeof(msg.crc));
        }

        qDebug() << "Final Message Data:" << messageData.toHex();

        if(ui->checkbox_r_n->isChecked())
        {
            messageData.append("/r/n");
        }

        serial.writeData(messageData);

        if (!ui->checkBox_Recived->isChecked())
        {
            ui->textBrowserlog->append("Sent: " + messageData.toHex());
        }

        if (ui->controlZCheckBox->isChecked())
        {
            serial.writeData("\x1A");
        }
    }
    else
    {
        QByteArray data = ui->lineEdit_2->text().toUtf8();

        if(ui->checkBox_Crc->isChecked())
        {
            uint32_t crc = getCRC32(data, static_cast<uint16_t>(data.size()));
            data.append(crc);
        }

        if(ui->checkbox_r_n->isChecked())
        {
            data.append("\r\n");
        }

        serial.writeData(data);

        if (!ui->checkBox_Recived->isChecked())
        {
            ui->textBrowserlog->append("Sent: " + data);
        }

        if (ui->controlZCheckBox->isChecked())
        {
            serial.writeData("\x1A");
        }
    }
}


/**
 * @brief Receives and displays data from the connected device.
 *
 * This function is triggered by the QSerialPort::readyRead signal and processes the data received from the serial port.
 * It appends the received data to the log display in the UI.
 */
void MainWindow::receiveMessage()
{
    QByteArray data = serial.readData();
    qDebug() << "Raw Data ByteArray:" << data.toUpper();
    qDebug() << "Raw Data Hex" << data.toHex().toUpper();

    if(!ui->checkBox_protocol->isChecked())
    {
        if (ui->checkBox_Crc->isChecked())
        {
            QByteArray messageData = data.left(data.size() - 4);
            QByteArray receivedCrcData = data.right(4);
            uint32_t receivedCrc;
            memcpy(&receivedCrc, receivedCrcData.constData(), sizeof(receivedCrc));

            uint32_t calculatedCrc = getCRC32(data, static_cast<uint16_t>(data.size()));
            messageData.append(calculatedCrc);

            if (ui->checkBox_Recived->isChecked())
            {
                ui->textBrowserlog->append(messageData.toHex());
            }
            else
            {
                ui->textBrowserlog->append("Received: " + QString::fromUtf8(messageData.toHex()));
            }
        }
        else
        {
            ui->textBrowserlog->append("Received: " + QString::fromUtf8(data));
        }
    }
    else
    {
        uint16_t machineId = 0;
        uint16_t customId = 0;
        uint32_t sequenceNumber = 0;
        uint16_t packetId = 0;
        uint16_t commandType = 0;
        uint8_t serviceCommandType = 0;
        uint16_t dataLength = 0;
        QByteArray dataPart;
        uint16_t errorCode = 0;
        uint32_t receivedCrc = 0;

        QDataStream stream(data);
        stream.setByteOrder(QDataStream::LittleEndian);

        stream >> machineId;
        stream >> customId;
        stream >> sequenceNumber;
        stream >> packetId;
        stream >> commandType;
        stream >> serviceCommandType;

        uint8_t dataLengthBytes[2];
        stream.readRawData(reinterpret_cast<char*>(dataLengthBytes), 2);
        dataLength = dataLengthBytes[0] | (dataLengthBytes[1] << 8);

        qDebug() << "Extracted Machine ID:" << QString::number(machineId, 16).toUpper();
        qDebug() << "Extracted Custom ID:" << QString::number(customId, 16).toUpper();
        qDebug() << "Extracted Sequence Number:" << QString::number(sequenceNumber, 16).toUpper();
        qDebug() << "Extracted Packet ID:" << QString::number(packetId, 16).toUpper();
        qDebug() << "Extracted Command Type:" << QString::number(commandType, 16).toUpper();
        qDebug() << "Extracted Service Command Type:" << QString::number(serviceCommandType, 16).toUpper();
        qDebug() << "Extracted Data Length Bytes:" << dataLengthBytes[0] << dataLengthBytes[1];
        qDebug() << "Extracted Data Length:" << dataLength;

        // Check if dataLength is valid
        int expectedSize = 14 + dataLength + 2 + 4; // 14 bytes of fixed fields + dataLength + 2 bytes error code + 4 bytes CRC
        if (data.size() < expectedSize)
        {
            qDebug() << "Received data length is inconsistent with the expected length";
            ui->textBrowserlog->append("Received data length is inconsistent with the expected length");
            return;
        }

        dataPart = data.mid(15, dataLength);
        stream.skipRawData(dataLength); // Skip the data part in the stream
        stream >> errorCode;
        stream >> receivedCrc;

        qDebug() << "Extracted Error Code:" << QString::number(errorCode, 16).toUpper();
        qDebug() << "Extracted Received CRC:" << QString::number(receivedCrc, 16).toUpper();

        qDebug() << "Data Part (Hex):" << dataPart.toHex().toUpper();
        qDebug() << "Data Part (Size):" << dataPart.size();
        qDebug() << "Data Part (Length for CRC):" << dataLength;

        QString logMessage;
        logMessage += QString("Machine ID: %1\n").arg(machineId, 4, 16, QChar('0')).toUpper();
        logMessage += QString("Custom ID: %1\n").arg(customId, 4, 16, QChar('0')).toUpper();
        logMessage += QString("Sequence Number: %1\n").arg(sequenceNumber, 8, 16, QChar('0')).toUpper();
        logMessage += QString("Packet ID: %1\n").arg(packetId, 4, 16, QChar('0')).toUpper();
        logMessage += QString("Command Type: %1\n").arg(commandType, 4, 16, QChar('0')).toUpper();
        logMessage += QString("Service Command Type: %1\n").arg(serviceCommandType, 2, 16, QChar('0')).toUpper();
        logMessage += QString("Data Length: %1\n").arg(dataLength);
        logMessage += "Data: " + dataPart.toHex().toUpper() + "\n";
        logMessage += QString("Error Code: %1\n").arg(errorCode, 4, 16, QChar('0')).toUpper();

        qDebug() << dataPart.toHex().toUpper();

        if (ui->checkBox_Crc->isChecked())
        {
            uint32_t calculatedCrc = getCRC32(dataPart, dataLength);
            qDebug() << "Calculated CRC:" << QString::number(calculatedCrc, 16).toUpper();
            qDebug() << "Received CRC:" << QString::number(receivedCrc, 16).toUpper();
            qDebug() << "Data Part (for CRC calculation):" << dataPart.toHex().toUpper();

            logMessage += "Received CRC: " + QString::number(receivedCrc, 16).toUpper() + "\n";
            logMessage += "Host CRC: " + QString::number(calculatedCrc, 16).toUpper() + "\n";
        }

        if (ui->checkBox_Recived->isChecked())
        {
            ui->textBrowserlog->append(logMessage);
        }
        else
        {
            ui->textBrowserlog->append("Received:\n" + logMessage);
        }

        qDebug() << logMessage;
    }
}



/**
 * @brief Clears the text display in the UI.
 *
 * This function is activated when the user clicks the 'Clear' button and clears the text output area in the user interface.
 */
void MainWindow::on_pushButton_Clear_clicked()
{
    ui->textBrowserlog->clear();
}

/**
 * @brief Refreshes and updates the list of available serial ports.
 *
 * This function is called when the 'Refresh' button is clicked, updating the list of serial ports displayed in the UI.
 */
void MainWindow::on_pushButton_Refresh_clicked()
{
    const QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    QStringList newPortNames;
    for (const QSerialPortInfo &port : ports)
    {
        newPortNames << port.portName();
    }

    if (newPortNames != currentPortNames)
    {
        currentPortNames = newPortNames;
        ui->select->clear();
        ui->select->addItems(currentPortNames);
    }

    bool lastDeviceFound = false;
    for (const QSerialPortInfo &port : ports)
    {
        if (port.hasVendorIdentifier() && port.vendorIdentifier() == lastConnectedParams.vendorId &&
            port.hasProductIdentifier() && port.productIdentifier() == lastConnectedParams.productId)
        {
            lastDeviceFound = true;
            break;
        }
    }

    isConnected = lastDeviceFound;
}

/**
 * @brief Handles serial port errors and displays an error message.
 *
 * This slot is connected to the Serial::serialError signal and displays the error message in a message box.
 * @param error The error message to display.
 */
void MainWindow::errorHandler(QString error)
{
    QMessageBox::critical(this, "Problem Occurred", error);

    if(serial.port()->isOpen())
    {
        ui->pushButton_Connect->setStyleSheet("background-color : red"); /*Shows the disconnection with turning button color to red */
        ui->pushButton_Connect->setText("Disconnected");

        qDebug() << "Disconnection happened";
    }
    serial.closePort();/* Closes the connection */

    ui->Baudrate->setEnabled(true);
    ui->paritySelect->setEnabled(true);
    ui->select->setEnabled(true);
    ui->databits->setEnabled(true);
    ui->bits->setEnabled(true);
    ui->flowControl->setEnabled(true);

    ui->lineEdit_2->setEnabled(false);
    ui->pushButton_Send->setEnabled(false);

    isConnected = false;
}

/**
 * @brief Refreshes the list of available serial ports and displays their information.
 *
 * This function logs detailed information about each available serial port when the 'Refresh' button is clicked.
 */
void MainWindow::on_pushButton_Rferesh_clicked()
{
    const QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &info : ports)
    {
        qDebug() << "Port Name:" << info.portName();
        qDebug() << "Description:" << info.description();
        qDebug() << "Manufacturer:" << info.manufacturer();

        if (info.hasVendorIdentifier())
        {
            qDebug() << "Vendor ID:" << QString::number(info.vendorIdentifier(), 16);
        }
        if (info.hasProductIdentifier())
        {
            qDebug() << "Product ID:" << QString::number(info.productIdentifier(), 16);
        }
        if (!info.serialNumber().isEmpty())
        {
            qDebug() << "Serial Number:" << info.serialNumber();
        }

        qDebug() << "-------------------";
    }

    bool lastDeviceFound = false;
    for (const QSerialPortInfo &port : ports)
    {
        if (port.hasVendorIdentifier() && port.vendorIdentifier() == lastConnectedParams.vendorId &&
            port.hasProductIdentifier() && port.productIdentifier() == lastConnectedParams.productId)
        {
            lastDeviceFound = true;
            break;
        }
    }

    isConnected = lastDeviceFound;
}

/**
 * @brief Opens a file dialog to select a file for import.
 *
 * This function opens a file dialog for the user to select a file to import, and updates the file name input field with the selected file.
 */
void MainWindow::on_pushButton_import_clicked()
{
    QString filter = "Binary files (*.bin);;HEX files (*.hex)";
    QString fileName = QFileDialog::getOpenFileName(this, "Import File", QDir::homePath(), filter);
    if (!fileName.isEmpty())
    {
        ui->lineEdit_filename->setText(fileName);
    }
}

/**
 * @brief Opens a file dialog to select a directory for exporting the log.
 *
 * This function provides options to export the log as a TXT or CSV file, and saves the file in the selected directory.
 */
void MainWindow::on_pushButton_export_clicked()
{
    QMenu menu;
    QAction* exportTxt = menu.addAction("Export as TXT");
    QAction* exportCsv = menu.addAction("Export as CSV");

    QAction* selectedAction = menu.exec(QCursor::pos());

    if (selectedAction)
    {
        QString extension = (selectedAction == exportTxt) ? "txt" : "csv";
        QString fileTypeName = (selectedAction == exportTxt) ? "Text files (*.txt)" : "CSV files (*.csv)";

        QString dir = QFileDialog::getExistingDirectory(this, "Select Directory to Save File");
        if (!dir.isEmpty())
        {
            QString filePath = QFileDialog::getSaveFileName(this, "Save File", dir, fileTypeName);

            if (!filePath.isEmpty())
            {
                QFile file(filePath);
                if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QTextStream out(&file);
                    out << ui->textBrowserlog->toPlainText();
                    file.close();
                    QMessageBox::information(this, "Export Success", "Successfully exported the log to " + filePath);
                }
                else
                {
                    QMessageBox::critical(this, "Error", "Could not open file for writing.");
                }
            }
        }
    }
}

/**
 * @brief Updates the data read from the selected file.
 *
 * This function reads data from the file specified in the file name input field, divides it into packets,
 * appends CRC if necessary, and sends the packets through the serial port.
 */

void MainWindow::on_pushButton_UpdateFile_clicked()
{
    QString filePath = ui->lineEdit_filename->text();
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Read Error", "Could not open the file for reading.");
        return;
    }

    int packetSize = ui->comboBox_packetsize->currentText().toInt();
    QByteArray packet;
    ProtocolMessage msg;

    msg.machineId = ui->lineEdit_MachinID->text().toInt();
    msg.customId = ui->lineEdit_CustomID->text().toInt();
    msg.messageSeqNum = ui->lineEdit_MessageSeq->text().toUInt(); // 4 byte
    msg.messagePacketId = ui->lineEdit_MessagPacket->text().toInt();
    msg.commandType = ui->lineEdit_CommandT->text().toInt();
    msg.serviceCommandType = ui->lineEdit_ServiceComman->text().toInt();

    while (!file.atEnd())
    {
        packet = file.read(packetSize);
        if (packet.isEmpty())
        {
            break;
        }

        QByteArray messageData;
        messageData.append(reinterpret_cast<const char*>(&msg.machineId), sizeof(msg.machineId));
        messageData.append(reinterpret_cast<const char*>(&msg.customId), sizeof(msg.customId));
        messageData.append(reinterpret_cast<const char*>(&msg.messageSeqNum), sizeof(msg.messageSeqNum)); // 4 byte
        messageData.append(reinterpret_cast<const char*>(&msg.messagePacketId), sizeof(msg.messagePacketId));
        messageData.append(reinterpret_cast<const char*>(&msg.commandType), sizeof(msg.commandType));
        messageData.append(reinterpret_cast<const char*>(&msg.serviceCommandType), sizeof(msg.serviceCommandType));
        msg.dataLength = packet.size();
        messageData.append(reinterpret_cast<const char*>(&msg.dataLength), sizeof(msg.dataLength));
        messageData.append(packet);

        if (ui->checkBox_Crc->isChecked())
        {
            msg.crc = getCRC32(packet, msg.dataLength);
            messageData.append(reinterpret_cast<const char*>(&msg.crc), sizeof(msg.crc));
        }

        serial.writeData(messageData);
        QThread::msleep(50);
    }
    file.close();
}

/**
 * @brief Reads data from the selected file and displays it in packets.
 *
 * This function reads data from the file specified in the file name input field, divides it into packets, and displays the packets in the log.
 */
void MainWindow::on_pushButton_ReadFile_clicked()
{
    QString filePath = ui->lineEdit_filename->text();
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this, "Read Error", "Could not open the file for reading.");
        return;
    }

    int packetSize = ui->comboBox_packetsize->currentText().toInt();
    QByteArray packet;
    int packetCounter = 0;

    ProtocolMessage msg;

    msg.machineId = ui->lineEdit_MachinID->text().toInt();
    msg.customId = ui->lineEdit_CustomID->text().toInt();
    msg.messageSeqNum = ui->lineEdit_MessageSeq->text().toUInt();
    msg.messagePacketId = ui->lineEdit_MessagPacket->text().toInt();
    msg.commandType = ui->lineEdit_CommandT->text().toInt();
    msg.serviceCommandType = ui->lineEdit_ServiceComman->text().toInt();

    qDebug() << "File Path:" << filePath;
    qDebug() << "Packet Size:" << packetSize;
    qDebug() << "Machine ID:" << msg.machineId;
    qDebug() << "Custom ID:" << msg.customId;
    qDebug() << "Message Sequence Number:" << msg.messageSeqNum;
    qDebug() << "Message Packet ID:" << msg.messagePacketId;
    qDebug() << "Command Type:" << msg.commandType;
    qDebug() << "Service Command Type:" << msg.serviceCommandType;

    while (!file.atEnd())
    {
        packet = file.read(packetSize);
        if (packet.isEmpty())
        {
            break;
        }

        QByteArray messageData;
        messageData.append(reinterpret_cast<const char*>(&msg.machineId), sizeof(msg.machineId));
        messageData.append(reinterpret_cast<const char*>(&msg.customId), sizeof(msg.customId));
        messageData.append(reinterpret_cast<const char*>(&msg.messageSeqNum), sizeof(msg.messageSeqNum)); // 4 byte
        messageData.append(reinterpret_cast<const char*>(&msg.messagePacketId), sizeof(msg.messagePacketId));
        messageData.append(reinterpret_cast<const char*>(&msg.commandType), sizeof(msg.commandType));
        messageData.append(reinterpret_cast<const char*>(&msg.serviceCommandType), sizeof(msg.serviceCommandType));
        msg.dataLength = packet.size();
        messageData.append(reinterpret_cast<const char*>(&msg.dataLength), sizeof(msg.dataLength));
        messageData.append(packet);

        uint32_t crc = 0;
        if (ui->checkBox_Crc->isChecked())
        {
            crc = getCRC32(packet, msg.dataLength);
            messageData.append(reinterpret_cast<const char*>(&crc), sizeof(crc));
        }

        QString formattedString = QString("Packet #%1:\n Machine ID: %2\n Custom ID: %3\n Message Seq Num: %4\n Message Packet ID: %5\n Command Type: %6\n Service Command Type: %7\n Data: 0x%8\n Size: %9 bytes\n CRC: %10")
                                      .arg(QString::number(packetCounter + 1))
                                      .arg(msg.machineId)
                                      .arg(msg.customId)
                                      .arg(msg.messageSeqNum)
                                      .arg(msg.messagePacketId)
                                      .arg(msg.commandType)
                                      .arg(msg.serviceCommandType)
                                      .arg(QString(packet.toHex(' ')))
                                      .arg(QString::number(packet.size()))
                                      .arg(QString::number(crc, 16));

        ui->textBrowserlog->append(formattedString);

        qDebug() << formattedString;
        QApplication::processEvents();
        QThread::msleep(50);
        packetCounter++;
    }
    file.close();
}


/**
 * @brief Connects to the device with the specified serial port parameters.
 *
 * This function attempts to open the serial port with the given parameters and updates the UI accordingly.
 *
 * @param params The serial port parameters to use for the connection.
 */
void MainWindow::connectToDevice(const SerialPortParameters &params)
{
    if (serial.port()->isOpen())
    {
        serial.closePort();
    }

    serial.port()->setPortName(params.portName);
    serial.port()->setBaudRate(params.baudRate);
    serial.port()->setDataBits(params.dataBits);
    serial.port()->setParity(params.parity);
    serial.port()->setStopBits(params.stopBits);
    serial.port()->setFlowControl(params.flowControl);

    serial.openPort(params.portName, params.baudRate, params.dataBits, params.parity, params.stopBits, params.flowControl);

    if (serial.port()->isOpen())
    {
        isConnected = true;
        currentParams = params;
        qDebug() << "Connected to device: " << params.portName;

        ui->pushButton_Connect->setStyleSheet("background-color : green");
        ui->pushButton_Connect->setText("Connected");

        lastConnectedParams = currentParams;
        currentParams = params;

        ui->Baudrate->setEnabled(false);
        ui->paritySelect->setEnabled(false);
        ui->select->setEnabled(false);
        ui->databits->setEnabled(false);
        ui->bits->setEnabled(false);
        ui->flowControl->setEnabled(false);

        ui->lineEdit_2->setEnabled(true);
        ui->pushButton_Send->setEnabled(true);

        // Reset flags when a new device is connected
        reconnectMessageBoxShown = false;
        devicePreviouslyConnected = true;
    }
    else
    {
        QMessageBox::critical(this, "Error", "Failed to open the serial port.");
    }
}

void MainWindow::reconnectDevice()
{
    qDebug() << "Reconnecting to device...";
    connectToDevice(currentParams);
}

bool MainWindow::isSameDevice(const SerialPortParameters &params)
{
    return (currentParams.vendorId == params.vendorId && currentParams.productId == params.productId);
}

void MainWindow::showReconnectMessageBox()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Reconnect", "Do you want to reconnect the device?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        reconnectDevice();
    }
}

void MainWindow::checkDeviceStatus()
{
    if (serial.port()->isOpen() == false && isConnected == true)
    {
        if (isSameDevice(currentParams))
        {
            qDebug() << "Connection lost. Prompting user for reconnection.";
            isConnected = false;

            // Check if the message box has already been shown
            if (!reconnectMessageBoxShown)
            {
                showReconnectMessageBox();
                reconnectMessageBoxShown = true;  // Set flag to true after showing the message box
            }
        }
    }
    else if (serial.port()->isOpen() == true)
    {
        // Device is connected
        if (!devicePreviouslyConnected)
        {
            // A new device is connected
            devicePreviouslyConnected = true;
            reconnectMessageBoxShown = false;  // Reset the flag for new device connections
        }
    }
    else
    {
        // Device was previously connected but now is not
        devicePreviouslyConnected = false;
    }
}



void MainWindow::on_pushButton_enlarge_clicked()
{
    if (isEnlarged)
    {
        this->resize(originalWidth, this->height());
    }
    else
    {
        this->resize(enlargedWidth, this->height());
    }
    isEnlarged = !isEnlarged;

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect frameGeometry = this->frameGeometry();
    frameGeometry.moveCenter(screen->availableGeometry().center());
    this->move(frameGeometry.topLeft());
}

