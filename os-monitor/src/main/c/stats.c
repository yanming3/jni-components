//gcc -o collect collect.c -lrt -w
#include <stdio.h>
#include <stdlib.h>
#include <jni.h>
#include <unistd.h>
#include <string.h>

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


int get_cpu_info(cpuInfo *c);
int get_mem_info(memInfo *m);
int get_net_info(netInfo *n);



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


static jobject stats_get_cpu_ifo(JNIEnv* env, jclass clazz) {
    jclass cpu_cls=(*env)->FindClass(env,"com/yam/os/CpuInfo");
    if(cpu_cls==NULL)return NULL;

    jmethodID cpu_construct=(*env)->GetMethodID(env,cpu_cls,"<init>","()V");
    jobject cpu_obj=(*env)->NewObject(env,cpu_cls,cpu_construct);

    jfieldID userFieldId=(*env)->GetFieldID(env,cpu_cls,"user","J");
    jfieldID niceFieldId=(*env)->GetFieldID(env,cpu_cls,"nice","J");
    jfieldID systemFieldId=(*env)->GetFieldID(env,cpu_cls,"system","J");
    jfieldID idleFieldId=(*env)->GetFieldID(env,cpu_cls,"idle","J");
    jfieldID iowait=(*env)->GetFieldID(env,cpu_cls,"iowait","J");
    jfieldID irqFieldId=(*env)->GetFieldID(env,cpu_cls,"irq","J");
    jfieldID softirqFieldId=(*env)->GetFieldID(env,cpu_cls,"softirq","J");

    cpuInfo  *c=(cpuInfo*)malloc(sizeof(cpuInfo));
    memset(c, 0, sizeof(cpuInfo));
    get_cpu_info(c);
    (*env)->SetLongField(env,cpu_obj,userFieldId,c->user);
    (*env)->SetLongField(env,cpu_obj,niceFieldId,c->nice);
    (*env)->SetLongField(env,cpu_obj,systemFieldId,c->system);
    (*env)->SetLongField(env,cpu_obj,idleFieldId,c->idle);
    (*env)->SetLongField(env,cpu_obj,iowait,c->iowait);
    (*env)->SetLongField(env,cpu_obj,irqFieldId,c->irq);
    (*env)->SetLongField(env,cpu_obj,softirqFieldId,c->softirq);
    free(c);
    return cpu_obj;
}

static jobject stats_get_mem_ifo(JNIEnv* env, jclass clazz) {
    jclass mem_cls=(*env)->FindClass(env,"com/yam/os/MemInfo");
    if(mem_cls==NULL)return NULL;

    jmethodID mem_construct=(*env)->GetMethodID(env,mem_cls,"<init>","()V");
    jobject mem_obj=(*env)->NewObject(env,mem_cls,mem_construct);

    jfieldID totalFieldId=(*env)->GetFieldID(env,mem_cls,"total","I");
    jfieldID freeFieldId=(*env)->GetFieldID(env,mem_cls,"free","I");
    jfieldID buffersFieldId=(*env)->GetFieldID(env,mem_cls,"buffers","I");
    jfieldID cachedFieldId=(*env)->GetFieldID(env,mem_cls,"cached","I");

    memInfo  *m=(memInfo*)malloc(sizeof(memInfo));
    memset(m, 0, sizeof(memInfo));
    get_mem_info(m);

    (*env)->SetIntField(env,mem_obj,totalFieldId,m->total);
    (*env)->SetIntField(env,mem_obj,freeFieldId,m->free);
    (*env)->SetIntField(env,mem_obj,buffersFieldId,m->buffers);
    (*env)->SetIntField(env,mem_obj,cachedFieldId,m->cached);
    free(m);
    return mem_obj;
}

