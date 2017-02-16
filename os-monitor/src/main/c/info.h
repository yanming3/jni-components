#ifndef STATS_INFO_H_
#define STATS_INFO_H_


#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <unistd.h>
#include <string.h>
#include <sys/vfs.h>
#include <sys/stat.h>
#include <time.h>
#include <signal.h>
#include <pthread.h>


typedef struct cpuInfo                       //存放cpu数据结构体
{
    unsigned long long user;
    unsigned long long nice;
    unsigned long long system;
    unsigned long long idle;
    unsigned long long iowait;
    unsigned long long irq;
    unsigned long long softirq;
}cpuInfo;

typedef struct memInfo                   //存放内存数据结构体
{
    unsigned int total;
    unsigned int free;
    unsigned int buffers;
    unsigned int cached;
}memInfo;

typedef struct netInfo                  //存放网口数据结构体
{
    char *name;
    struct netInfo *next;
    unsigned int len;
    unsigned long long r_bytes;
    unsigned long long r_packets;
    unsigned long long r_errs;
    unsigned long long r_drop;
    unsigned long long fifo;
    unsigned long long frame;
    unsigned long long compressed;
    unsigned long long multicast;
    unsigned long long t_bytes;
    unsigned long long t_packets;
    unsigned long long t_errs;
    unsigned long long t_drop;
}netInfo;

typedef struct diskInfo                  //存放网口数据结构体
{
    char *fs_name;
    char *mount_point;
    struct diskInfo *next;
    unsigned int len;
    unsigned long long size;
    unsigned long long used;
    unsigned long long avail;
    unsigned int percent;
}diskInfo;

int get_cpu_info(cpuInfo *c);
int get_mem_info(memInfo *m);
int get_net_info(netInfo *n);
int get_disk_info(diskInfo *d);

#endif