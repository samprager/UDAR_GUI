#ifndef GETIP_H
#define GETIP_H

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

const sockaddr_in* castToIP4(const sockaddr* addr);
void printIP(const char* name, int addr);
void printIP(const char* name, const sockaddr_in* addr);
const char* levelToString(int level);
int getInterfaceConfig(char ***if_names, char ***if_stats, uint8_t ***if_macs, uint8_t ***if_ips);

#endif // GETIP_H
