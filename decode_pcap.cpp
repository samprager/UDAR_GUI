#include "decode_pcap.h"

#define WRITE_LIM 5000
#define PKT_SIZE 496
#define HEADER_SIZE 16
#define SUB_PKT_SIZE 64 // 64 bytes or 512 bits


void dump_UDP_packet(const unsigned char *packet, struct timeval ts,unsigned int capture_len)
{
  struct ip *ip;
  struct UDP_hdr *udp;
  unsigned int IP_header_length;

  /* For simplicity, we assume Ethernet encapsulation. */

  if (capture_len < sizeof(struct ether_header))
  {
    /* We didn't even capture a full Ethernet header, so we
    * can't analyze this any further.
    */
    too_short(ts, "Ethernet header");
    return;
  }

  /* Skip over the Ethernet header. */
  packet += sizeof(struct ether_header);
  capture_len -= sizeof(struct ether_header);

  if (capture_len < sizeof(struct ip))
  { /* Didn't capture a full IP header */
    too_short(ts, "IP header");
    return;
  }

  ip = (struct ip*) packet;
  IP_header_length = ip->ip_hl * 4;	/* ip_hl is in 4-byte words */

  if (capture_len < IP_header_length)
  { /* didn't capture the full IP header including options */
  too_short(ts, "IP header with options");
  return;
  }

  if (ip->ip_p != IPPROTO_UDP)
  {
    problem_pkt(ts, "non-UDP packet");
    return;
  }

  /* Skip over the IP header to get to the UDP header. */
  packet += IP_header_length;
  capture_len -= IP_header_length;

  if (capture_len < sizeof(struct UDP_hdr))
  {
    too_short(ts, "UDP header");
    return;
  }

  udp = (struct UDP_hdr*) packet;

  printf("%s UDP src_port=%d dst_port=%d length=%d\n",
  timestamp_string(ts),
  ntohs(udp->uh_sport),
  ntohs(udp->uh_dport),
  ntohs(udp->uh_ulen));
}

int decodeDataPacket(uint32_t **dataU, uint32_t **dataL,unsigned char *packet_data, int size, int numpkts,int counter_offset, int s_index)
{
  int i,j,e_index,sq_size32,start_found;
  uint32_t temp0,temp1;
  uint32_t u_cval0,l_cval0,u_cval1,l_cval1;

  s_index = s_index%16;

  e_index = ((numpkts*size)/4 - s_index)%16;

  sq_size32 = ((numpkts*size)/4 - s_index - e_index)/2;

 // *dataIQ = (uint32_t *)malloc(sq_size32*sizeof(uint32_t));
 // *counter = (uint32_t *)malloc(sq_size32*sizeof(uint32_t));
  *dataL = new uint32_t[sq_size32];
  *dataU = new uint32_t[sq_size32];

  uint32_t l_ctr1 = 0;
  uint32_t u_ctr1 = 0;
  uint32_t l_ctr2 = 0;
  uint32_t u_ctr2 = 0;
  uint32_t nchirps = 0;
  uint32_t chirp_len = 0;
  uint32_t cur_ind = 0;

//reverse order of 32 bit words for each 512 bit sub-packet
  for (i=0;i<sq_size32;i+=8){
    for (j=0;j<8;j++){
      memcpy(*dataL+i+j,((uint32_t*)packet_data)+2*i+s_index+counter_offset+14-2*j,sizeof(uint32_t));
      memcpy(*dataU+i+j,((uint32_t*)packet_data)+2*i+s_index+1-counter_offset+14-2*j,sizeof(uint32_t));
    }
  }
 return sq_size32;

}

int decodeDataJumps( int ** cjumps,uint32_t *dataU, uint32_t *dataL, int datasize)
{
  int i,j,numjumps;
  int *cjumps_temp;
  uint32_t l_ctr1 = 0;
  uint32_t u_ctr1 = 0;
  uint32_t l_ctr2 = 0;
  uint32_t u_ctr2 = 0;
  uint32_t chirp_len = 0;
  int nchirps = 0;
  int numchirps = 0;
  int cur_ind = 0;

  for (i=0;i<datasize;i+=8){
    l_ctr2 = dataL[i+7];
    u_ctr2 = dataU[i+7];
    if(i==cur_ind){
        l_ctr1 = dataL[cur_ind];
        u_ctr1 = dataU[cur_ind];
    }
    else if ((l_ctr2 == l_ctr1+i+7-cur_ind)&(u_ctr2 == u_ctr1+i+7-cur_ind)){
           nchirps++;
           chirp_len = l_ctr2-l_ctr1;
           cur_ind = i+8;
    }
  }

  numchirps = nchirps;

  numjumps = 2*numchirps+2;

  cjumps_temp = new int[numjumps];

  cjumps_temp[0] = 0;
  cjumps_temp[numjumps-1] = datasize-1;

  nchirps = 0;
  cur_ind = 0;

  int l_off;
  int u_off;

  for (i=0;i<datasize;i+=8){
    l_ctr2 = dataL[i+7];
    u_ctr2 = dataU[i+7];
    if(i==cur_ind){
        l_ctr1 = dataL[cur_ind];
        u_ctr1 = dataU[cur_ind];
    }
    else if ((l_ctr2 == l_ctr1+i+7-cur_ind)&(u_ctr2 == u_ctr1+i+7-cur_ind)){
           cjumps_temp[2*nchirps+1] = cur_ind;
           cjumps_temp[2*nchirps+2] = i+7;
           nchirps++;
           cur_ind = i+8;
    }
  }

 *cjumps = cjumps_temp;
 return numjumps;

}

