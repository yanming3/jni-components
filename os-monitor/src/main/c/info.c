//gcc -o collect collect.c -lrt -w

#include "info.h"

/*从/proc/stat文件中提取cpu数据状态*/
int get_cpu_info(cpuInfo *c)
{
    FILE *fd;
    char buff[256];
    char name[20];
    fd = fopen("/proc/stat", "r");
    if (!fd) {
        fclose(fd);
        perror("cannot open /proc/stat!");
        return 1;
    }

    while(fgets(buff, sizeof(buff), fd)) {
        if(strstr(buff, "cpu") != NULL) {
            sscanf(buff,"%s %Ld %Ld %Ld %Ld %Ld %Ld %Ld", name, &(c->user), &(c->nice), &(c->system), &(c->idle),&(c->iowait),&(c->irq),&(c->softirq));
            break;
        }
    }

    fclose(fd);
    return 0;
}

/*从 /proc/meminfo 文件中提取内存数据*/
int get_mem_info(memInfo *m)
{
    FILE *fd;
    char buff[256];

    char name[20];
    fd = fopen("/proc/meminfo", "r");
    if (!fd) {
        fclose(fd);
        perror("Cannot open /proc/meminfo!");
        return 1;
    }

    while(fgets(buff, sizeof(buff), fd)){
        if (strstr(buff, "MemTotal") != NULL) {
            sscanf(buff, "%s %u", name, &(m->total));
        }
        else if (strstr(buff, "MemFree") != NULL) {
            sscanf(buff, "%s %u", name, &(m->free));
        }
        else if (strstr(buff, "Buffers") != NULL) {
            sscanf(buff, "%s %u", name, &(m->buffers));
        }
        else if (strstr(buff, "Cached") != NULL) {
             sscanf(buff, "%s %u", name, &(m->cached));
        }
   }

    fclose(fd);
    return 0;
}

/*提取网口数据，计算丢包率*/
int get_net_info(netInfo *n)
{
    FILE *fd;
    int i = 0;
    n->len=0;
    char buff[256];

    unsigned long long r_bytes,r_packets,r_errs,r_drop,fifo,frame,compressed,multicast,t_bytes,t_packets,t_errs,t_drop;
    fd = fopen("/proc/net/dev", "r+");
    if (!fd) {
        fclose(fd);
        perror("Cannot open /proc/net/dev");
        return 1;
    }

    netInfo *cur=n;
    while(fgets(buff, sizeof(buff), fd)) {
        i++;
        if(i > 3) {
            char* name = (char*)malloc(20);
            sscanf(buff,"%s %Ld %Ld %Ld %Ld %Ld %Ld %Ld %Ld %Ld %Ld %Ld %Ld",
                name, &r_bytes, &r_packets,
                &r_errs, &r_drop, &fifo,
                &frame, &compressed, &multicast,
                &t_bytes, &t_packets, &t_errs,
                &t_drop);
            if(n->len>0){
                cur->next=(netInfo*)malloc(sizeof(netInfo));
                cur=cur->next;
            }
            cur->name=name;
            cur->r_bytes=r_bytes;
            cur->r_packets=r_packets;
            cur->r_errs=r_errs;
            cur->r_drop=r_drop;
            cur->fifo=fifo;
            cur->frame=frame;
            cur->compressed=compressed;
            cur->multicast=multicast;
            cur->t_bytes=t_bytes;
            cur->t_packets=t_packets;
            cur->t_errs=t_errs;
            cur->t_drop=t_drop;
            n->len+=1;
        }
    }

    cur->next=NULL;

    fclose(fd);
    return 0;
}

