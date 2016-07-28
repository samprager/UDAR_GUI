#include "netinterface.h"
#include "udar_controller.h"


NetInterface::NetInterface()
{

}
NetInterface::NetInterface(QString name){
    if_name = name;
    memset(if_mac,0,sizeof(if_mac));
    memset(if_ip,0,sizeof(if_ip));
    has_mac = 0;
    has_ip = 0;
    has_status = 0;
    rx_thread_open = 0;
    wr_thread_open = 0;
}
NetInterface::NetInterface(UDAR_Controller *parent,QString name){
    parent_ui = parent;
    if_name = name;
    memset(if_mac,0,sizeof(if_mac));
    memset(if_ip,0,sizeof(if_ip));
    has_mac = 0;
    has_ip = 0;
    has_status = 0;
    rx_thread_open = 0;
    wr_thread_open = 0;
}

NetInterface::NetInterface(char *name){
    QString namestr = QString::fromUtf8(name);
    if_name = namestr;
    memset(if_mac,0,sizeof(if_mac));
    memset(if_ip,0,sizeof(if_ip));
    has_mac = 0;
    has_ip = 0;
    has_status = 0;
    rx_thread_open = 0;
    wr_thread_open = 0;
}
NetInterface::NetInterface(QString name, u_char mac[6]){
    if_name = name;
    memcpy(if_mac,mac,6);
    memset(if_ip,0,sizeof(if_ip));
    has_mac = 1;
    has_ip = 0;
    has_status = 0;
    rx_thread_open = 0;
    wr_thread_open = 0;
}
NetInterface::NetInterface(QString name, u_char mac[6], u_char ip[4]){
    if_name = name;
    memcpy(if_mac,mac,6);
    memcpy(if_ip,ip,4);
    has_mac = 1;
    has_ip = 1;
    has_status = 0;
    rx_thread_open = 0;
    wr_thread_open = 0;
}

NetInterface::NetInterface(QString name,QString status, u_char mac[6]){
    if_name = name;
    if_status = status;
    memcpy(if_mac,mac,6);
    memset(if_ip,0,sizeof(if_ip));
    has_mac = 1;
    has_ip = 0;
    has_status = 1;
    rx_thread_open = 0;
    wr_thread_open = 0;
}

NetInterface::NetInterface(QString name,QString status, u_char mac[6],u_char ip[4]){
    if_name = name;
    if_status = status;
    memcpy(if_mac,mac,6);
    memcpy(if_ip,ip,4);
    has_mac = 1;
    has_ip = 1;
    has_status = 1;
    rx_thread_open = 0;
    wr_thread_open = 0;
}

