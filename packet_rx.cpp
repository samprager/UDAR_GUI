#include "packet_rx.h"

#define SUB_PKT_SIZE 64 // 64 bytes or 512 bits



// struct arg_struct{
//   char *filename;
//   char *devname;
//   char *dimensions;
//   pthread_mutex_t *mutex;
//   uint32_t **buffer;
//   int *threadcontrol;
// };

/* Some helper functions, which we define at the end of this file. */

void pcap_fatal(const char *failed_in, const char *errbuf) {
    printf("Fatal Error in %s: %s\n", failed_in, errbuf);
    exit(1);
}


void *listenThread(void *args){
  int i,j,ext_ind;
  int numbufs,numextbufs,len,offset,trim,ext_buffer_empty,numstatbufs,lenstat;
  int threadexit,wcount,count;
  int *dim, *threadcontrol, *newdata, *extstatus, *newstat;
  struct arg_struct *arguments = (struct arg_struct *)args;
  dim = (int *)arguments->dimensions;

  struct pcap_pkthdr header;
  const u_char *packet;
  char errbuf[PCAP_ERRBUF_SIZE];
  char *device;
  unsigned char **pbuffer, **pextbuffer, **pstatbuffer;
  pcap_t *pcap_handle;

  pthread_mutex_t *mutex;
  pthread_mutex_t *extmutex;
  pthread_mutex_t *statmutex;

  numbufs = dim[0];
  len = dim[1];
  offset = dim[2];
  trim = dim[3];
  numextbufs = dim[4];

  numstatbufs = dim[5];
  lenstat = dim[6];
  pbuffer = (unsigned char **)arguments->buffer;
  for (i=0;i<numbufs;i++){
      *(pbuffer+i) = *((unsigned char **)(arguments->buffer)+i);
  }

  pstatbuffer = (unsigned char **)arguments->statbuffer;
  for (i=0;i<numstatbufs;i++){
      *(pstatbuffer+i) = *((unsigned char **)(arguments->statbuffer)+i);
  }

  pextbuffer = (unsigned char **)arguments->extbuffer;
  for (i=0;i<numextbufs;i++){
      *(pextbuffer+i) = *((unsigned char **)(arguments->extbuffer)+i);
  }
  threadcontrol = (int *)arguments->threadcontrol;

  extstatus = (int *)arguments->extstatus;

  newdata = (int *)arguments->newdata;

  newstat = (int *)arguments->newstat;

  mutex = (pthread_mutex_t *)arguments->mutex;

  extmutex = (pthread_mutex_t *)arguments->extmutex;

  statmutex = (pthread_mutex_t *)arguments->statmutex;

  threadexit = 0;
  i = 0;
  j = 0;
  count = 0;
  wcount = 0;

  ext_ind = 0;
  ext_buffer_empty = 1;


  device = (char *)arguments->devname;
  if(device == NULL)
      pcap_fatal("pcap_lookupdev", errbuf);

  printf("Sniffing on device %s\n", device);

  pcap_handle = pcap_open_live(device, 4096, 1, 1000, errbuf);
  if(pcap_handle == NULL)
      pcap_fatal("pcap_open_live", errbuf);

  int promisc_mode = threadcontrol[5];

  //pthread_mutex_lock(&extmutex[0]);

  threadcontrol[4] = 0;

  while (threadexit==0){
    if ((packet = pcap_next(pcap_handle, &header)) != NULL){
        if (header.caplen==len){
            pthread_mutex_lock(&mutex[i]);
            memcpy(pbuffer[i],packet+offset,header.caplen-offset-trim);
            newdata[i] = 1;
            pthread_mutex_unlock(&mutex[i]);

            if(ext_ind < numextbufs) {
                //memcpy(pextbuffer[ext_ind],packet+offset,header.caplen-offset-trim);
                memcpy(pextbuffer[ext_ind],packet,header.caplen);
                ext_ind++;
            }
            else if((ext_ind == numextbufs) & (ext_buffer_empty==1)){
                ext_buffer_empty = 0;
                pthread_mutex_lock(&extmutex[0]);
                extstatus[0] = ext_buffer_empty;
                pthread_mutex_unlock(&extmutex[0]);
            }
            else {
                pthread_mutex_lock(&extmutex[0]);
                ext_buffer_empty = extstatus[0];
                pthread_mutex_unlock(&extmutex[0]);
                if (ext_buffer_empty){
                    ext_ind = 0;
                }
            }

//            if(ext_ind < numextbufs) {
//                memcpy(pextbuffer[ext_ind],packet+offset,header.caplen-offset-trim);
//                ext_ind++;
//            }
//            else if((ext_ind == numextbufs) & (ext_buffer_empty==1)){
//                ext_buffer_empty = 0;
//                extstatus[0] = ext_buffer_empty;
//                pthread_mutex_unlock(&extmutex[0]);
//            }else {
//                pthread_mutex_lock(&extmutex[0]);
//                ext_buffer_empty = extstatus[0];
//                if (ext_buffer_empty){
//                    ext_ind = 0;
//                }
//                else {
//                    pthread_mutex_unlock(&extmutex[0]);
//                }
//            }
            i = (i+1)%numbufs;
            wcount++;
            threadcontrol[2] = wcount;
        }
        else if (header.caplen==lenstat){
        //else if (header.caplen>=lenstat){
            pthread_mutex_lock(&statmutex[j]);
           // memcpy(pstatbuffer[j],packet+offset,header.caplen-offset-trim);
           // memcpy(pstatbuffer[j],packet+offset,lenstat-offset-trim);
            memcpy(pstatbuffer[j],packet,lenstat);
            newstat[j] = 1;
            pthread_mutex_unlock(&statmutex[j]);
            j = (j+1)%numstatbufs;
        }
        else if (promisc_mode==1){
            int copylen = header.caplen;
            if (copylen>len) copylen = len;

            pthread_mutex_lock(&mutex[i]);
            memcpy(pbuffer[i],packet,copylen);
            newdata[i] = 1;
            pthread_mutex_unlock(&mutex[i]);

            if(ext_ind < numextbufs) {
                memcpy(pextbuffer[ext_ind],packet,copylen);
                ext_ind++;
                printf("%i ",ext_ind);
            }
            else if((ext_ind == numextbufs) & (ext_buffer_empty==1)){
                printf("done copying ext buf \n");
                ext_buffer_empty = 0;
                pthread_mutex_lock(&extmutex[0]);
                extstatus[0] = ext_buffer_empty;
                pthread_mutex_unlock(&extmutex[0]);
            }
            else {
                printf("check ext status \n");
                pthread_mutex_lock(&extmutex[0]);
                ext_buffer_empty = extstatus[0];
                pthread_mutex_unlock(&extmutex[0]);
                if (ext_buffer_empty){
                    printf("set ext int to 0 \n");
                    ext_ind = 0;
                }
            }

            i = (i+1)%numbufs;
            wcount++;
            threadcontrol[2] = wcount;
        }
        count++;
        threadcontrol[3] = count;
        promisc_mode = threadcontrol[5];
    }
    else {
      //printf("NULL pacap handle\n");
      usleep(1);
    }
    threadexit = threadcontrol[0];
  }
  threadcontrol[4] = 1;
  return NULL;
}
void *writeThread(void *args){
  int i;
  FILE *fp;
  int numbufs,len, offset, trim;
  int writecount,threadexit, writelim;
  int *dim, *threadcontrol, *newdata;
  char *filename;
  unsigned char **pbuffer;
  struct arg_struct *arguments = (struct arg_struct *)args;
  filename = (char *)arguments->filename;
  dim = (int *)arguments->dimensions;
  newdata = (int *)arguments->newdata;

  numbufs = dim[0];
  len = dim[1];
  offset = dim[2];
  trim = dim[3];

  pbuffer = (unsigned char **)arguments->buffer;
  for (i=0;i<numbufs;i++){
      *(pbuffer+i) = *((unsigned char **)(arguments->buffer)+i);
  }

  threadcontrol = (int *)arguments->threadcontrol;
  pthread_mutex_t *mutex, *file_mutex;
  mutex = (pthread_mutex_t *)arguments->mutex;
  file_mutex = (pthread_mutex_t *)arguments->extmutex;
  printf("Write Thread with file: %s\n",filename);


  fp = fopen(filename,"wb");

  writecount = 0;
  writelim = threadcontrol[1];
  threadexit = 0;

  threadcontrol[4] = 0;
  i = 0;
  //for(i=0;i<numbufs;i++) {
  while((threadexit==0)&&(writecount<writelim)){
      pthread_mutex_lock(&mutex[i]);
      //pbuffer[i] = *((unsigned char **)arguments->arg2 + i);

      // The following three statements are equivalent:

      //fwrite(pbuffer[i],sizeof(char),4*len,out);
      //fwrite(&pbuffer[i][0],sizeof(char),4*len,out);
      while (newdata[i]==0){
        if (threadcontrol[0]){
             break;
         }
        //printf("write data %i locked \n",i);
        pthread_mutex_unlock(&mutex[i]);
        usleep(1);
        pthread_mutex_lock(&mutex[i]);
      }
      if (newdata[i]){
      //fwrite( *((unsigned char **)arguments->buffer + i),sizeof(char),len-offset-trim,fp);
        pthread_mutex_lock(&file_mutex[0]);
        fwrite( pbuffer[i],sizeof(char),len-offset-trim,fp);
        pthread_mutex_unlock(&file_mutex[0]);
        writecount++;
      }
      newdata[i] = 0;
      pthread_mutex_unlock(&mutex[i]);
      threadexit = threadcontrol[0];
      threadcontrol[2] = writecount;
      i = (i+1)%numbufs;
  }

  fclose(fp);
  threadcontrol[4] = 1;
  return NULL;

}

