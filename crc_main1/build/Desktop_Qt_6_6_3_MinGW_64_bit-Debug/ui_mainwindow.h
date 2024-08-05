/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "codeeditor.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    CodeEditor *textBrowserlog;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QFrame *line_4;
    QLabel *label_4;
    QFrame *line_10;
    QLabel *label_6;
    QFrame *line_14;
    QVBoxLayout *verticalLayout_4;
    QComboBox *select;
    QFrame *line_9;
    QComboBox *databits;
    QFrame *line_11;
    QComboBox *paritySelect;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QFrame *line_2;
    QLabel *label_5;
    QFrame *line_3;
    QLabel *label_7;
    QFrame *line_7;
    QVBoxLayout *verticalLayout_5;
    QComboBox *Baudrate;
    QFrame *line;
    QComboBox *bits;
    QFrame *line_5;
    QComboBox *flowControl;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_Connect;
    QPushButton *pushButton_Rferesh;
    QSpacerItem *horizontalSpacer;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_8;
    QLineEdit *lineEdit;
    QFrame *line_16;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_Clear;
    QFrame *line_6;
    QCheckBox *checkBox_Recived;
    QFrame *line_8;
    QCheckBox *controlZCheckBox;
    QFrame *line_12;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkbox_r_n;
    QLabel *label_14;
    QFrame *line_13;
    QCheckBox *checkBox_Crc;
    QFrame *line_15;
    QCheckBox *checkBox_protocol;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButton_Send;
    QFrame *line_17;
    QPushButton *pushButton_enlarge;
    QStackedWidget *stackedWidget;
    QWidget *page_6;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_filename;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_import;
    QPushButton *pushButton_export;
    QPushButton *pushButton_ReadFile;
    QFrame *line_31;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_6;
    QPushButton *pushButton_UpdateFile;
    QFrame *line_30;
    QLabel *label_3;
    QFrame *line_29;
    QLabel *label_9;
    QFrame *line_28;
    QLabel *label_10;
    QFrame *line_27;
    QLabel *label_11;
    QFrame *line_26;
    QLabel *label_12;
    QFrame *line_25;
    QLabel *label_13;
    QFrame *line_18;
    QVBoxLayout *verticalLayout_7;
    QComboBox *comboBox_packetsize;
    QFrame *line_24;
    QLineEdit *lineEdit_MachinID;
    QFrame *line_23;
    QLineEdit *lineEdit_CustomID;
    QFrame *line_22;
    QLineEdit *lineEdit_MessageSeq;
    QFrame *line_21;
    QLineEdit *lineEdit_MessagPacket;
    QFrame *line_20;
    QLineEdit *lineEdit_CommandT;
    QFrame *line_19;
    QLineEdit *lineEdit_ServiceComman;
    QSpacerItem *verticalSpacer;
    QWidget *page_7;
    QMenuBar *MenuBar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1636, 778);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/logos/image/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName("gridLayout_2");
        textBrowserlog = new CodeEditor(centralwidget);
        textBrowserlog->setObjectName("textBrowserlog");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(111);
        sizePolicy.setVerticalStretch(111);
        sizePolicy.setHeightForWidth(textBrowserlog->sizePolicy().hasHeightForWidth());
        textBrowserlog->setSizePolicy(sizePolicy);
        textBrowserlog->setMaximumSize(QSize(800, 2500));
        textBrowserlog->setSizeIncrement(QSize(111, 111));
        textBrowserlog->setBaseSize(QSize(100, 100));
        textBrowserlog->setToolTipDuration(-1);
        textBrowserlog->setFrameShape(QFrame::StyledPanel);
        textBrowserlog->setFrameShadow(QFrame::Raised);

        gridLayout_2->addWidget(textBrowserlog, 1, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        line_4 = new QFrame(centralwidget);
        line_4->setObjectName("line_4");
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_4);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        verticalLayout_2->addWidget(label_4);

        line_10 = new QFrame(centralwidget);
        line_10->setObjectName("line_10");
        line_10->setFrameShape(QFrame::HLine);
        line_10->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_10);

        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");

        verticalLayout_2->addWidget(label_6);


        horizontalLayout_7->addLayout(verticalLayout_2);

        line_14 = new QFrame(centralwidget);
        line_14->setObjectName("line_14");
        line_14->setFrameShape(QFrame::VLine);
        line_14->setFrameShadow(QFrame::Sunken);

        horizontalLayout_7->addWidget(line_14);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        select = new QComboBox(centralwidget);
        select->setObjectName("select");

        verticalLayout_4->addWidget(select);

        line_9 = new QFrame(centralwidget);
        line_9->setObjectName("line_9");
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_9);

        databits = new QComboBox(centralwidget);
        databits->setObjectName("databits");

        verticalLayout_4->addWidget(databits);

        line_11 = new QFrame(centralwidget);
        line_11->setObjectName("line_11");
        line_11->setFrameShape(QFrame::HLine);
        line_11->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_11);

        paritySelect = new QComboBox(centralwidget);
        paritySelect->setObjectName("paritySelect");

        verticalLayout_4->addWidget(paritySelect);


        horizontalLayout_7->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        verticalLayout_3->addWidget(label_2);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_2);

        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        verticalLayout_3->addWidget(label_5);

        line_3 = new QFrame(centralwidget);
        line_3->setObjectName("line_3");
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_3);

        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");

        verticalLayout_3->addWidget(label_7);


        horizontalLayout_7->addLayout(verticalLayout_3);

        line_7 = new QFrame(centralwidget);
        line_7->setObjectName("line_7");
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);

        horizontalLayout_7->addWidget(line_7);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        Baudrate = new QComboBox(centralwidget);
        Baudrate->setObjectName("Baudrate");
        Baudrate->setEditable(false);

        verticalLayout_5->addWidget(Baudrate);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line);

        bits = new QComboBox(centralwidget);
        bits->setObjectName("bits");

        verticalLayout_5->addWidget(bits);

        line_5 = new QFrame(centralwidget);
        line_5->setObjectName("line_5");
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line_5);

        flowControl = new QComboBox(centralwidget);
        flowControl->setObjectName("flowControl");

        verticalLayout_5->addWidget(flowControl);


        horizontalLayout_7->addLayout(verticalLayout_5);


        gridLayout_2->addLayout(horizontalLayout_7, 5, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_5);

        pushButton_Connect = new QPushButton(centralwidget);
        pushButton_Connect->setObjectName("pushButton_Connect");

        horizontalLayout_9->addWidget(pushButton_Connect);

        pushButton_Rferesh = new QPushButton(centralwidget);
        pushButton_Rferesh->setObjectName("pushButton_Rferesh");

        horizontalLayout_9->addWidget(pushButton_Rferesh);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);


        gridLayout_2->addLayout(horizontalLayout_9, 8, 0, 1, 1);

        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");

        gridLayout_2->addWidget(lineEdit_2, 2, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");

        horizontalLayout_11->addWidget(label_8);

        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_11->addWidget(lineEdit);


        gridLayout_2->addLayout(horizontalLayout_11, 6, 0, 1, 1);

        line_16 = new QFrame(centralwidget);
        line_16->setObjectName("line_16");
        line_16->setFrameShape(QFrame::HLine);
        line_16->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_16, 4, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_Clear = new QPushButton(centralwidget);
        pushButton_Clear->setObjectName("pushButton_Clear");

        horizontalLayout_3->addWidget(pushButton_Clear);

        line_6 = new QFrame(centralwidget);
        line_6->setObjectName("line_6");
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_6);

        checkBox_Recived = new QCheckBox(centralwidget);
        checkBox_Recived->setObjectName("checkBox_Recived");

        horizontalLayout_3->addWidget(checkBox_Recived);

        line_8 = new QFrame(centralwidget);
        line_8->setObjectName("line_8");
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_8);

        controlZCheckBox = new QCheckBox(centralwidget);
        controlZCheckBox->setObjectName("controlZCheckBox");

        horizontalLayout_3->addWidget(controlZCheckBox);

        line_12 = new QFrame(centralwidget);
        line_12->setObjectName("line_12");
        line_12->setFrameShape(QFrame::VLine);
        line_12->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_12);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        checkbox_r_n = new QCheckBox(centralwidget);
        checkbox_r_n->setObjectName("checkbox_r_n");

        horizontalLayout_4->addWidget(checkbox_r_n);

        label_14 = new QLabel(centralwidget);
        label_14->setObjectName("label_14");

        horizontalLayout_4->addWidget(label_14);


        horizontalLayout_3->addLayout(horizontalLayout_4);

        line_13 = new QFrame(centralwidget);
        line_13->setObjectName("line_13");
        line_13->setFrameShape(QFrame::VLine);
        line_13->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_13);

        checkBox_Crc = new QCheckBox(centralwidget);
        checkBox_Crc->setObjectName("checkBox_Crc");

        horizontalLayout_3->addWidget(checkBox_Crc);

        line_15 = new QFrame(centralwidget);
        line_15->setObjectName("line_15");
        line_15->setFrameShape(QFrame::VLine);
        line_15->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line_15);

        checkBox_protocol = new QCheckBox(centralwidget);
        checkBox_protocol->setObjectName("checkBox_protocol");

        horizontalLayout_3->addWidget(checkBox_protocol);


        gridLayout_2->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");

        gridLayout_2->addLayout(horizontalLayout_10, 9, 0, 1, 1);

        pushButton_Send = new QPushButton(centralwidget);
        pushButton_Send->setObjectName("pushButton_Send");

        gridLayout_2->addWidget(pushButton_Send, 3, 0, 1, 1);

        line_17 = new QFrame(centralwidget);
        line_17->setObjectName("line_17");
        line_17->setFrameShape(QFrame::HLine);
        line_17->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_17, 7, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 0, 0, 1, 1);

        pushButton_enlarge = new QPushButton(centralwidget);
        pushButton_enlarge->setObjectName("pushButton_enlarge");
        pushButton_enlarge->setMaximumSize(QSize(25, 25));

        gridLayout->addWidget(pushButton_enlarge, 0, 1, 1, 1);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        page_6 = new QWidget();
        page_6->setObjectName("page_6");
        verticalLayoutWidget_4 = new QWidget(page_6);
        verticalLayoutWidget_4->setObjectName("verticalLayoutWidget_4");
        verticalLayoutWidget_4->setGeometry(QRect(20, 0, 493, 701));
        verticalLayout_8 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        lineEdit_filename = new QLineEdit(verticalLayoutWidget_4);
        lineEdit_filename->setObjectName("lineEdit_filename");

        verticalLayout->addWidget(lineEdit_filename);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_import = new QPushButton(verticalLayoutWidget_4);
        pushButton_import->setObjectName("pushButton_import");

        horizontalLayout->addWidget(pushButton_import);

        pushButton_export = new QPushButton(verticalLayoutWidget_4);
        pushButton_export->setObjectName("pushButton_export");

        horizontalLayout->addWidget(pushButton_export);


        verticalLayout->addLayout(horizontalLayout);

        pushButton_ReadFile = new QPushButton(verticalLayoutWidget_4);
        pushButton_ReadFile->setObjectName("pushButton_ReadFile");

        verticalLayout->addWidget(pushButton_ReadFile);

        line_31 = new QFrame(verticalLayoutWidget_4);
        line_31->setObjectName("line_31");
        line_31->setFrameShape(QFrame::HLine);
        line_31->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_31);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        pushButton_UpdateFile = new QPushButton(verticalLayoutWidget_4);
        pushButton_UpdateFile->setObjectName("pushButton_UpdateFile");

        verticalLayout_6->addWidget(pushButton_UpdateFile);

        line_30 = new QFrame(verticalLayoutWidget_4);
        line_30->setObjectName("line_30");
        line_30->setFrameShape(QFrame::HLine);
        line_30->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_30);

        label_3 = new QLabel(verticalLayoutWidget_4);
        label_3->setObjectName("label_3");

        verticalLayout_6->addWidget(label_3);

        line_29 = new QFrame(verticalLayoutWidget_4);
        line_29->setObjectName("line_29");
        line_29->setFrameShape(QFrame::HLine);
        line_29->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_29);

        label_9 = new QLabel(verticalLayoutWidget_4);
        label_9->setObjectName("label_9");

        verticalLayout_6->addWidget(label_9);

        line_28 = new QFrame(verticalLayoutWidget_4);
        line_28->setObjectName("line_28");
        line_28->setFrameShape(QFrame::HLine);
        line_28->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_28);

        label_10 = new QLabel(verticalLayoutWidget_4);
        label_10->setObjectName("label_10");

        verticalLayout_6->addWidget(label_10);

        line_27 = new QFrame(verticalLayoutWidget_4);
        line_27->setObjectName("line_27");
        line_27->setFrameShape(QFrame::HLine);
        line_27->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_27);

        label_11 = new QLabel(verticalLayoutWidget_4);
        label_11->setObjectName("label_11");

        verticalLayout_6->addWidget(label_11);

        line_26 = new QFrame(verticalLayoutWidget_4);
        line_26->setObjectName("line_26");
        line_26->setFrameShape(QFrame::HLine);
        line_26->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_26);

        label_12 = new QLabel(verticalLayoutWidget_4);
        label_12->setObjectName("label_12");

        verticalLayout_6->addWidget(label_12);

        line_25 = new QFrame(verticalLayoutWidget_4);
        line_25->setObjectName("line_25");
        line_25->setFrameShape(QFrame::HLine);
        line_25->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_25);

        label_13 = new QLabel(verticalLayoutWidget_4);
        label_13->setObjectName("label_13");

        verticalLayout_6->addWidget(label_13);


        horizontalLayout_2->addLayout(verticalLayout_6);

        line_18 = new QFrame(verticalLayoutWidget_4);
        line_18->setObjectName("line_18");
        line_18->setFrameShape(QFrame::VLine);
        line_18->setFrameShadow(QFrame::Sunken);

        horizontalLayout_2->addWidget(line_18);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        comboBox_packetsize = new QComboBox(verticalLayoutWidget_4);
        comboBox_packetsize->setObjectName("comboBox_packetsize");
        comboBox_packetsize->setEditable(true);

        verticalLayout_7->addWidget(comboBox_packetsize);

        line_24 = new QFrame(verticalLayoutWidget_4);
        line_24->setObjectName("line_24");
        line_24->setFrameShape(QFrame::HLine);
        line_24->setFrameShadow(QFrame::Sunken);

        verticalLayout_7->addWidget(line_24);

        lineEdit_MachinID = new QLineEdit(verticalLayoutWidget_4);
        lineEdit_MachinID->setObjectName("lineEdit_MachinID");

        verticalLayout_7->addWidget(lineEdit_MachinID);

        line_23 = new QFrame(verticalLayoutWidget_4);
        line_23->setObjectName("line_23");
        line_23->setFrameShape(QFrame::HLine);
        line_23->setFrameShadow(QFrame::Sunken);

        verticalLayout_7->addWidget(line_23);

        lineEdit_CustomID = new QLineEdit(verticalLayoutWidget_4);
        lineEdit_CustomID->setObjectName("lineEdit_CustomID");

        verticalLayout_7->addWidget(lineEdit_CustomID);

        line_22 = new QFrame(verticalLayoutWidget_4);
        line_22->setObjectName("line_22");
        line_22->setFrameShape(QFrame::HLine);
        line_22->setFrameShadow(QFrame::Sunken);

        verticalLayout_7->addWidget(line_22);

        lineEdit_MessageSeq = new QLineEdit(verticalLayoutWidget_4);
        lineEdit_MessageSeq->setObjectName("lineEdit_MessageSeq");

        verticalLayout_7->addWidget(lineEdit_MessageSeq);

        line_21 = new QFrame(verticalLayoutWidget_4);
        line_21->setObjectName("line_21");
        line_21->setFrameShape(QFrame::HLine);
        line_21->setFrameShadow(QFrame::Sunken);

        verticalLayout_7->addWidget(line_21);

        lineEdit_MessagPacket = new QLineEdit(verticalLayoutWidget_4);
        lineEdit_MessagPacket->setObjectName("lineEdit_MessagPacket");

        verticalLayout_7->addWidget(lineEdit_MessagPacket);

        line_20 = new QFrame(verticalLayoutWidget_4);
        line_20->setObjectName("line_20");
        line_20->setFrameShape(QFrame::HLine);
        line_20->setFrameShadow(QFrame::Sunken);

        verticalLayout_7->addWidget(line_20);

        lineEdit_CommandT = new QLineEdit(verticalLayoutWidget_4);
        lineEdit_CommandT->setObjectName("lineEdit_CommandT");

        verticalLayout_7->addWidget(lineEdit_CommandT);

        line_19 = new QFrame(verticalLayoutWidget_4);
        line_19->setObjectName("line_19");
        line_19->setFrameShape(QFrame::HLine);
        line_19->setFrameShadow(QFrame::Sunken);

        verticalLayout_7->addWidget(line_19);

        lineEdit_ServiceComman = new QLineEdit(verticalLayoutWidget_4);
        lineEdit_ServiceComman->setObjectName("lineEdit_ServiceComman");

        verticalLayout_7->addWidget(lineEdit_ServiceComman);


        horizontalLayout_2->addLayout(verticalLayout_7);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_8->addLayout(verticalLayout);

        stackedWidget->addWidget(page_6);
        page_7 = new QWidget();
        page_7->setObjectName("page_7");
        stackedWidget->addWidget(page_7);

        gridLayout->addWidget(stackedWidget, 0, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        MenuBar = new QMenuBar(MainWindow);
        MenuBar->setObjectName("MenuBar");
        MenuBar->setGeometry(QRect(0, 0, 1636, 25));
        MainWindow->setMenuBar(MenuBar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Whiloader_CA Beta", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Ports", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Data Bits", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Parity", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Baud Rate", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Stop Bits", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Flow Control", nullptr));
        pushButton_Connect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        pushButton_Rferesh->setText(QCoreApplication::translate("MainWindow", "Refresh Ports", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Code", nullptr));
        pushButton_Clear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        checkBox_Recived->setText(QCoreApplication::translate("MainWindow", "Only Recived", nullptr));
        controlZCheckBox->setText(QCoreApplication::translate("MainWindow", "Ctrl +Z", nullptr));
        checkbox_r_n->setText(QString());
        label_14->setText(QCoreApplication::translate("MainWindow", "Send With \\r\\n", nullptr));
        checkBox_Crc->setText(QCoreApplication::translate("MainWindow", "CRC", nullptr));
        checkBox_protocol->setText(QCoreApplication::translate("MainWindow", "Whilone Protocol", nullptr));
        pushButton_Send->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        pushButton_enlarge->setText(QCoreApplication::translate("MainWindow", "<>", nullptr));
        pushButton_import->setText(QCoreApplication::translate("MainWindow", "Import File", nullptr));
        pushButton_export->setText(QCoreApplication::translate("MainWindow", "Export File", nullptr));
        pushButton_ReadFile->setText(QCoreApplication::translate("MainWindow", "Read File", nullptr));
        pushButton_UpdateFile->setText(QCoreApplication::translate("MainWindow", "Update", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Machine ID", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Custom ID", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Message Sequence Number ", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Message Packet ID", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Command Type ", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Service Command Type", nullptr));
        comboBox_packetsize->setCurrentText(QCoreApplication::translate("MainWindow", "Packet Size", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
