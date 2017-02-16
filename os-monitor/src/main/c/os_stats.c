#include "info.h"
#include "util.h"

static jobject stats_get_cpu_ifo(JNIEnv *env, jclass clazz) {
  jclass cpu_cls = (*env)->FindClass(env, "com/yam/os/CpuInfo");
  if (cpu_cls == NULL) return NULL;

  jmethodID cpu_construct = (*env)->GetMethodID(env, cpu_cls, "<init>", "()V");
  jobject cpu_obj = (*env)->NewObject(env, cpu_cls, cpu_construct);

  jfieldID userFieldId = (*env)->GetFieldID(env, cpu_cls, "user", "J");
  jfieldID niceFieldId = (*env)->GetFieldID(env, cpu_cls, "nice", "J");
  jfieldID systemFieldId = (*env)->GetFieldID(env, cpu_cls, "system", "J");
  jfieldID idleFieldId = (*env)->GetFieldID(env, cpu_cls, "idle", "J");
  jfieldID iowait = (*env)->GetFieldID(env, cpu_cls, "iowait", "J");
  jfieldID irqFieldId = (*env)->GetFieldID(env, cpu_cls, "irq", "J");
  jfieldID softirqFieldId = (*env)->GetFieldID(env, cpu_cls, "softirq", "J");

  cpuInfo *c = (cpuInfo *)malloc(sizeof(cpuInfo));
  memset(c, 0, sizeof(cpuInfo));
  get_cpu_info(c);
  (*env)->SetLongField(env, cpu_obj, userFieldId, c->user);
  (*env)->SetLongField(env, cpu_obj, niceFieldId, c->nice);
  (*env)->SetLongField(env, cpu_obj, systemFieldId, c->system);
  (*env)->SetLongField(env, cpu_obj, idleFieldId, c->idle);
  (*env)->SetLongField(env, cpu_obj, iowait, c->iowait);
  (*env)->SetLongField(env, cpu_obj, irqFieldId, c->irq);
  (*env)->SetLongField(env, cpu_obj, softirqFieldId, c->softirq);
  free(c);
  return cpu_obj;
}

static jobject stats_get_mem_ifo(JNIEnv *env, jclass clazz) {
  jclass mem_cls = (*env)->FindClass(env, "com/yam/os/MemInfo");
  if (mem_cls == NULL) return NULL;

  jmethodID mem_construct = (*env)->GetMethodID(env, mem_cls, "<init>", "()V");
  jobject mem_obj = (*env)->NewObject(env, mem_cls, mem_construct);

  jfieldID totalFieldId = (*env)->GetFieldID(env, mem_cls, "total", "I");
  jfieldID freeFieldId = (*env)->GetFieldID(env, mem_cls, "free", "I");
  jfieldID buffersFieldId = (*env)->GetFieldID(env, mem_cls, "buffers", "I");
  jfieldID cachedFieldId = (*env)->GetFieldID(env, mem_cls, "cached", "I");

  memInfo *m = (memInfo *)malloc(sizeof(memInfo));
  memset(m, 0, sizeof(memInfo));
  get_mem_info(m);

  (*env)->SetIntField(env, mem_obj, totalFieldId, m->total);
  (*env)->SetIntField(env, mem_obj, freeFieldId, m->free);
  (*env)->SetIntField(env, mem_obj, buffersFieldId, m->buffers);
  (*env)->SetIntField(env, mem_obj, cachedFieldId, m->cached);
  free(m);
  return mem_obj;
}

