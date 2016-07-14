#ifndef NETINTERFACE_H
#define NETINTERFACE_H

#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <net/if.h>
#ifdef __linux__
#    include <sys/ioctl.h>
#    include <netinet/in.h>
#    include <unistd.h>
#    include <string.h>

//    Match Linux to FreeBSD
#    define AF_LINK AF_PACKET
#else
#    include <net/if_dl.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <netinet/if_ether.h>
#include <netinet/ip.h>

#include <pcap.h>
#include <errno.h>

#include "packet_rx.h"
#include <QMainWindow>

#include <QString>

class UDAR_Controller;

class NetInterface
{
public:
    NetInterface();
    NetInterface(char *name);
    NetInterface(QString name);
    NetInterface(UDAR_Controller *parent,QString name);
    NetInterface(QString name, u_char mac[6]);
    NetInterface(QString name, u_char mac[6], u_char ip[4]);
    NetInterface(QString name,QString status, u_char mac[6]);
    NetInterface(QString name,QString status, u_char mac[6],u_char ip[4]);
    u_char *GetMac();
    QString GetMacString();
    QString GetName();
    char * GetNameString();
    QString GetStatus();
    QString GetIpString();
    u_char *GetIp();
    void setMac(QString mac);
    void setMac(u_char mac[6]);
    void setIp(QString ip);
    void setIp(u_char ip[4]);
    void setStatus(QString status);
    void setStatus(char *status);
    //int initRxThreads(char fname[], char outdir[]);
    int initRxThreads(char fname[], char outdir[],int init_wr_thread,int writelim);
    int initWrThread();
    QString GetThreadStatus();
    int KillThreads();
    int PrintExtBuffer(int offset);
    void setPromiscMode(int value);
private:
    UDAR_Controller *parent_ui;
    QString if_name;
    QString if_status;
    u_char if_mac[6];
    u_char if_ip[6];
    int has_mac,has_ip,has_status;
    int numbufs;    // Number of row buffers
    int numextbufs;    // Number of row external buffers
    int numthreads;
    int numextmutex;

    unsigned char ** rec_pbuffer;
    unsigned char ** rec_pextbuf;
    pthread_mutex_t *rec_mutex;
    pthread_mutex_t *rec_extmutex;
    pthread_t *rec_threads;
    int **rec_threadctrl;
    char *rec_filename;
    char *rec_device;
    int *rec_newdata;
    int *rec_dim;
    int *rec_extstatus;
    struct arg_struct *rec_args;
    int rec_writelim;

    int rx_thread_open;
    int wr_thread_open;

};

#endif // NETINTERFACE_H
