#include "com_yanming_image_ImageUtils.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <magick/api.h>


JNIEXPORT void JNICALL Java_com_yanming_image_ImageUtils_process
  (JNIEnv *env, jclass cls, jint count, jobjectArray args){
        char ** p_arg=NULL;
        p_arg=(char**)calloc((int)count,sizeof(char*));
        int i;
        for(i=0;i<count;i++){
          jstring obj=(jstring)(*env)->GetObjectArrayElement(env,args,i);
          const char* arg=(*env)->GetStringUTFChars(env,obj,0);
          p_arg[i]=arg;
        }
        GMCommand(count,p_arg);
  }