int decodePacket(uint32_t **dataIQ, uint32_t **counter,unsigned char *packet_data,int size, int numpkts, int counter_offset, int s_index)
{
  int i,j,e_index,sq_size32,start_found;
  uint32_t temp0,temp1;
  uint32_t u_cval0,l_cval0,u_cval1,l_cval1;

  s_index = s_index%16;

  e_index = ((numpkts*size)/4 - s_index)%16;

  sq_size32 = ((numpkts*size)/4 - s_index - e_index)/2;

 // *dataIQ = (uint32_t *)malloc(sq_size32*sizeof(uint32_t));
 // *counter = (uint32_t *)malloc(sq_size32*sizeof(uint32_t));
  *dataIQ = new uint32_t[sq_size32];
  *counter = new uint32_t[sq_size32];

//reverse order of 32 bit words for each 512 bit sub-packet
  for (i=0;i<sq_size32;i+=8){
    for (j=0;j<8;j++){
      memcpy(*counter+i+j,((uint32_t*)packet_data)+2*i+s_index+counter_offset+14-2*j,sizeof(uint32_t));
      memcpy(*dataIQ+i+j,((uint32_t*)packet_data)+2*i+s_index+1-counter_offset+14-2*j,sizeof(uint32_t));
    }
  }

 return sq_size32;

}

int decodePacket(uint32_t **dataIQ, uint32_t **counter,unsigned char *packet_data,int size, int numpkts)
{
  int i,j,s_index,e_index,sq_size32,start_found;
  int counter_offset;
  uint32_t temp0,temp1;
  uint32_t u_cval0,l_cval0,u_cval1,l_cval1;

  u_cval0 = *((uint32_t*)packet_data);
  l_cval0 = *(((uint32_t*)packet_data)+1);
  u_cval1 = *(((uint32_t*)packet_data)+2);
  l_cval1 = *(((uint32_t*)packet_data)+3);

// Determine whether counter is in upper or lower 32 bits of 64b word
  if ((u_cval0 == u_cval1+1)||(u_cval1 == u_cval0+15)) {
    counter_offset = 0;
  } else if ((l_cval0 == l_cval1+1)||(l_cval1 == l_cval0+15)) {
    counter_offset = 1;
  } else {
    return -1;
  }

// find start of first 512 bit sub-packet
  s_index = 0;
  start_found = 0;
  while (start_found == 0){
    if(s_index == 16){
      return -1;
    }
    temp0 = *(((uint32_t*)packet_data)+counter_offset+s_index);
    temp1 = *(((uint32_t*)packet_data)+counter_offset+s_index+2);
    if (temp0 != temp1+1){
      start_found = 1;
    }
    s_index += 2;
  }
  s_index = s_index%16;

  e_index = ((numpkts*size)/4 - s_index)%16;

  sq_size32 = ((numpkts*size)/4 - s_index - e_index)/2;

 // *dataIQ = (uint32_t *)malloc(sq_size32*sizeof(uint32_t));
 // *counter = (uint32_t *)malloc(sq_size32*sizeof(uint32_t));
  *dataIQ = new uint32_t[sq_size32];
  *counter = new uint32_t[sq_size32];

//reverse order of 32 bit words for each 512 bit sub-packet
  for (i=0;i<sq_size32;i+=8){
    for (j=0;j<8;j++){
      memcpy(*counter+i+j,((uint32_t*)packet_data)+2*i+s_index+counter_offset+14-2*j,sizeof(uint32_t));
      memcpy(*dataIQ+i+j,((uint32_t*)packet_data)+2*i+s_index+1-counter_offset+14-2*j,sizeof(uint32_t));
    }
  }

 return sq_size32;

}

int counterJumps(int ** cjumps,uint32_t *counter,int datasize)
{
  int i,j,numjumps;
  int *temparray;
  numjumps = 2;
  for (i=1;i<datasize;i++){
    if (counter[i]!=counter[i-1]+1){
      numjumps++;
    }
  }
  //temparray = (int *)malloc((2+numjumps)*sizeof(int));
  temparray = new int[(numjumps)];

  temparray[0] = 0;
  j = 1;
  for (i=1;i<datasize;i++){
    if (counter[i]!=counter[i-1]+1){
      temparray[j] = i;
      j++;
    }
  }
  temparray[numjumps-1] = datasize-1;


  *cjumps = temparray;
  return numjumps;
}


/* Note, this routine returns a pointer into a static buffer, and
* so each call overwrites the value returned by the previous call.
*/
const char *timestamp_string(struct timeval ts)
{
  static char timestamp_string_buf[256];

  sprintf(timestamp_string_buf, "%d.%06d",
  (int) ts.tv_sec, (int) ts.tv_usec);

  return timestamp_string_buf;
}

void problem_pkt(struct timeval ts, const char *reason)
{
  fprintf(stderr, "%s: %s\n", timestamp_string(ts), reason);
}

void too_short(struct timeval ts, const char *truncated_hdr)
{
  fprintf(stderr, "packet with timestamp %s is truncated and lacks a full %s\n",
  timestamp_string(ts), truncated_hdr);
}