static jobject stats_get_net_ifo(JNIEnv *env, jclass clazz) {
  jobject list_obj = stats_util_createList(env);  //创建一个Arraylist集合对象
  //或得Arraylist类中的 add()方法ID，其方法原型为： boolean add(Object object) ;
  jmethodID list_add = stats_util_add_method(env);

  jclass net_cls =
      (*env)->FindClass(env, "com/yam/os/NetInfo");  //获得NetInfo类引用
  //获得该类型的构造函数  函数名为 <init> 返回类型必须为 void 即 V
  jmethodID net_costruct = (*env)->GetMethodID(env, net_cls, "<init>", "()V");
  jfieldID nameFieldId = (*env)->GetFieldID(
      env, net_cls, "name", "Ljava/lang/String;");  //获得属性句柄
  jfieldID rBytesFieldId =
      (*env)->GetFieldID(env, net_cls, "rbytes", "J");  //获得属性句柄
  jfieldID rPacketsFieldId =
      (*env)->GetFieldID(env, net_cls, "rpackets", "J");  //获得属性句柄
  jfieldID rErrsFieldId =
      (*env)->GetFieldID(env, net_cls, "rerrs", "J");  //获得属性句柄
  jfieldID rDropFieldId =
      (*env)->GetFieldID(env, net_cls, "rdrop", "J");  //获得属性句柄
  jfieldID fifoFieldId =
      (*env)->GetFieldID(env, net_cls, "fifo", "J");  //获得属性句柄
  jfieldID frameFieldId =
      (*env)->GetFieldID(env, net_cls, "frame", "J");  //获得属性句柄
  jfieldID compressedFieldId =
      (*env)->GetFieldID(env, net_cls, "compressed", "J");  //获得属性句柄
  jfieldID multicastFieldId =
      (*env)->GetFieldID(env, net_cls, "multicast", "J");  //获得属性句柄
  jfieldID tBytesFieldId =
      (*env)->GetFieldID(env, net_cls, "tbytes", "J");  //获得属性句柄
  jfieldID tPacketsFieldId =
      (*env)->GetFieldID(env, net_cls, "tpackets", "J");  //获得属性句柄
  jfieldID tErrsFieldId =
      (*env)->GetFieldID(env, net_cls, "terrs", "J");  //获得属性句柄
  jfieldID tDropFieldId =
      (*env)->GetFieldID(env, net_cls, "tdrop", "J");  //获得属性句柄

  netInfo *n = (netInfo *)malloc(sizeof(netInfo));
  memset(n, 0, sizeof(netInfo));
  get_net_info(n);

  netInfo *iter = n;
  while (iter) {
    jobject net_obj =
        (*env)->NewObject(env, net_cls, net_costruct);  //构造一个对象

    jstring name = (*env)->NewStringUTF(env, iter->name);
    (*env)->SetObjectField(env, net_obj, nameFieldId, name);  // 设置该字段的值
    (*env)->SetLongField(env, net_obj, rBytesFieldId,
                         iter->r_bytes);  // 设置该字段的值
    (*env)->SetLongField(env, net_obj, rPacketsFieldId,
                         iter->r_packets);  // 设置该字段的值
    (*env)->SetLongField(env, net_obj, rErrsFieldId,
                         iter->r_errs);  // 设置该字段的值
    (*env)->SetLongField(env, net_obj, rDropFieldId,
                         iter->r_drop);  // 设置该字段的值
    (*env)->SetLongField(env, net_obj, fifoFieldId,
                         iter->fifo);  // 设置该字段的值
    (*env)->SetLongField(env, net_obj, frameFieldId,
                         iter->frame);  // 设置该字段的值
    (*env)->SetLongField(env, net_obj, compressedFieldId,
                         iter->compressed);  // 设置该字段的值
    (*env)->SetLongField(env, net_obj, multicastFieldId,
                         iter->multicast);  // 设置该字段的值
    (*env)->SetLongField(env, net_obj, tBytesFieldId,
                         iter->t_bytes);  // 设置该字段的值
    (*env)->SetLongField(env, net_obj, tPacketsFieldId,
                         iter->t_packets);  // 设置该字段的值
    (*env)->SetLongField(env, net_obj, tErrsFieldId,
                         iter->t_errs);  // 设置该字段的值
    (*env)->SetLongField(env, net_obj, tDropFieldId,
                         iter->t_drop);  // 设置该字段的值
    (*env)->CallBooleanMethod(
        env, list_obj, list_add,
        net_obj);  //执行Arraylist类实例的add方法，添加一个netInfo对象
    netInfo *tmp = iter;
    iter = iter->next;
    free(tmp->name);
    free(tmp);
  }

  return list_obj;
}

