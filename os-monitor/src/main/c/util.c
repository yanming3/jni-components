#include "util.h"
static jclass statsExceptionClass = NULL;

void stats_util_throwExceptionErrorNo(JNIEnv* env, char* msg, int error) {
  char* allocatedMessage =
      stats_util_prepend(msg, strerror(error < 0 ? -error : error));
  (*env)->ThrowNew(env, statsExceptionClass, allocatedMessage);
  free(allocatedMessage);
}

char* stats_util_prepend(const char* prefix, const char* str) {
  if (prefix == NULL) {
    char* result = (char*)malloc(sizeof(char) * (strlen(str) + 1));
    strcpy(result, str);
    return result;
  }
  char* result =
      (char*)malloc(sizeof(char) * (strlen(prefix) + strlen(str) + 1));
  strcpy(result, prefix);
  strcat(result, str);
  return result;
}

jobject stats_util_createList(JNIEnv* env) {
  jclass list_cls = (*env)->FindClass(env, "java/util/ArrayList");
  if (list_cls == NULL) {
    perror("can find class java.util.ArrayList!\n");
    return NULL;
  }

  jmethodID list_construct =
      (*env)->GetMethodID(env, list_cls, "<init>", "()V");

  jobject list_obj = (*env)->NewObject(env, list_cls, list_construct);
  return list_obj;
}

jmethodID stats_util_add_method(JNIEnv* env) {
  jclass list_cls = (*env)->FindClass(env, "java/util/ArrayList");
  if (list_cls == NULL) {
    perror("can find class java.util.ArrayList!\n");
    return NULL;
  }

  return (*env)->GetMethodID(env, list_cls, "add", "(Ljava/lang/Object;)Z");
}

jint stats_util_JNI_OnLoad(JNIEnv* env) {
  // cache classes that are used within other jni methods for performance
  // reasons
  jclass localStatsExceptionClass =
      (*env)->FindClass(env, "com/yam/os/StatsException");
  if (localStatsExceptionClass == NULL) {
    // pending exception...
    return JNI_ERR;
  }
  statsExceptionClass =
      (jclass)(*env)->NewGlobalRef(env, localStatsExceptionClass);
  if (statsExceptionClass == NULL) {
    // out-of-memory!
    perror("out of memory!");
    return JNI_ERR;
  }
  return JNI_VERSION_1_6;
}
void stats_util_JNI_OnUnLoad(JNIEnv* env) {
  if (statsExceptionClass != NULL) {
    (*env)->DeleteGlobalRef(env, statsExceptionClass);
    statsExceptionClass = NULL;
  }
}