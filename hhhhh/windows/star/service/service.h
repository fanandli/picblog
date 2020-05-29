#pragma once
#include "base.h"
#include "list.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

//svc name -> port must be transfered in starshell(starmonitor)
#define SERVICE_LANHOST_LEN 63
#define SERVICE_SVCNAME_SIZE 8

class service {
public:
  enum intermode { //access from internet
    PORTDIFF, //mean the intra port != inter port
    PORTSAME, //mean user wan't the intra port === inter port
  };

  list_head entry;
  Client* clt;
  char type[SERVICE_SVCNAME_SIZE];
  char host[NBS_HOSTNAME_SIZE];
  UINT16 intraport;
  UCHAR protocol;
  UCHAR mode; //intermode
  
  //below is fwdinfo
  struct {
    SockEx* fwdChnl;
    UINT32 interip;
    UINT16 interport;
    UINT16 transitport;
  };
  
  service(Client* clt, char*, char*, UINT16 port, UCHAR protocol, intermode omode = PORTDIFF);
  virtual ~service();
  int getPublicAddr(void* host, SOCKADDR_IN*);
  int RequestPublicAddr(void*);
  int updateTransitInfo(int family = 0);
  int notinuse();
  static service* get(char* domain, char* type);
};

//driver implent the proxy

#ifdef __cplusplus
}
#endif //__cplusplus