static jobject stats_get_disk_ifo(JNIEnv *env, jclass clazz) {
  jobject list_obj = stats_util_createList(env);
  jmethodID list_add = stats_util_add_method(env);

  jclass disk_cls = (*env)->FindClass(env, "com/yam/os/DiskInfo");
  jmethodID disk_construct =
      (*env)->GetMethodID(env, disk_cls, "<init>", "()V");

  jfieldID fsFieldId =
      (*env)->GetFieldID(env, disk_cls, "fileSystem", "Ljava/lang/String;");
  jfieldID sizeFieldId = (*env)->GetFieldID(env, disk_cls, "size", "J");
  jfieldID usedFieldId = (*env)->GetFieldID(env, disk_cls, "used", "J");
  jfieldID availFieldId = (*env)->GetFieldID(env, disk_cls, "avail", "J");
  jfieldID usedPercentFieldId =
      (*env)->GetFieldID(env, disk_cls, "usedPercent", "J");
  jfieldID mountPointFieldId =
      (*env)->GetFieldID(env, disk_cls, "mountPoint", "Ljava/lang/String;");

  diskInfo *d = (diskInfo *)malloc(sizeof(diskInfo));
  if (get_disk_info(d)) {
    free(d);
    int err = errno;
    stats_util_throwExceptionErrorNo(env, "get_disk_info failed: ", err);
    return NULL;
  }

  diskInfo *cur = d;
  while (cur) {
    jobject record = (*env)->NewObject(env, disk_cls, disk_construct);
    jstring fs_name = (*env)->NewStringUTF(env, cur->fs_name);
    jstring mount_point = (*env)->NewStringUTF(env, cur->mount_point);
    (*env)->SetObjectField(env, record, fsFieldId, fs_name);
    (*env)->SetObjectField(env, record, mountPointFieldId, mount_point);
    (*env)->SetLongField(env, record, sizeFieldId, cur->size);
    (*env)->SetLongField(env, record, usedFieldId, cur->used);
    (*env)->SetLongField(env, record, availFieldId, cur->avail);
    (*env)->SetLongField(env, record, usedPercentFieldId, cur->percent);
    (*env)->CallBooleanMethod(env, list_obj, list_add, record);
    diskInfo *tmp = cur;
    cur = cur->next;
    free(tmp->fs_name);
    free(tmp->mount_point);
    free(tmp);
  }
  return list_obj;
}

static JNINativeMethod methods[] = {
    {"getCpuInfo", "()Lcom/yam/os/CpuInfo;", (void *)&stats_get_cpu_ifo},
    {"getMemInfo", "()Lcom/yam/os/MemInfo;", (void *)&stats_get_mem_ifo},
    {"getNetInfo", "()Ljava/util/List;", (void *)&stats_get_net_ifo},
    {"getDiskInfo", "()Ljava/util/List;", (void *)&stats_get_disk_ifo}};

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
  JNIEnv *env;
  if ((*vm)->GetEnv(vm, (void **)&env, JNI_VERSION_1_6) != JNI_OK) {
    return JNI_ERR;
  }
  if (stats_util_JNI_OnLoad(env) == JNI_ERR) {
    return JNI_ERR;
  }

  jclass cls = (*env)->FindClass(env, "com/yam/os/OsStats");
  (*env)->RegisterNatives(env, cls, methods,
                          sizeof(methods) / sizeof(methods[0]));
  return JNI_VERSION_1_6;
}

void JNI_OnUnload(JavaVM* vm, void* reserved) {
    JNIEnv* env;
    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        // Something is wrong but nothing we can do about this :(
        return;
    }
   stats_util_JNI_OnUnLoad(env);
}

