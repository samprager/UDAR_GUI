/********************************************************************************
** Form generated from reading UI file 'udar_controller.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UDAR_CONTROLLER_H
#define UI_UDAR_CONTROLLER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "../../qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_UDAR_Controller
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QLabel *label_6;
    QLabel *label_8;
    QLabel *label_9;
    QSpinBox *adcSamples_spinBox;
    QDoubleSpinBox *minFreq_dSpinBox;
    QDoubleSpinBox *chirpPRF_dSpinBox;
    QLabel *label_7;
    QDoubleSpinBox *chirpSlope_dSpinBox;
    QLabel *label_13;
    QDoubleSpinBox *chirpTime_dSpinBox;
    QDoubleSpinBox *chirpBW_dSpinBox;
    QLabel *label_12;
    QLabel *label_14;
    QDoubleSpinBox *clockFreq_dSpinBox;
    QLabel *label_15;
    QSpinBox *numSamples_spinBox;
    QSpinBox *phaseAccLen_spinBox;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QSpinBox *freqOffset_spinBox;
    QSpinBox *chirpTuningWord_spinBox;
    QPushButton *chirpParamsGenButton;
    QPushButton *chirpParamsResetButton;
    QWidget *tab_4;
    QTabWidget *tabWidget_2;
    QWidget *tab_5;
    QTextEdit *transcript;
    QPushButton *getThreadStatus;
    QPushButton *killThread;
    QPushButton *testButton;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *addressText;
    QLineEdit *valueWriteText;
    QPushButton *printExtBuf;
    QCheckBox *promiscModeCheckBox;
    QWidget *tab_7;
    QCustomPlot *plotI;
    QScrollBar *verticalScrollBarQ;
    QScrollBar *horizontalScrollBarQ;
    QWidget *tab_6;
    QCustomPlot *plotQ;
    QScrollBar *verticalScrollBarI;
    QScrollBar *horizontalScrollBarI;
    QWidget *tab_8;
    QCustomPlot *plotC;
    QScrollBar *verticalScrollBarC;
    QScrollBar *horizontalScrollBarC;
    QTabWidget *tabWidget_1;
    QWidget *tab;
    QLineEdit *srcMacAddr;
    QLabel *label_2;
    QLineEdit *srcIpAddr;
    QLineEdit *destIpAddr;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_3;
    QLineEdit *destMacAddr;
    QLabel *label_5;
    QPushButton *writeButton;
    QPushButton *readButton;
    QCheckBox *byteReorderCheckBox;
    QComboBox *networkInterfaces;
    QCheckBox *pktRecordCheckBox;
    QLabel *label_22;
    QLineEdit *recOutputDirectory;
    QLabel *label_23;
    QLineEdit *recOutputFilename;
    QWidget *tab_13;
    QLineEdit *inputPcapFilename;
    QLineEdit *outputPcapFilename;
    QLineEdit *outputDirectory;
    QPushButton *readPcapButton;
    QLabel *label_19;
    QLabel *label_21;
    QLabel *label_20;
    QWidget *tab_14;
    QMenuBar *menuBar;
    QMenu *menuUDAR_GUI;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *UDAR_Controller)
    {
        if (UDAR_Controller->objectName().isEmpty())
            UDAR_Controller->setObjectName(QStringLiteral("UDAR_Controller"));
        UDAR_Controller->resize(853, 748);
        UDAR_Controller->setStyleSheet(QStringLiteral("font: 10pt \".SF NS Text\";"));
        centralWidget = new QWidget(UDAR_Controller);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 831, 691));
        tabWidget = new QTabWidget(groupBox);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 20, 831, 191));
        tab_1 = new QWidget();
        tab_1->setObjectName(QStringLiteral("tab_1"));
        label_6 = new QLabel(tab_1);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(350, 10, 81, 16));
        label_8 = new QLabel(tab_1);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(560, 10, 101, 16));
        label_9 = new QLabel(tab_1);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(350, 60, 111, 16));
        adcSamples_spinBox = new QSpinBox(tab_1);
        adcSamples_spinBox->setObjectName(QStringLiteral("adcSamples_spinBox"));
        adcSamples_spinBox->setGeometry(QRect(360, 80, 91, 24));
        adcSamples_spinBox->setMaximum(999999);
        adcSamples_spinBox->setValue(200);
        minFreq_dSpinBox = new QDoubleSpinBox(tab_1);
        minFreq_dSpinBox->setObjectName(QStringLiteral("minFreq_dSpinBox"));
        minFreq_dSpinBox->setGeometry(QRect(560, 30, 101, 24));
        minFreq_dSpinBox->setDecimals(6);
        minFreq_dSpinBox->setMaximum(1e+6);
        minFreq_dSpinBox->setValue(5);
        chirpPRF_dSpinBox = new QDoubleSpinBox(tab_1);
        chirpPRF_dSpinBox->setObjectName(QStringLiteral("chirpPRF_dSpinBox"));
        chirpPRF_dSpinBox->setGeometry(QRect(350, 30, 111, 24));
        chirpPRF_dSpinBox->setDecimals(6);
        chirpPRF_dSpinBox->setMaximum(1e+6);
        chirpPRF_dSpinBox->setValue(10);
        label_7 = new QLabel(tab_1);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(680, 10, 111, 16));
        chirpSlope_dSpinBox = new QDoubleSpinBox(tab_1);
        chirpSlope_dSpinBox->setObjectName(QStringLiteral("chirpSlope_dSpinBox"));
        chirpSlope_dSpinBox->setGeometry(QRect(690, 30, 91, 24));
        chirpSlope_dSpinBox->setDecimals(6);
        chirpSlope_dSpinBox->setMaximum(1e+9);
        chirpSlope_dSpinBox->setValue(10);
        label_13 = new QLabel(tab_1);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(700, 60, 81, 16));
        chirpTime_dSpinBox = new QDoubleSpinBox(tab_1);
        chirpTime_dSpinBox->setObjectName(QStringLiteral("chirpTime_dSpinBox"));
        chirpTime_dSpinBox->setGeometry(QRect(700, 80, 81, 24));
        chirpTime_dSpinBox->setDecimals(3);
        chirpTime_dSpinBox->setMaximum(1e+9);
        chirpTime_dSpinBox->setValue(5);
        chirpBW_dSpinBox = new QDoubleSpinBox(tab_1);
        chirpBW_dSpinBox->setObjectName(QStringLiteral("chirpBW_dSpinBox"));
        chirpBW_dSpinBox->setGeometry(QRect(560, 80, 101, 24));
        chirpBW_dSpinBox->setDecimals(6);
        chirpBW_dSpinBox->setMaximum(1e+6);
        chirpBW_dSpinBox->setValue(50);
        label_12 = new QLabel(tab_1);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(560, 60, 101, 16));
        label_14 = new QLabel(tab_1);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(140, 60, 91, 16));
        clockFreq_dSpinBox = new QDoubleSpinBox(tab_1);
        clockFreq_dSpinBox->setObjectName(QStringLiteral("clockFreq_dSpinBox"));
        clockFreq_dSpinBox->setGeometry(QRect(60, 30, 81, 24));
        clockFreq_dSpinBox->setReadOnly(false);
        clockFreq_dSpinBox->setDecimals(3);
        clockFreq_dSpinBox->setMaximum(1000);
        clockFreq_dSpinBox->setValue(491.52);
        label_15 = new QLabel(tab_1);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(250, 60, 81, 16));
        numSamples_spinBox = new QSpinBox(tab_1);
        numSamples_spinBox->setObjectName(QStringLiteral("numSamples_spinBox"));
        numSamples_spinBox->setGeometry(QRect(260, 80, 71, 24));
        numSamples_spinBox->setMaximum(1000000);
        numSamples_spinBox->setValue(4096);
        phaseAccLen_spinBox = new QSpinBox(tab_1);
        phaseAccLen_spinBox->setObjectName(QStringLiteral("phaseAccLen_spinBox"));
        phaseAccLen_spinBox->setGeometry(QRect(180, 30, 71, 24));
        phaseAccLen_spinBox->setReadOnly(false);
        phaseAccLen_spinBox->setMaximum(64);
        phaseAccLen_spinBox->setValue(16);
        label_16 = new QLabel(tab_1);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(170, 10, 101, 16));
        label_17 = new QLabel(tab_1);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(50, 10, 101, 16));
        label_18 = new QLabel(tab_1);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(40, 60, 91, 16));
        freqOffset_spinBox = new QSpinBox(tab_1);
        freqOffset_spinBox->setObjectName(QStringLiteral("freqOffset_spinBox"));
        freqOffset_spinBox->setGeometry(QRect(40, 80, 81, 24));
        freqOffset_spinBox->setMaximum(999999);
        freqOffset_spinBox->setValue(768);
        chirpTuningWord_spinBox = new QSpinBox(tab_1);
        chirpTuningWord_spinBox->setObjectName(QStringLiteral("chirpTuningWord_spinBox"));
        chirpTuningWord_spinBox->setGeometry(QRect(150, 80, 81, 24));
        chirpTuningWord_spinBox->setMaximum(999999);
        chirpTuningWord_spinBox->setValue(1);
        chirpParamsGenButton = new QPushButton(tab_1);
        chirpParamsGenButton->setObjectName(QStringLiteral("chirpParamsGenButton"));
        chirpParamsGenButton->setGeometry(QRect(630, 110, 113, 32));
        chirpParamsResetButton = new QPushButton(tab_1);
        chirpParamsResetButton->setObjectName(QStringLiteral("chirpParamsResetButton"));
        chirpParamsResetButton->setGeometry(QRect(170, 110, 113, 32));
        tabWidget->addTab(tab_1, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tabWidget->addTab(tab_4, QString());
        tabWidget_2 = new QTabWidget(groupBox);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(0, 400, 831, 291));
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        transcript = new QTextEdit(tab_5);
        transcript->setObjectName(QStringLiteral("transcript"));
        transcript->setGeometry(QRect(0, 10, 451, 231));
        transcript->setStyleSheet(QStringLiteral("font: 10pt \"Menlo\";"));
        getThreadStatus = new QPushButton(tab_5);
        getThreadStatus->setObjectName(QStringLiteral("getThreadStatus"));
        getThreadStatus->setGeometry(QRect(490, 20, 91, 32));
        killThread = new QPushButton(tab_5);
        killThread->setObjectName(QStringLiteral("killThread"));
        killThread->setGeometry(QRect(490, 60, 91, 32));
        testButton = new QPushButton(tab_5);
        testButton->setObjectName(QStringLiteral("testButton"));
        testButton->setGeometry(QRect(640, 120, 113, 32));
        label_10 = new QLabel(tab_5);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(670, 10, 81, 16));
        label_11 = new QLabel(tab_5);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(670, 50, 81, 16));
        addressText = new QLineEdit(tab_5);
        addressText->setObjectName(QStringLiteral("addressText"));
        addressText->setGeometry(QRect(670, 30, 71, 21));
        valueWriteText = new QLineEdit(tab_5);
        valueWriteText->setObjectName(QStringLiteral("valueWriteText"));
        valueWriteText->setGeometry(QRect(670, 70, 71, 21));
        printExtBuf = new QPushButton(tab_5);
        printExtBuf->setObjectName(QStringLiteral("printExtBuf"));
        printExtBuf->setGeometry(QRect(490, 100, 91, 32));
        promiscModeCheckBox = new QCheckBox(tab_5);
        promiscModeCheckBox->setObjectName(QStringLiteral("promiscModeCheckBox"));
        promiscModeCheckBox->setGeometry(QRect(490, 160, 121, 20));
        tabWidget_2->addTab(tab_5, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        plotI = new QCustomPlot(tab_7);
        plotI->setObjectName(QStringLiteral("plotI"));
        plotI->setGeometry(QRect(0, 10, 801, 241));
        verticalScrollBarQ = new QScrollBar(tab_7);
        verticalScrollBarQ->setObjectName(QStringLiteral("verticalScrollBarQ"));
        verticalScrollBarQ->setGeometry(QRect(800, 10, 20, 251));
        verticalScrollBarQ->setOrientation(Qt::Vertical);
        horizontalScrollBarQ = new QScrollBar(tab_7);
        horizontalScrollBarQ->setObjectName(QStringLiteral("horizontalScrollBarQ"));
        horizontalScrollBarQ->setGeometry(QRect(0, 250, 801, 16));
        horizontalScrollBarQ->setOrientation(Qt::Horizontal);
        tabWidget_2->addTab(tab_7, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        plotQ = new QCustomPlot(tab_6);
        plotQ->setObjectName(QStringLiteral("plotQ"));
        plotQ->setGeometry(QRect(0, 10, 801, 241));
        verticalScrollBarI = new QScrollBar(tab_6);
        verticalScrollBarI->setObjectName(QStringLiteral("verticalScrollBarI"));
        verticalScrollBarI->setGeometry(QRect(800, 10, 20, 251));
        verticalScrollBarI->setOrientation(Qt::Vertical);
        horizontalScrollBarI = new QScrollBar(tab_6);
        horizontalScrollBarI->setObjectName(QStringLiteral("horizontalScrollBarI"));
        horizontalScrollBarI->setGeometry(QRect(0, 250, 801, 16));
        horizontalScrollBarI->setOrientation(Qt::Horizontal);
        tabWidget_2->addTab(tab_6, QString());
        tab_8 = new QWidget();
        tab_8->setObjectName(QStringLiteral("tab_8"));
        plotC = new QCustomPlot(tab_8);
        plotC->setObjectName(QStringLiteral("plotC"));
        plotC->setGeometry(QRect(0, 10, 801, 241));
        verticalScrollBarC = new QScrollBar(tab_8);
        verticalScrollBarC->setObjectName(QStringLiteral("verticalScrollBarC"));
        verticalScrollBarC->setGeometry(QRect(800, 10, 20, 251));
        verticalScrollBarC->setOrientation(Qt::Vertical);
        horizontalScrollBarC = new QScrollBar(tab_8);
        horizontalScrollBarC->setObjectName(QStringLiteral("horizontalScrollBarC"));
        horizontalScrollBarC->setGeometry(QRect(0, 250, 801, 16));
        horizontalScrollBarC->setOrientation(Qt::Horizontal);
        tabWidget_2->addTab(tab_8, QString());
        tabWidget_1 = new QTabWidget(groupBox);
        tabWidget_1->setObjectName(QStringLiteral("tabWidget_1"));
        tabWidget_1->setGeometry(QRect(0, 210, 831, 191));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        srcMacAddr = new QLineEdit(tab);
        srcMacAddr->setObjectName(QStringLiteral("srcMacAddr"));
        srcMacAddr->setGeometry(QRect(560, 20, 161, 21));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(560, 0, 71, 21));
        srcIpAddr = new QLineEdit(tab);
        srcIpAddr->setObjectName(QStringLiteral("srcIpAddr"));
        srcIpAddr->setGeometry(QRect(560, 70, 161, 21));
        destIpAddr = new QLineEdit(tab);
        destIpAddr->setObjectName(QStringLiteral("destIpAddr"));
        destIpAddr->setGeometry(QRect(330, 70, 151, 21));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(330, 0, 101, 20));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(560, 50, 59, 16));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(330, 50, 59, 16));
        destMacAddr = new QLineEdit(tab);
        destMacAddr->setObjectName(QStringLiteral("destMacAddr"));
        destMacAddr->setGeometry(QRect(330, 20, 151, 21));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(40, 30, 81, 16));
        writeButton = new QPushButton(tab);
        writeButton->setObjectName(QStringLiteral("writeButton"));
        writeButton->setGeometry(QRect(160, 20, 101, 32));
        readButton = new QPushButton(tab);
        readButton->setObjectName(QStringLiteral("readButton"));
        readButton->setGeometry(QRect(160, 100, 101, 32));
        byteReorderCheckBox = new QCheckBox(tab);
        byteReorderCheckBox->setObjectName(QStringLiteral("byteReorderCheckBox"));
        byteReorderCheckBox->setGeometry(QRect(170, 50, 101, 20));
        networkInterfaces = new QComboBox(tab);
        networkInterfaces->setObjectName(QStringLiteral("networkInterfaces"));
        networkInterfaces->setGeometry(QRect(40, 50, 104, 26));
        pktRecordCheckBox = new QCheckBox(tab);
        pktRecordCheckBox->setObjectName(QStringLiteral("pktRecordCheckBox"));
        pktRecordCheckBox->setGeometry(QRect(170, 130, 101, 20));
        label_22 = new QLabel(tab);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(500, 110, 81, 16));
        recOutputDirectory = new QLineEdit(tab);
        recOutputDirectory->setObjectName(QStringLiteral("recOutputDirectory"));
        recOutputDirectory->setGeometry(QRect(500, 130, 241, 21));
        label_23 = new QLabel(tab);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(310, 110, 81, 16));
        recOutputFilename = new QLineEdit(tab);
        recOutputFilename->setObjectName(QStringLiteral("recOutputFilename"));
        recOutputFilename->setGeometry(QRect(310, 130, 171, 21));
        tabWidget_1->addTab(tab, QString());
        tab_13 = new QWidget();
        tab_13->setObjectName(QStringLiteral("tab_13"));
        inputPcapFilename = new QLineEdit(tab_13);
        inputPcapFilename->setObjectName(QStringLiteral("inputPcapFilename"));
        inputPcapFilename->setGeometry(QRect(80, 30, 491, 21));
        outputPcapFilename = new QLineEdit(tab_13);
        outputPcapFilename->setObjectName(QStringLiteral("outputPcapFilename"));
        outputPcapFilename->setGeometry(QRect(80, 80, 121, 21));
        outputDirectory = new QLineEdit(tab_13);
        outputDirectory->setObjectName(QStringLiteral("outputDirectory"));
        outputDirectory->setGeometry(QRect(230, 80, 181, 21));
        readPcapButton = new QPushButton(tab_13);
        readPcapButton->setObjectName(QStringLiteral("readPcapButton"));
        readPcapButton->setGeometry(QRect(480, 70, 113, 32));
        label_19 = new QLabel(tab_13);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(90, 10, 101, 16));
        label_21 = new QLabel(tab_13);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(230, 60, 81, 16));
        label_20 = new QLabel(tab_13);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(80, 60, 81, 16));
        tabWidget_1->addTab(tab_13, QString());
        tab_14 = new QWidget();
        tab_14->setObjectName(QStringLiteral("tab_14"));
        tabWidget_1->addTab(tab_14, QString());
        UDAR_Controller->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(UDAR_Controller);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 853, 22));
        menuUDAR_GUI = new QMenu(menuBar);
        menuUDAR_GUI->setObjectName(QStringLiteral("menuUDAR_GUI"));
        UDAR_Controller->setMenuBar(menuBar);
        mainToolBar = new QToolBar(UDAR_Controller);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        UDAR_Controller->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(UDAR_Controller);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        UDAR_Controller->setStatusBar(statusBar);

        menuBar->addAction(menuUDAR_GUI->menuAction());

        retranslateUi(UDAR_Controller);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);
        tabWidget_1->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(UDAR_Controller);
    } // setupUi

    void retranslateUi(QMainWindow *UDAR_Controller)
    {
        UDAR_Controller->setWindowTitle(QApplication::translate("UDAR_Controller", "UDAR_Controller", 0));
        groupBox->setTitle(QApplication::translate("UDAR_Controller", "Underground Radar Control", 0));
        label_6->setText(QApplication::translate("UDAR_Controller", "Chirp PRF (s)", 0));
        label_8->setText(QApplication::translate("UDAR_Controller", "Min Freq. (MHz)", 0));
        label_9->setText(QApplication::translate("UDAR_Controller", "ADC Sample Cycles", 0));
        label_7->setText(QApplication::translate("UDAR_Controller", "Chirp Slope (MHz/us)", 0));
        label_13->setText(QApplication::translate("UDAR_Controller", "Chirp Time (us)", 0));
        label_12->setText(QApplication::translate("UDAR_Controller", "Bandwidth (MHz)", 0));
        label_14->setText(QApplication::translate("UDAR_Controller", "Chirp Tuning Word", 0));
        label_15->setText(QApplication::translate("UDAR_Controller", "Num. Samples", 0));
        label_16->setText(QApplication::translate("UDAR_Controller", "Phase Accum. Len. ", 0));
        label_17->setText(QApplication::translate("UDAR_Controller", "Clock Freq. (MHz)", 0));
        label_18->setText(QApplication::translate("UDAR_Controller", "Freq. Offset Word", 0));
        chirpParamsGenButton->setText(QApplication::translate("UDAR_Controller", "Calculate Params", 0));
        chirpParamsResetButton->setText(QApplication::translate("UDAR_Controller", "Reset Defaults", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("UDAR_Controller", "Chirp", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("UDAR_Controller", "...", 0));
        getThreadStatus->setText(QApplication::translate("UDAR_Controller", "Thread Status", 0));
        killThread->setText(QApplication::translate("UDAR_Controller", "Kill Thread", 0));
        testButton->setText(QApplication::translate("UDAR_Controller", "Send Test", 0));
        label_10->setText(QApplication::translate("UDAR_Controller", "Address", 0));
        label_11->setText(QApplication::translate("UDAR_Controller", "Command", 0));
        printExtBuf->setText(QApplication::translate("UDAR_Controller", "Print Packet", 0));
        promiscModeCheckBox->setText(QApplication::translate("UDAR_Controller", "Promiscuous Mode", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_5), QApplication::translate("UDAR_Controller", "Transcript", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_7), QApplication::translate("UDAR_Controller", "I Channel", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_6), QApplication::translate("UDAR_Controller", "Q Channel", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_8), QApplication::translate("UDAR_Controller", "Counter", 0));
        label_2->setText(QApplication::translate("UDAR_Controller", "Source Mac", 0));
        label->setText(QApplication::translate("UDAR_Controller", "Dest Mac", 0));
        label_4->setText(QApplication::translate("UDAR_Controller", "Source IP", 0));
        label_3->setText(QApplication::translate("UDAR_Controller", "Dest IP", 0));
        label_5->setText(QApplication::translate("UDAR_Controller", "Interface", 0));
        writeButton->setText(QApplication::translate("UDAR_Controller", "Inject Packet", 0));
        readButton->setText(QApplication::translate("UDAR_Controller", "Listen", 0));
        byteReorderCheckBox->setText(QApplication::translate("UDAR_Controller", "Reorder Bytes", 0));
        pktRecordCheckBox->setText(QApplication::translate("UDAR_Controller", "Save to file", 0));
        label_22->setText(QApplication::translate("UDAR_Controller", "Output Directory", 0));
        recOutputDirectory->setText(QApplication::translate("UDAR_Controller", "/Users/sam/outputs/", 0));
        label_23->setText(QApplication::translate("UDAR_Controller", "Output Filename", 0));
        recOutputFilename->setText(QApplication::translate("UDAR_Controller", "dataout.bin", 0));
        tabWidget_1->setTabText(tabWidget_1->indexOf(tab), QApplication::translate("UDAR_Controller", "Network", 0));
        inputPcapFilename->setText(QApplication::translate("UDAR_Controller", "/Users/sam/WiresharkCaptures/adc_chirp.pcapng", 0));
        outputPcapFilename->setText(QApplication::translate("UDAR_Controller", "adc_chirp", 0));
        outputDirectory->setText(QApplication::translate("UDAR_Controller", "/Users/sam/outputs/", 0));
        readPcapButton->setText(QApplication::translate("UDAR_Controller", "Read Pcap File", 0));
        label_19->setText(QApplication::translate("UDAR_Controller", "Input Pcap Filename", 0));
        label_21->setText(QApplication::translate("UDAR_Controller", "Output Directory", 0));
        label_20->setText(QApplication::translate("UDAR_Controller", "Output Filename", 0));
        tabWidget_1->setTabText(tabWidget_1->indexOf(tab_13), QApplication::translate("UDAR_Controller", "Pcap", 0));
        tabWidget_1->setTabText(tabWidget_1->indexOf(tab_14), QApplication::translate("UDAR_Controller", "...", 0));
        menuUDAR_GUI->setTitle(QApplication::translate("UDAR_Controller", "UDAR GUI", 0));
    } // retranslateUi

};

namespace Ui {
    class UDAR_Controller: public Ui_UDAR_Controller {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UDAR_CONTROLLER_H
