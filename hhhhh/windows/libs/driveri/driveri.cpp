#include <memory.h>
#include <vector>
#include <map>
#include<winSock2.h>
#pragma comment(lib, "ws2_32.lib")
#include "base.h"

#include "json-c/json.h"
#include "unidef.h"
#include "sockex.h"
#include "driver_inner.h"
#include "tlv.h"


struct portinfo {
  SOCKET listen;
  in_addr localip;
  in_addr rmtip;
  in6_addr localip6;
  in6_addr rmtip6;
  UINT16 rmtport;
  //char type;
};

/*
WORD wdVersion = MAKEWORD(2, 2);
WSADATA wdSockMsg;

int nres = WSAStartup(wdVersion, &wdSockMsg);
*/




//�����������һ������ͨ����win socket    tcp


class SockExListen :public SockEx {
public:
    void* extra;
    SockExListen(SOCKET s, SOCKADDR* addr, socklen_t len) :SockEx(true) {
        //����Ĺ��캯������ȥbind 
        if (bind(s, addr, len) == SOCKET_ERROR) {
            throw std::logic_error("bind error");
        }

        //Ȼ��ȥlisten
        if (listen(s, SOMAXCONN) == SOCKET_ERROR) {
            throw std::logic_error("listen error");
        }

        //struct epoll_event _ev = { EPOLLIN, {ptr:this} }; //EPOLLRDHUP event no receive, so delete the EPOLLRDHUP subscribe;
        //epoll_ctl(epsock, EPOLL_CTL_ADD, s, &_ev);
    };
    virtual ~SockExListen() {};

   /* int procSock(__uint32_t events) {
        SOCKET sockaccept = accept(sock, NULL, NULL);
        if (sockaccept == -1) {
            LOG("ERR: sock listen accept err:%d", errno);
            return 0;
        }

        TTCP* tcp = new TTCP(sockaccept, extra);
        tcp->onConnect();

        return 0;
    };*/
}; 


//��Զ�̷������3389����Ϣ��ͨ������ͨ�������͸�������
//�������յ�����ϢҲͨ������ͨ���������ң�����ת����3389



#define DRIVERI_FWD_THREADS 4
#define DRIVERI_IPTABLE_COMMENT "starfwd"
class SoftFwder {
public:
  int eplisten;
  int epfwd[DRIVERI_FWD_THREADS];
  portinfo portinfos[65536];
  SOCKET fwdmapping[65536];

  static void* acceptRoutine(void* threadinfo);
  static void* fwdRoutine(void* threadinfo);

  SoftFwder() {
    
  }

  int updatefwdinfo(SOCKADDR* xaddr, UINT32 type, SOCKADDR* downAddr, SockEx* xtunnel, SOCKADDR_IN* upAddr) {
    return 0;
  }
}*fwder;

void* SoftFwder::acceptRoutine(void* threadinfo) {
  return nullptr;
}

#define DRIVERI_FWDER_RCVBUF_LEN 4096
void* SoftFwder::fwdRoutine(void* threadinfo) {
  return nullptr;
}

//ȫ�ֱ�����ͬһ���ļ��ж��壬�����Ⱥ�˳���ʼ����ȫ�ֱ���������ǰ��ʼ��������driveri����ȫ�������ȫ�ֱ����ǿ��е�
driveri::driveri() {
  fwder = new SoftFwder();
}

UINT16 driveri::updateFwdInfo(SOCKADDR* addr, UINT32 type, SOCKADDR* downAddr, SockEx* xtunnel, SOCKADDR_IN* upAddr) {
  return fwder->updatefwdinfo(addr, type, downAddr, xtunnel, upAddr);
}

driveri::~driveri() {
  delete fwder;
}

/*
https://www.cnblogs.com/lidabo/p/5344899.html
get the default gateway, then get the ip address on the interface
*/
UINT32 driveri::GetGateWayAndIfIP(char* ifname, UINT32 *sip) {
  return 0;
}

void driveri::getIfMac(char* ifName, char* mac) {
  mac[0] = 0xB4;
  mac[1] = 0x2E;
  mac[2] = 0x99;
  mac[3] = 0x18;
  mac[4] = 0xE8;
  mac[5] = 0xB5;
}

UINT32 driveri::getIfIP(char* ifname) {
  return 0;
}

void driveri::getArp(UINT32 ip, const char* dev, char* arp) {

}

void driveri::sendtcp6(sockaddr_in6* src, sockaddr_in6* dst) {

}
