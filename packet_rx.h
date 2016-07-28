#ifndef PACKET_RX_H
#define PACKET_RX_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <net/if.h>
#include <netinet/if_ether.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pcap.h>
#include <pthread.h>
#include <stdint.h>
#include <time.h>

#define RX_WRITE_LIM 10000
#define RX_PKT_SIZE 528 //496
#define RX_HEADER_SIZE 16
#define RX_STAT_PKT_SIZE 80


struct arg_struct{
  void *filename;
  void *devname;
  void *dimensions;
  void *mutex;
  void *extmutex;
  void *statmutex;
  void *buffer;
  void *statbuffer;
  void *extbuffer;
  void *newdata;
  void *newstat;
  void *threadcontrol;
  void *extstatus;
};

void pcap_fatal(const char *failed_in, const char *errbuf);
void *listenThread(void *args);
void *writeThread(void *args);
void *extBufferThread(void *args);


#endif // PACKET_RX_H
