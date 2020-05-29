#pragma once

#include "unidef.h"
enum NBSDRV_PORTTYPE {
  DRIVERI_NORMAL = 0,
  DRIVERI_TUNNEL,
  DRIVERI_SVCSTART,
  DRIVERI_SVCTRANSIT,
  DRIVERI_SVCEND,
  DRIVERI_MAX
};

struct driveri {
#ifdef __cplusplus
  /*
  type=DRIVERI_TRANSIT：如果addr->port == 0, 说明要分配transitport；
  */    
    static UINT16 updateFwdInfo(SOCKADDR* addr, UINT32 type = DRIVERI_NORMAL, SOCKADDR* rmtAddr = nullptr, SockEx* tunnel = nullptr, SOCKADDR_IN* upAddr = nullptr);
    driveri();
    virtual ~driveri();
    static UINT32 GetGateWayAndIfIP(char*, UINT32*);
    static void getIfMac(char*, char*);
    static void getArp(UINT32 cltip, const char*, char*);
    static UINT32 getIfIP(char*);
    static void sendtcp6(sockaddr_in6* src, sockaddr_in6* dst);
#endif // __CPLUSPLUS
};
