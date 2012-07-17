#define _GNU_SOURCE /**/

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <poll.h>

#include <arpa/inet.h>
#include <netinet/icmp6.h>
#include <net/if.h>
#include <linux/rtnetlink.h>

#ifdef DEBUG
#define LOG(fmt, ...)       fprintf(stderr, fmt "\n", ##__VA_ARGS__)
#else
#define LOG(...)
#endif

void dump(const char* title, void* msg, int len);

#define HWADDR_MAX          16
#define MAX_PKT_BUFF        1500
#define MAX_MSG_SIZE        2048
#define INTERFACE_STRLEN    12
#define DISPATCH_TIMEOUT    300000          // milliseconds 300000 = 5 mins

struct slaac_handle
{
    int    nlfd;
    struct sockaddr_nl    local;
    struct sockaddr_nl    peer;
    __u32  seq;
    __u32  dump;
    int    icmp6fd;
    int    if_wan;
    int    if_lan;
};

// NETLINK related
int open_netlink_socket(struct slaac_handle *rth);
int neighor_addproxy(struct slaac_handle* rth, struct in6_addr* ip6);

// ICMPv6 related
int open_icmp_socket(struct slaac_handle* rth);
int process_icmp6(struct slaac_handle* rth, unsigned char *msg) 

//////////////////////////////
//# vim:ts=4