int NetInterface::initRxThreads(char fname[], char outdir[],int init_wr_thread, int writelim)
{
  pcap_t *pcap;
  FILE *fp,*fp_c,*fp_iq;
  const unsigned char *packet;
  char errbuf[PCAP_ERRBUF_SIZE];
  struct pcap_pkthdr header;
  int mode_select;    // 0: dump udp packet, 1: dump data at offset
  int offset = RX_HEADER_SIZE;
  int trim = 0;
  char *filename,*device;
  unsigned char *packet_data;
  uint32_t *counter = NULL;
  uint32_t *dataIQ = NULL;
  int count,wcount,datasize,p_datasize;

  char tempstr[STR_SIZE];
  int i,j,err;

  int len8 = RX_PKT_SIZE;   // buffer size in bytes
  int lenstat8 = RX_STAT_PKT_SIZE;
  int len32 = len8/4;
  int *dim;
  int **threadctrl;
  int *newdata;
  int *newstat;
  int *extstatus;

  numbufs = 1000;    // Number of row buffers
  numextbufs = 10;    // Number of row external buffers
  numstatbufs= 1;
  numthreads = 3;
  numextmutex = 1;

    //uint32_t buffer[numbufs][len];
  unsigned char ** pbuffer;
  unsigned char ** pextbuf;
  unsigned char ** pstatbuf;
  struct arg_struct *args;


pthread_mutex_t *mutex;
pthread_mutex_t *extmutex;
pthread_mutex_t *statmutex;
pthread_t *threads;

  clock_t t,end,overhead;

  if (rx_thread_open == 1){
      if ((wr_thread_open == 0) & (init_wr_thread==1)){
          rec_writelim = writelim;
          if (rec_writelim > RX_WRITE_LIM) rec_writelim = RX_WRITE_LIM;
         initWrThread();
         return 0;
      }
      else
        return 1;
  }



  filename = new char[sizeof(fname)+sizeof(outdir)];
  sprintf(filename,"%s%s",outdir,fname);
  device = this->GetNameString();

  extstatus = new int[2];

  extstatus[0] = 0;
  extstatus[1] = 0;

  dim = new int[7];
  dim[0] = numbufs;
  dim[1] = len8;

  dim[2] = offset;
  dim[3] = trim;

  dim[4] = numextbufs;
  dim[6] = numstatbufs;
  dim[7] = lenstat8;

  overhead = clock();
  overhead = clock()-overhead;
  t = clock();

    args = new arg_struct[numthreads];
    pbuffer = new unsigned char*[numbufs];
    pextbuf = new unsigned char*[numextbufs];
    pstatbuf = new unsigned char*[numstatbufs];
    threadctrl = new int*[numthreads];

  for (i=0;i<numbufs;i++) pbuffer[i] = new unsigned char[len8];
  for (i=0;i<numextbufs;i++) pextbuf[i] =new unsigned char[len8];
  for (i=0;i<numstatbufs;i++) pstatbuf[i] = new unsigned char[lenstat8];
  for(i=0;i<numthreads;i++) threadctrl[i] = new int[6];

  rec_writelim = writelim;
  if (rec_writelim > RX_WRITE_LIM) rec_writelim = RX_WRITE_LIM;

  for(i=0;i<numthreads;i++){
    threadctrl[i][0] = 0;
    threadctrl[i][1] = rec_writelim;
    threadctrl[i][2] = 0;
    threadctrl[i][3] = 0;
    threadctrl[i][4] = 0;
    threadctrl[i][5] = 0;
  }

  newdata = new int[numbufs];
  for (i=0;i<numbufs;i++) newdata[i] = 0;

  newstat = new int[numstatbufs];
  for (i=0;i<numstatbufs;i++) newstat[i] = 0;

 threads = new pthread_t[numthreads];

 // mutex = calloc(numbufs,sizeof(*mutex));
 mutex = new pthread_mutex_t[numbufs];

 extmutex = new pthread_mutex_t[numextmutex];

 statmutex = new pthread_mutex_t[numstatbufs];

  for (i=0;i<numbufs;i++){
      if(pthread_mutex_init(&mutex[i],NULL)!=0){
          printf("\nMutex %i init error",i);
          return -1;
      }
  }
  for (i=0;i<numextmutex;i++){
    if(pthread_mutex_init(&extmutex[i],NULL)!=0){
        printf("\nExtMutex %i init error",i);
        return -1;
    }
  }
  for (i=0;i<numstatbufs;i++){
    if(pthread_mutex_init(&statmutex[i],NULL)!=0){
        printf("\nExtMutex %i init error",i);
        return -1;
    }
  }

  for(i=0;i<numthreads;i++){
      args[i].mutex = (void *)mutex;
      args[i].extmutex = (void *)extmutex;
      args[i].statmutex = (void *)statmutex;
      args[i].dimensions = (void *)dim;
      args[i].threadcontrol = (void *)threadctrl[i];
      args[i].buffer = (void *)pbuffer;
      args[i].extbuffer = (void *)pextbuf;
      args[i].statbuffer = (void *)pstatbuf;
      args[i].devname = (void *)device;
      args[i].filename = (void *)filename;
      args[i].newdata = (void *)newdata;
      args[i].newstat = (void *)newstat;
      args[i].extstatus = (void *)extstatus;
  }

  rec_pbuffer = pbuffer;
  rec_pextbuf = pextbuf;
  rec_pstatbuf = pstatbuf;
  rec_mutex = mutex;
  rec_extmutex = extmutex;
  rec_statmutex = statmutex;
  rec_threads = threads;
  rec_threadctrl = threadctrl;
  rec_filename = filename;
  rec_device = device;
  rec_newdata = newdata;
  rec_newstat = newstat;
  rec_dim = dim;
  rec_extstatus= extstatus;
  rec_args = args;

 // Create Read Threads

  threadctrl[0][4] = 1;
  err = pthread_create(&threads[0],NULL,listenThread,(void *)&args[0]);
  if(err != 0) {
      printf("\nError initializing Read thread: %i\n",err);
      return -1;
  }
  while (threadctrl[0][4]!=0)
    usleep(1);

  rx_thread_open = 1;
  sprintf(tempstr,"Read Thread Initialized...Listening to %s",device);
  // parent_ui->setTranscript(tempstr);


  if (init_wr_thread) {
      // Create Write Thread
     err = initWrThread();
     if(err != 0) {
         printf("\nError initializing Write thread: %i\n",err);
         return -1;
     }
  }

  threadctrl[2][4] = 1;
  err = pthread_create(&threads[2],NULL,extBufferThread,(void *)&args[2]);
  if(err != 0) {
      printf("\nError initializing Ext Buffer thread: %i\n",err);
      return -1;
  }
  while (threadctrl[2][4]!=0)
    usleep(1);


  return 0;

}

