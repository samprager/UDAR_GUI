/**
 @file getip.cpp
 
 Enumerates the "interfaces" on a Unix (e.g. OS X, Linux, FreeBSD)
 system.  This includes what we consider to be the Ethernet and
 Wireless adapters.

 This code will:

 - get the IP address
 - get the broadcast address
 - get the subnet mask

 and print them for all such devices.  This is similar functionality
 to the Unix program ifconfig.  The purpose of this program is to
 demonstrate how to access that functionality within a C program.

 */

#include "getip.h"


const sockaddr_in* castToIP4(const sockaddr* addr) {
    if (addr == NULL) {
        return NULL;
    } else if (addr->sa_family == AF_INET) {
        // An IPv4 address
        return reinterpret_cast<const sockaddr_in*>(addr);
    } else {
        // Not an IPv4 address
        return NULL;
    }
}


/** Assumes addr is in host byte order */
void printIP(const char* name, int addr) {
    printf("%s = %3d.%3d.%3d.%3d\n", name, (addr >> 24) & 0xFF, (addr >> 16) & 0xFF,
           (addr >> 8) & 0xFF, addr & 0xFF);
}


void printIP(const char* name, const sockaddr_in* addr) {
    if (addr != NULL) {
        printIP(name, ntohl(addr->sin_addr.s_addr));
    } 
}

const char* levelToString(int level) {
    switch(level) {
    case AF_INET:
        return "Internet (AF_INET)";

    case AF_LINK:
        return "Link (AF_LINK/AF_PACKET)";
    default:
        return "Other";
    }
}

int getInterfaceConfig(char ***if_names, char ***if_stats, uint8_t ***if_macs, uint8_t ***if_ips) {
    int i,index;
    int numinterfaces;
    char name_prev[128];
    char **tmp_names;
    char **tmp_stats;
    uint8_t **tmp_macs;
    uint8_t **tmp_ips;

    // Head of the interface address linked list
    ifaddrs* ifap = NULL;

    int r = getifaddrs(&ifap);

    if (r != 0) {
        // Non-zero return code means an error
        printf("return code = %d\n", r);
        exit(r);
    }

    ifaddrs* current = ifap;

    if (current == NULL) {
        printf("No interfaces found\n");
    }

    numinterfaces=0;
    while (current != NULL) {
        if(strcmp(name_prev,current->ifa_name)){
            numinterfaces++;
        }
        strcpy(name_prev,current->ifa_name);
        current = current->ifa_next;
    }
    tmp_names = new char*[numinterfaces];
    tmp_stats = new char*[numinterfaces];
    tmp_macs = new uint8_t*[numinterfaces];
    tmp_ips = new uint8_t*[numinterfaces];

    for (i=0;i<numinterfaces;i++){
        tmp_names[i] = new char[128];
        tmp_stats[i] = new char [128];
        tmp_macs[i] = new uint8_t[6];
        tmp_ips[i] = new uint8_t[4];
    }

    memset(&name_prev[0], 0, sizeof(name_prev));

    current = ifap;
    index = -1;
    while (current != NULL) {

        if(strcmp(name_prev,current->ifa_name)){
            index++;
            strcpy(tmp_names[index],current->ifa_name);
        }

        const sockaddr_in* interfaceAddress = castToIP4(current->ifa_addr);
        const sockaddr_in* broadcastAddress = castToIP4(current->ifa_dstaddr);
        const sockaddr_in* subnetMask       = castToIP4(current->ifa_netmask);

        printf("Interface %s", current->ifa_name);
        if (current->ifa_addr != NULL) {
            printf(" %s", levelToString(current->ifa_addr->sa_family));
        }
        printf("\nStatus    = %s\n", (current->ifa_flags & IFF_UP) ? "Online" : "Down");
        printIP("IP       ", interfaceAddress);
        printIP("Broadcast", broadcastAddress);
        printIP("Subnet   ", subnetMask);

        if(interfaceAddress != NULL){
            int addr = ntohl(interfaceAddress->sin_addr.s_addr);
            *(tmp_ips[index]) = (addr >> 24) & 0xFF;
            *(tmp_ips[index]+1) = (addr >> 16) & 0xFF;
            *(tmp_ips[index]+2) = (addr >> 8) & 0xFF;
            *(tmp_ips[index]+3) = addr & 0xFF;
            printf("02x",*(tmp_ips[index]+3));
        }
        
        // The MAC address and the interfaceAddress come in as
        // different interfaces with the same name.

        if ((current->ifa_addr != NULL) && (current->ifa_addr->sa_family == AF_LINK)) {
#           ifdef __linux__
            // Linux
            struct ifreq ifr;

            int fd = socket(AF_INET, SOCK_DGRAM, 0);

            ifr.ifr_addr.sa_family = AF_INET;
            strcpy(ifr.ifr_name, current->ifa_name);
            ioctl(fd, SIOCGIFHWADDR, &ifr);
            close(fd);

            uint8_t* MAC = reinterpret_cast<uint8_t*>(ifr.ifr_hwaddr.sa_data);
            
#else
            // Posix/FreeBSD/Mac OS
            sockaddr_dl* sdl = (struct sockaddr_dl *)current->ifa_addr;
            uint8_t* MAC = reinterpret_cast<uint8_t*>(LLADDR(sdl));

#endif
            memcpy(tmp_macs[index],MAC,6);
            sprintf(tmp_stats[index],"%s", (current->ifa_flags & IFF_UP) ? "Online" : "Down");

            printf("MAC       = %02x:%02x:%02x:%02x:%02x:%02x\n", MAC[0], MAC[1], MAC[2], MAC[3], MAC[4], MAC[5]);
        }
        
        printf("\n");
        strcpy(name_prev,current->ifa_name);
        current = current->ifa_next;
        char* tempname = tmp_names[index];
        char* tempstat = tmp_stats[index];
        uint8_t *tempmac = tmp_macs[index];
        uint8_t *tempip = tmp_ips[index];
    }

    freeifaddrs(ifap);
    ifap = NULL;

    *if_names = tmp_names;
    *if_stats = tmp_stats;
    *if_macs = tmp_macs;
    *if_ips = tmp_ips;

    return numinterfaces;
}