static jobject stats_get_net_ifo(JNIEnv* env, jclass clazz) {
    jclass list_cls = (*env)->FindClass(env,"java/util/ArrayList");//获得ArrayList类引用

    if(list_cls == NULL)
    {
        printf("listcls is null \n");
        return NULL;
    }
    jmethodID list_costruct = (*env)->GetMethodID(env,list_cls , "<init>","()V"); //获得得构造函数Id

    jobject list_obj = (*env)->NewObject(env,list_cls , list_costruct); //创建一个Arraylist集合对象
    //或得Arraylist类中的 add()方法ID，其方法原型为： boolean add(Object object) ;
    jmethodID list_add  = (*env)->GetMethodID(env,list_cls,"add","(Ljava/lang/Object;)Z");

    jclass net_cls = (*env)->FindClass(env,"com/yam/os/NetInfo");//获得NetInfo类引用
    //获得该类型的构造函数  函数名为 <init> 返回类型必须为 void 即 V
    jmethodID net_costruct = (*env)->GetMethodID(env,net_cls , "<init>", "()V");
    jfieldID  nameFieldId = (*env)->GetFieldID(env,net_cls , "name" , "Ljava/lang/String;"); //获得属性句柄
    jfieldID  rBytesFieldId = (*env)->GetFieldID(env,net_cls , "rBytes" , "J;"); //获得属性句柄
    jfieldID  rPacketsFieldId = (*env)->GetFieldID(env,net_cls , "rPackets" , "J;"); //获得属性句柄
    jfieldID  rErrsFieldId = (*env)->GetFieldID(env,net_cls , "rErrs" , "J;"); //获得属性句柄
    jfieldID  rDropFieldId = (*env)->GetFieldID(env,net_cls , "rDrop" , "J;"); //获得属性句柄
    jfieldID  fifoFieldId = (*env)->GetFieldID(env,net_cls , "fifo" , "J;"); //获得属性句柄
    jfieldID  frameFieldId = (*env)->GetFieldID(env,net_cls , "frame" , "J;"); //获得属性句柄
    jfieldID  compressedFieldId = (*env)->GetFieldID(env,net_cls , "compressed" , "J;"); //获得属性句柄
    jfieldID  multicastFieldId = (*env)->GetFieldID(env,net_cls , "multicast" , "J;"); //获得属性句柄
    jfieldID  tBytesFieldId = (*env)->GetFieldID(env,net_cls , "tBytes" , "J;"); //获得属性句柄
    jfieldID  tPacketsFieldId = (*env)->GetFieldID(env,net_cls , "tPackets" , "J;"); //获得属性句柄
    jfieldID  tErrsFieldId = (*env)->GetFieldID(env,net_cls , "tErrs" , "J;"); //获得属性句柄
    jfieldID  tDropFieldId = (*env)->GetFieldID(env,net_cls , "tDrop" , "J;"); //获得属性句柄

    netInfo  *n=(netInfo*)malloc(sizeof(netInfo));
    memset(n, 0, sizeof(netInfo));
    get_net_info(n);

   netInfo *iter=n;
   while(iter){
        jobject net_obj = (*env)->NewObject(env,net_cls , net_costruct);  //构造一个对象

        jstring name=(*env)->NewStringUTF(env,iter->name);
        (*env)->SetObjectField(env,net_obj , nameFieldId , name); // 设置该字段的值
        (*env)->SetLongField(env,net_obj , rBytesFieldId , iter->r_bytes); // 设置该字段的值
        (*env)->SetLongField(env,net_obj , rPacketsFieldId , iter->r_packets); // 设置该字段的值
        (*env)->SetLongField(env,net_obj , rErrsFieldId , iter->r_errs); // 设置该字段的值
        (*env)->SetLongField(env,net_obj , rDropFieldId , iter->r_drop); // 设置该字段的值
        (*env)->SetLongField(env,net_obj , fifoFieldId , iter->fifo); // 设置该字段的值
        (*env)->SetLongField(env,net_obj , frameFieldId , iter->frame); // 设置该字段的值
        (*env)->SetLongField(env,net_obj , compressedFieldId , iter->compressed); // 设置该字段的值
        (*env)->SetLongField(env,net_obj , multicastFieldId , iter->multicast); // 设置该字段的值
        (*env)->SetLongField(env,net_obj , tBytesFieldId , iter->t_bytes); // 设置该字段的值
        (*env)->SetLongField(env,net_obj , tPacketsFieldId , iter->t_packets); // 设置该字段的值
        (*env)->SetLongField(env,net_obj , tErrsFieldId , iter->t_errs); // 设置该字段的值
        (*env)->SetLongField(env,net_obj , tDropFieldId , iter->t_drop); // 设置该字段的值
        (*env)->CallBooleanMethod(env,list_obj , list_add , net_obj); //执行Arraylist类实例的add方法，添加一个netInfo对象
        netInfo *tmp=iter;
        iter=iter->next;
        free(tmp->name);
        free(tmp);
   }

    return list_obj ;
}


static JNINativeMethod methods[] = {
    {"getCpuInfo",    "()Lcom/yam/os/CpuInfo;",               (void *)&stats_get_cpu_ifo},
    {"getMemInfo",    "()Lcom/yam/os/MemInfo;",               (void *)&stats_get_mem_ifo},
    {"getNetInfo",    "()Ljava/util/List;",                   (void *)&stats_get_net_ifo}
};


jint JNI_OnLoad(JavaVM* vm, void* reserved) {
       JNIEnv* env;
       if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_6) != JNI_OK) {
               return JNI_ERR;
       }
       jclass cls = (*env)->FindClass(env, "com/yam/os/OsStats");
       printf("find class!");
       (*env)->RegisterNatives(env, cls, methods, sizeof(methods)/sizeof(methods[0]));
       printf("finish register");
       return JNI_VERSION_1_6;
}
/**
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
        iter=iter->next;
   }
   free(n);
}
**/