void NetInterface::setPromiscMode(int value){
    if (rx_thread_open){
        if (value == 0)
            rec_threadctrl[0][5] = 0;
        else
            rec_threadctrl[0][5] = 1;
    }
}

int NetInterface::initWrThread(){
    int i,err;
    char tempstr[STR_SIZE];

    if (rx_thread_open == 0){
        // parent_ui->setTranscript("Read thread must be open to launch write thread");
        return 1;
     }
    if (wr_thread_open == 1){
        // parent_ui->setTranscript("Write thread already open");
        return 1;
     }
    // Create Write Thread
    //err = pthread_create(&threads[2],NULL,writethread,(void *)&args[2]);
    struct arg_struct *args = rec_args;
    pthread_t *threads = rec_threads;
    int **threadctrl = rec_threadctrl;
    char *filename = rec_filename;

    threadctrl[1][1] = rec_writelim;

    threadctrl[1][4] = 1;
    err = pthread_create(&threads[1],NULL,writeThread,(void *)&args[1]);
    if(err != 0) {
        printf("\nError initializing Write thread: %i\n",err);
        return -1;
    }
    while (threadctrl[1][4]!=0)
      usleep(1);

    wr_thread_open = 1;

    sprintf(tempstr,"Write Thread Initialized...Writing to %s",filename);
    // parent_ui->setTranscript(tempstr);
    sprintf(tempstr,"Write Limit set at %i packets",rec_writelim);
    // parent_ui->setTranscript(tempstr);



    return 0;
}

QString NetInterface::GetThreadStatus(){
    QString qstr;
    char tempstr[128];
    int err;
    if (rx_thread_open == 0){
        thread_status ="["+ if_name + "," +if_status + "] Read thread Not Open";
        //return qstr;
    }
    else if (wr_thread_open == 0){
        sprintf(tempstr,"read: %i/%i, written (inactive): %i",rec_threadctrl[0][2],rec_threadctrl[0][3],0);
        thread_status = "["+ if_name + "," +if_status + "] " + QString::fromLatin1(tempstr);
        //return qstr;
    }
    else if (rec_threadctrl[1][2] < RX_WRITE_LIM) {
        char tempstr[128];
        sprintf(tempstr,"read: %i/%i, written: %i",rec_threadctrl[0][2],rec_threadctrl[0][3],rec_threadctrl[1][2]);
        thread_status = "["+ if_name + "," +if_status + "] " + QString::fromLatin1(tempstr);
    }
    else {
       err = KillThreads();
       thread_status = "["+ if_name + "," +if_status + "] " + "Write Limit Exceeded...Killing threads";
    }
    return thread_status;
}