void *extBufferThread(void *args){
    int i,ext_ind;
    int numbufs,numextbufs,len,offset,trim;
    int threadexit;
    int *dim, *threadcontrol, *extstatus;
    struct arg_struct *arguments = (struct arg_struct *)args;
    dim = (int *)arguments->dimensions;

    unsigned char **pextbuffer;

    pthread_mutex_t *extmutex;

    numbufs = dim[0];
    len = dim[1];
    offset = dim[2];
    trim = dim[3];
    numextbufs = dim[4];

    pextbuffer = (unsigned char **)arguments->extbuffer;
    for (i=0;i<numextbufs;i++){
        *(pextbuffer+i) = *((unsigned char **)(arguments->extbuffer)+i);
    }
    threadcontrol = (int *)arguments->threadcontrol;

    extstatus = (int *)arguments->extstatus;

    extmutex = (pthread_mutex_t *)arguments->extmutex;

    threadexit = 0;
    i = 0;

    ext_ind = 0;


   threadcontrol[4] = 0;
   while (threadexit==0){
       pthread_mutex_lock(&extmutex[0]);
       if(extstatus[0]==0){
           pthread_mutex_unlock(&extmutex[0]);
           usleep(1000);
           pthread_mutex_lock(&extmutex[0]);
           extstatus[0]=1;
       }
       pthread_mutex_unlock(&extmutex[0]);
       usleep(1000);
       threadexit = threadcontrol[0];

   }

  threadcontrol[4] = 1;
  return NULL;
}