/*提取磁盘数据*/
int get_disk_info(diskInfo *d)
{
    //获取block大小
    struct stat fi;
    stat("/", &fi);
    int  blksize=fi.st_blksize/1024;

    FILE *fd;
    d->len=0;
    char buff[256];

    fd = fopen("/proc/mounts", "r+");
    if (!fd) {
        fclose(fd);
        perror("Cannot open /proc/mounts!");
        return 1;
    }

    /**
    Format of /proc/mounts

    The 1st column specifies the device that is mounted.
    The 2nd column reveals the mount point.
    The 3rd column tells the file-system type.
    The 4th column tells you if it is mounted read-only (ro) or read-write (rw).
    The 5th and 6th columns are dummy values designed to match the format used in /etc/mtab.
    **/

    diskInfo *cur=d;
    while(fgets(buff, sizeof(buff), fd)) {
            char* fs_name = (char*)malloc(50);
            char* mount_point = (char*)malloc(50);
            char* file_system = (char*)malloc(50);

            sscanf(buff,"%s %s %s",fs_name, mount_point,file_system);
            if((!strstr(file_system,"ext")&&!strstr(file_system,"tmpfs"))||strstr(file_system,"devtmpfs")){
                free(fs_name);
                free(mount_point);
                free(file_system);
                continue;
            }

            free(file_system);

            struct statfs sfs;
            if(statfs(mount_point, &sfs)){
               free(fs_name);
               free(mount_point);
               free(file_system);
               continue;
            }

            if(d->len>0){
                cur->next=(diskInfo*)malloc(sizeof(diskInfo));
                cur=cur->next;
            }
            int percent=(sfs.f_blocks - sfs.f_bfree ) * 100 / (sfs.f_blocks -sfs.f_bfree + sfs.f_bavail) + 1;
            unsigned long long size=blksize*sfs.f_blocks;
            unsigned long long used=blksize*(sfs.f_blocks - sfs.f_bfree);
            unsigned long long avail=blksize*sfs.f_bavail;
            cur->fs_name=fs_name;
            cur->mount_point=mount_point;
            cur->size=size;
            cur->used=used;
            cur->avail=avail;
            cur->percent=percent;
            d->len+=1;

    }

    cur->next=NULL;

    fclose(fd);
    return 0;
}

/**
void start_timer(void)
{
    struct sigevent se;
    struct itimerspec ts, ots;
    timer_t tid;

    memset(&se, 0, sizeof(se));
    se.sigev_notify = SIGEV_THREAD;
    se.sigev_notify_function = collect;//定时执行函数，获取运维数据
    se.sigev_value.sival_int = 0;
    if (timer_create(CLOCK_REALTIME, &se, &tid) < 0) {
        perror("timer_create of operation and maintenance\n");
    }
    ts.it_value.tv_sec = 28;
    ts.it_value.tv_nsec = 0;
    ts.it_interval = ts.it_value;
    if (timer_settime(tid, 0, &ts, &ots) < 0) {
        perror("time_settime of operation and maintenance\n");
    }
}
**/


int main()
{
   cpuInfo  *c=(cpuInfo*)malloc(sizeof(cpuInfo));
   memset(c, 0, sizeof(cpuInfo));
   get_cpu_info(c);
   printf("CPU:%Ld %Ld %Ld %Ld %Ld %Ld %Ld\n",c->user,c->nice,c->system,c->idle,c->iowait,c->irq,c->softirq);
   free(c);

   memInfo  *m=(memInfo*)malloc(sizeof(memInfo));
   memset(m, 0, sizeof(memInfo));
   get_mem_info(m);
   printf("MEM:total = %u ,free = %u\n",m->total,m->free);
   free(m);

   netInfo  *n=(netInfo*)malloc(sizeof(netInfo));
   memset(n, 0, sizeof(netInfo));
   get_net_info(n);
   netInfo *iter=n;
   while(iter){
        printf("NET:name = %s,r_bytes = %Ld,r_packets = %Ld,t_bytes = %Ld\n",iter->name,iter->r_bytes,iter->r_packets,iter->t_bytes);
        netInfo *tmp=iter;
        iter=iter->next;
        free(tmp->name);
        free(tmp);
   }


   diskInfo *d=(diskInfo*)malloc(sizeof(diskInfo));
   get_disk_info(d);
   diskInfo *cur=d;
   while(cur){
       printf("File System=%s,Size=%Ld,Used=%Ld,Avail=%Ld,Use=%d%%\n",cur->fs_name,cur->size,cur->used,cur->avail,cur->percent);
       diskInfo *tmp=cur;
       cur=cur->next;
       free(tmp->fs_name);
       free(tmp->mount_point);
       free(tmp);
   }
}
