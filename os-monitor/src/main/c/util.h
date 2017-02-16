#ifndef STATS_UTIL_H_
#define STATS_UTIL_H_

#include <jni.h>
#include<string.h>
#include <errno.h>
#include <stdlib.h>

void stats_util_throwExceptionErrorNo(JNIEnv* env, char* msg, int error);

char* stats_util_prepend(const char* prefix, const char* str);

jobject stats_util_createList(JNIEnv* env);

jmethodID stats_util_add_method(JNIEnv* env);

// JNI initialization hooks. Users of this file are responsible for calling these in the JNI_OnLoad and JNI_OnUnload methods.
jint stats_util_JNI_OnLoad(JNIEnv* env);
void stats_util_JNI_OnUnLoad(JNIEnv* env);

#endif