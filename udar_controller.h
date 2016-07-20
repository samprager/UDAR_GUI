#ifndef UDAR_CONTROLLER_H
#define UDAR_CONTROLLER_H

#include <QMainWindow>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <net/if.h>
#include <netdb.h>

#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#include "getip.h"
#include "fftCT.h"

#include "netinterface.h"
#include "read_pcap.h"
#include "packet_rx.h"
#include "qcustomplot.h"
#include <QMap>

#define STR_SIZE 100

#ifdef __linux__
#define DEFAULT_DIRECTORY "/home/sprager/outputs/"
#else
#define DEFAULT_DIRECTORY "/Users/sam/outputs/"
#endif

#define CHIRP_WRITE_COMMAND 0x57574343          //Ascii WWCC
#define FMC150_WRITE_COMMAND 0x57574646         //Ascii WWFF
#define DATA_WRITE_COMMAND 0x57574441       //Ascii WWDA

#define CHIRP_READ_COMMAND 0x52524343          //Ascii RRCC
#define FMC150_READ_COMMAND 0x52524646         //Ascii RRFF

#define TX_PKT_CMD_REPEAT 2


#define DEFAULT_DEST_MAC "5a:01:02:03:04:05"
#define DEFAULT_SRC_MAC "98:05:02:03:04:05"
#define DEFAULT_DEST_IP "192.168.10.1"
#define DEFAULT_SRC_IP "192.168.10.10"
#define DEFAULT_IF_DEV1 "en4"
#define DEFAULT_IF_DEV2 "en0"

#define PLOT_RANGE_LIMIT 1000000 // 32000
#define SAMPLING_FREQ 245.76    // MHz

#define PCAP_WRITE_LIM 5000
#define PCAP_PKT_SIZE 496
#define PCAP_HEADER_SIZE 16
#define PCAP_SUB_PKT_SIZE 64 // 64 bytes or 512 bits

struct chirp_parameters {
    uint32_t command_id;
    uint32_t prf_int;
    uint32_t prf_frac;
    uint32_t adc_count;
    uint32_t freq_off;
    uint32_t tuning_word;
    uint32_t num_samples;
    uint32_t control_word;
};
struct fmc150_parameters {
    uint32_t command_id;
    u_char set_CH_A_iDelay;
    u_char set_CH_B_iDelay;
    u_char set_CLK_iDelay;
    u_char set_user8;
    uint16_t register_addres;
    uint16_t set_user16;
    uint32_t spi_register_data_to_fmc150;
    uint32_t rw;
    u_char cdce72010;
    u_char ads62p49;
    u_char dac3283;
    u_char amc7823;
    u_char code_check1;
    u_char code_check2;
    uint16_t code_check16;
    uint32_t control_word;
};

namespace Ui {
class UDAR_Controller;
}

class UDAR_Controller : public QMainWindow
{
    Q_OBJECT

public:
    explicit UDAR_Controller(QWidget *parent = 0);
    ~UDAR_Controller();

    void setupPlotIQ();
    void updateDataPlotIQ();
    void updateFFTPlotIQ();
    void connectSignals();
    void controllerInit();
    void calculateChirpParams();
    void storeChirpParams();
    void storeFMC150Params();

    void sendCommand(const QString name);
    void sendCommand(const QString name, uint32_t cmd);
    void sendTestCommand(const QString name);
    uint32_t genCommandIdentifier();
    QStringList getNetworkInterfaces();
    void read_pcap(int argc, char *argv[], char *outdir);
    void decode_plot(int argc, char *argv[], char *outdir);

    int fftDataI(double **fftI, uint32_t *dataIQ,int datasize);
    int fftDataQ(double **fftQ, uint32_t *dataIQ,int datasize);
    int fftDataIQ(double **fftIQ, uint32_t *dataIQ,int datasize);

    void getMacArray(u_char mac[6],QString text);
    void getIpArray(u_char ip[4],QString text);

    void setTranscript(QString text);
    void setTranscript(char * text);
    void setTranscript(u_char * text);
    void setTranscript(u_char * data, int len);
    void setTranscript(double data);
    void setTranscript(int data);
    void setTranscript(unsigned int data);

private:
    Ui::UDAR_Controller *ui;
    QStringList interfaceNames;
    QMap<QString,NetInterface*> interfaceMap;
    struct chirp_parameters chirp_params;
    struct fmc150_parameters fmc150_params;
    time_t start_time;
    struct timeval start_tp;

    QVector<double> plotDataI;
    QVector<double> plotDataQ;
    QVector<double> plotDataC;
    QVector<double> plotTimeVec;
    QVector<double> plotfftI;
    QVector<double> plotfftQ;
    QVector<double> plotfftVec;
    QVector<double> ctrjumpsX;
    QVector<double> ctrjumpsY;





    uint16_t global_pkt_counter;

private slots:
    void updateInterfaceFields(const QString if_name);

    void horzScrollBarIChanged(int value);
    void vertScrollBarIChanged(int value);
    void horzScrollBarQChanged(int value);
    void vertScrollBarQChanged(int value);
    void horzScrollBarCChanged(int value);
    void vertScrollBarCChanged(int value);
    void horzScrollBarFFTIChanged(int value);
    void vertScrollBarFFTIChanged(int value);
    void horzScrollBarFFTQChanged(int value);
    void vertScrollBarFFTQChanged(int value);

    void xAxisIChanged(QCPRange range);
    void yAxisIChanged(QCPRange range);

    void selectionChanged();
    void mousePress();
    void mouseWheel();

    void on_tabWidget_a_currentChanged(int value);
    void on_testButton_clicked();
    void on_writeButton_clicked();
    void on_listenButton_clicked();
    void on_chirpTuningWord_spinBox_valueChanged(int value);
    void on_numSamples_spinBox_valueChanged(int value);
    void on_freqOffset_spinBox_valueChanged(int value);
    void on_chirpParamsGenButton_clicked();
    void on_chirpParamsResetButton_clicked();
    void on_clockFreq_dSpinBox_valueChanged(double value);
    void on_phaseAccLen_spinBox_valueChanged(int value);
    void on_adcSamples_spinBox_valueChanged(int value);
    void on_chirpPRF_dSpinBox_valueChanged(double value);
    void on_readPcapButton_clicked();
    void on_plotOutputButton_clicked();
    void on_getThreadStatus_clicked();
    void on_killThread_clicked();
    void on_printExtBuf_clicked();
    void on_promiscModeCheckBox_stateChanged(int state);

    void fixTranscirptPosition();



};

#endif // UDAR_CONTROLLER_H