int NetInterface::IsListening(){
    return rx_thread_open;
}
int NetInterface::IsRecording(){
    return wr_thread_open;
}

int NetInterface::PrintExtBuffer(int offset){
    u_char pktsample[RX_PKT_SIZE];
    if (rx_thread_open == 0){
        // parent_ui->setTranscript("Read thread Not Open");
        return 1;
    }
    // parent_ui->setTranscript("Locking Mutex...");
    pthread_mutex_lock(&rec_extmutex[0]);
    if (rec_extstatus[0]==1) {
        pthread_mutex_unlock(&rec_extmutex[0]);
        memcpy(pktsample,rec_pextbuf[0]+offset,RX_PKT_SIZE-offset);
        // parent_ui->setTranscript(pktsample,RX_PKT_SIZE-offset);
    }
    else {
        pthread_mutex_unlock(&rec_extmutex[0]);
        // parent_ui->setTranscript("Ext Buffer Empty");
    }
    return 0;
}


int NetInterface::GetStatBufferSize(){
    return RX_STAT_PKT_SIZE;
}

int NetInterface::GetStatBuffer(unsigned char **statbuffer, int offset){
    if (rx_thread_open == 0){
        // parent_ui->setTranscript("Read thread Not Open");
        return -1;
    }
    // parent_ui->setTranscript("Locking Mutex...");
    pthread_mutex_lock(&rec_statmutex[0]);
    if (rec_newstat[0]==1) {
        memcpy(*statbuffer,rec_pextbuf[0]+offset,RX_STAT_PKT_SIZE-offset);
        rec_newstat[0]==0;
        // parent_ui->setTranscript(pktsample,RX_PKT_SIZE-offset);
        pthread_mutex_unlock(&rec_statmutex[0]);
        return RX_STAT_PKT_SIZE-offset;
    }
    else {
        pthread_mutex_unlock(&rec_statmutex[0]);
        // parent_ui->setTranscript("Ext Buffer Empty");
        return 0;
    }
}

