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
#include "decode_pcap.h"
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

#define PEAK_STAT_COMMAND 0x504B504B         //Ascii PKPK

#define TX_PKT_CMD_REPEAT 2


#define DEFAULT_DEST_MAC "5a:01:02:03:04:05"
#define DEFAULT_SRC_MAC "98:05:02:03:04:05"
#define DEFAULT_DEST_IP "192.168.10.1"
#define DEFAULT_SRC_IP "192.168.10.10"
#define DEFAULT_IF_DEV1 "en4"
#define DEFAULT_IF_DEV2 "en0"

#define PLOT_RANGE_LIMIT 13056 // = 3*(4096+256) // 32000
#define SAMPLING_FREQ 245.76    // MHz
#define DEFAULT_ADC_SAMPLES 254
#define DEFAULT_CHIRP_PRF 10.0
#define DEFAULT_FREQ_OFFSET 768
#define DEFAULT_NUM_SAMPLES 4096
#define DEFAULT_CHIRP_TUNING_WORD 1
#define DEFAULT_CHIRP_PHASE_ACCUM_LEN 16

#define FFT_LEN 32768
#define SPEED_OF_LIGHT 300000000.0
#define RELATIVE_PERMITTIVITY 1.0

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

struct radar_status_payload {
    uint32_t command_word;
    uint16_t placeholder;
    u_char   threshold_ctrl_i;
    u_char   threshold_ctrl_q;
    uint32_t adc_counter;
    uint32_t glbl_counter;
    uint32_t chirp_control_word;
    uint32_t chirp_freq_off;
    uint32_t chirp_tuning_word;
    uint32_t chirp_num_samples;
    uint32_t peak_index_q;
    uint32_t peak_index_i;
    uint64_t peak_value_q;
    uint64_t peak_value_i;
    uint32_t num_peaks_q;
    uint32_t num_peaks_i;
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

    void setupDataPlot(QCustomPlot *plot, QPen pen);
    void setupCounterPlot(QCustomPlot *plot, QPen pen);
    void setupPlotIQ();
    void updateDataPlotIQ();
    void updateFFTPlotIQ();
    void connectSignals();
    void controllerInit();
    void calculateChirpParams();
    void storeChirpParams();
    void storeFMC150Params();
    u_char GetRxDataFormat();

    void sendCommand(const QString name);
    void sendCommand(const QString name, uint32_t cmd);
    void sendTestCommand(const QString name);
    uint32_t genCommandIdentifier();
    QStringList getNetworkInterfaces();
    void read_pcap(int argc, char *argv[], char *outdir);
    void decode_plot(int argc, char *argv[], char *outdir);


    int fftData(double **fft, QVector<double> &data, int datasize);
    int fftDataI(double **fftI, uint32_t *dataIQ,int datasize);
    int fftDataQ(double **fftQ, uint32_t *dataIQ,int datasize);
    int fftDataIQ(double **fftIQ, uint32_t *dataIQ,int datasize);

    void getMacArray(u_char mac[6],QString text);
    void getIpArray(u_char ip[4],QString text);

    void setStatusTranscript(QString text);
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
    struct radar_status_payload radar_status;
    struct radar_status_payload radar_calib_zero;
    time_t start_time;
    struct timeval start_tp;
    QTimer *rx_status_timer;

    uint32_t calib_index_i;
    uint32_t calib_index_q;

    QVector<double> plotDataI;
    QVector<double> plotDataQ;
    QVector<double> plotDataC;
    QVector<double> plotDataI2;
    QVector<double> plotDataQ2;
    QVector<double> plotDataC2;
    QVector<double> plotTimeVec;
    QVector<double> plotfftI;
    QVector<double> plotfftQ;
    QVector<double> plotfftI2;
    QVector<double> plotfftQ2;
    QVector<double> plotfftVec;
    QVector<double> ctrjumpsX;
    QVector<double> ctrjumpsY;
    QVector<double> ctrjumpsY2;





    uint16_t global_pkt_counter;

private slots:
    void updateInterfaceFields(const QString if_name);
    void updateRXStatus();
    void updateDataPlot(QCustomPlot *plot,QVector<double> &dataX,QVector<double> &dataY, int graph_num);
    void horzScrollBarChanged(QCustomPlot *plot, int value);
    void vertScrollBarChanged(QCustomPlot *plot, int value);
    void selectionChanged(QCustomPlot *plot);
    void mousePress(QCustomPlot *plot);
    void mouseWheel(QCustomPlot *plot);

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
    void on_calibrateIndexZero_pressed();
    void on_resetIndexZero_pressed();
    void on_printExtBuf_clicked();
    void on_promiscModeCheckBox_stateChanged(int state);

    void on_dec2hex_in_returnPressed();
    void on_hex2dec_in_returnPressed();

    void fixTranscriptPosition();



};

#endif // UDAR_CONTROLLER_H