int NetInterface::KillThreads(){
    char tempstr[128];
    int i,err;

    if (wr_thread_open == 0){
        // parent_ui->setTranscript("Write Thread Not Open");
    }
    else {
        rec_threadctrl[1][0] = 1;
        usleep(10);
        if (rec_threadctrl[1][4] == 1){
            // parent_ui->setTranscript("Write Thread Killed");
        }
        else {
            // parent_ui->setTranscript("Joining Write thread...");
            err = pthread_join(rec_threads[1],NULL);
            if(err != 0) {
                sprintf(tempstr,"\nError joining Write thread: %i\n",err);
                // parent_ui->setTranscript(tempstr);
                return err;
            }
        }
       wr_thread_open = 0;
    }

   if (rx_thread_open == 0){
           // parent_ui->setTranscript("Read Thread Not Open");
           return 0;
    }
   else {
       rec_threadctrl[2][0] = 1;
       usleep(10);
       if (rec_threadctrl[2][4] == 1){
           // parent_ui->setTranscript("Ext Buf Thread Killed");
       }
       else{
           // parent_ui->setTranscript("Joining Ext Buf thread...");
           err = pthread_join(rec_threads[2],NULL);
           if(err != 0) {
               sprintf(tempstr,"\nError joining Ext Buf thread: %i\n",err);
               // parent_ui->setTranscript(tempstr);
               return err;
           }
       }

       rec_threadctrl[0][0] = 1;
       usleep(10);
       if (rec_threadctrl[0][4] == 1){
           // parent_ui->setTranscript("Read Thread Killed");
       }
       else{
           // parent_ui->setTranscript("Joining Read thread...");
           err = pthread_join(rec_threads[0],NULL);
           if(err != 0) {
               sprintf(tempstr,"\nError joining Read thread: %i\n",err);
               // parent_ui->setTranscript(tempstr);
               return err;
           }
       }
       rx_thread_open = 0;

       sprintf(tempstr,"Succeuslly exited threads. read: %i/%i, written: %i",rec_threadctrl[0][2],rec_threadctrl[0][3],rec_threadctrl[1][2]);
       // parent_ui->setTranscript(tempstr);

       delete[] rec_dim;
       delete[] rec_extstatus;
       delete[] rec_newdata;
       delete[] rec_newstat;
      // delete [] rec_filename;
       delete [] rec_device;
       for (i=0;i<numbufs;i++) delete[] rec_pbuffer[i];
       for (i=0;i<numextbufs;i++) delete[] rec_pextbuf[i];
       for (i=0;i<numstatbufs;i++) delete[] rec_pstatbuf[i];
       for (i=0;i<numthreads;i++) delete[] rec_threadctrl[i];
       for (i=0;i<numbufs;i++) pthread_mutex_destroy(&rec_mutex[i]);
       for (i=0;i<numextmutex;i++) pthread_mutex_destroy(&rec_extmutex[i]);
       for (i=0;i<numstatbufs;i++) pthread_mutex_destroy(&rec_statmutex[i]);
       delete[] rec_pbuffer;
       delete[] rec_pextbuf;
       delete[] rec_pstatbuf;
       delete[] rec_threadctrl;
       delete[] rec_threads;
       delete[] rec_mutex;
       delete[] rec_extmutex;
       delete[] rec_statmutex;
       delete[] rec_args;

    }

   return 0;
}


u_char * NetInterface::GetMac(){
        u_char *tmp = new u_char[6];
        memcpy(tmp,if_mac,6);
        return tmp;

}

QString NetInterface::GetMacString(){
    QString tmpqstr;
        char formatstr[128];
        sprintf(formatstr,"%02x:%02x:%02x:%02x:%02x:%02x",if_mac[0],if_mac[1],if_mac[2],if_mac[3],if_mac[4],if_mac[5]);
        tmpqstr = QString::fromLatin1(formatstr);
    return tmpqstr;
}


QString NetInterface::GetName(){
    return if_name;
}

char * NetInterface::GetNameString(){
    //QByteArray ba = if_name.toLatin1();
    //char* name_str = ba.data();
    char* name_str = new char[sizeof(if_name.toLatin1().data())];
    strcpy(name_str,if_name.toLatin1().data());
    return name_str;
}

QString NetInterface::GetStatus(){
    QString tmpqstr;
    if (has_status == 1)
        tmpqstr = if_status;
    return tmpqstr;
}

QString NetInterface::GetIpString(){
    QString tmpqstr;
        char formatstr[128];
        sprintf(formatstr,"%d.%d.%d.%d",if_ip[0],if_ip[1],if_ip[2],if_ip[3]);
        tmpqstr = QString::fromLatin1(formatstr);

    return tmpqstr;
}

u_char *NetInterface::GetIp(){
        u_char *tmp = new u_char[4];
        memcpy(tmp,if_ip,4);
        return tmp;
}

void NetInterface::setMac(QString mac){
}

void NetInterface::setMac(u_char mac[6]){
    int i;
    for (i=0;i<6;i++){
        if_mac[i] = mac[i];
    }
    has_mac = 1;
}

void NetInterface::setIp(QString ip){

}

void NetInterface::setIp(u_char ip[4]){
    int i;
    for (i=0;i<4;i++){
        if_ip[i] = ip[i];
    }
    has_ip = 1;
}

void NetInterface::setStatus(QString status){
    if_status = status;
    has_status = 1;
}

void NetInterface::setStatus(char *status){
    QString statstr = QString::fromUtf8(status);
    if_status = statstr;
    has_status = 1;
}
