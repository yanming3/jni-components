#include "com_yanming_image_Image.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wand/magick_wand.h>
#include "magick/enum_strings.h"

JNIEXPORT void JNICALL Java_com_yanming_image_Image_init
  (JNIEnv *env, jobject obj)
  {
        InitializeMagick(NULL);
  }

JNIEXPORT void JNICALL Java_com_yanming_image_Image_destroy
  (JNIEnv *env, jobject obj)
  {
         DestroyMagick();
  }


JNIEXPORT jlong JNICALL Java_com_yanming_image_Image_newImageHandle
  (JNIEnv *env, jobject obj)
  {
        MagickWand *magick_wand;
        magick_wand=NewMagickWand();
        return (jlong)magick_wand;
  }


JNIEXPORT void JNICALL Java_com_yanming_image_Image_destroyImageHandle
  (JNIEnv *env, jobject obj, jlong hd)
  {
        DestroyMagickWand((MagickWand*)hd);
  }


JNIEXPORT jlong JNICALL Java_com_yanming_image_Image_getHeight
  (JNIEnv *env, jobject obj, jlong hd)
  {
        unsigned long h;
        h=MagickGetImageHeight((MagickWand*)hd);
        return (jlong)h;
  }


JNIEXPORT jlong JNICALL Java_com_yanming_image_Image_getWidth
  (JNIEnv *env, jobject obj, jlong hd)
  {
        unsigned long w;
        w=MagickGetImageWidth((MagickWand*)hd);
        return (jlong)w;
  }


JNIEXPORT jstring JNICALL Java_com_yanming_image_Image_getFormat
  (JNIEnv *env, jobject obj, jlong hd)
  {
        const char* tStr=MagickGetImageFormat((MagickWand*)hd);
        jstring result = (*env)->NewStringUTF(env, tStr);
        return result;
  }


JNIEXPORT jint JNICALL Java_com_yanming_image_Image_setFormat
  (JNIEnv *env, jobject obj, jlong hd, jstring tStr)
  {
        MagickPassFail status = MagickPass;
        const char* t=(*env)->GetStringUTFChars(env,tStr,0);
        status=MagickSetImageFormat((MagickWand*)hd,t);
        (*env)->ReleaseStringUTFChars(env, tStr, t);
        if (status != MagickPass)
         {
              char *description;
              ExceptionType severity;

              description=MagickGetException((MagickWand*)hd,&severity);
              (void) fprintf(stderr,"%.1024s (severity %d)\n",description,severity);
         }
        return (jint)(status == MagickPass ? 0 : 1);
  }

JNIEXPORT jint JNICALL Java_com_yanming_image_Image_setCompressQuality
  (JNIEnv *env, jobject obj, jlong hd, jlong quality)
  {
        MagickPassFail status = MagickPass;
        status=MagickSetCompressionQuality((MagickWand*)hd,(const unsigned long)quality);
        if (status != MagickPass)
           {
              char *description;
              ExceptionType severity;

              description=MagickGetException((MagickWand*)hd,&severity);
              (void) fprintf(stderr,"%.1024s (severity %d)\n",description,severity);
           }
        return (jint)(status == MagickPass ? 0 : 1);
  }

JNIEXPORT jint JNICALL Java_com_yanming_image_Image_setBackgroundColor
  (JNIEnv *env, jobject obj, jlong hd, jstring color)
  {
        const char* c=(*env)->GetStringUTFChars(env,color,0);
        PixelWand *background;
        background=NewPixelWand();
        PixelSetColor(background,c);
        MagickPassFail status = MagickPass;
        status=MagickGetImageBackgroundColor((MagickWand*)hd,background);
        DestroyPixelWand(background);
        (*env)->ReleaseStringUTFChars(env,color,c);
        if (status != MagickPass)
           {
              char *description;
              ExceptionType severity;

              description=MagickGetException((MagickWand*)hd,&severity);
              (void) fprintf(stderr,"%.1024s (severity %d)\n",description,severity);
           }
           return (jint)(status == MagickPass ? 0 : 1);
  }


JNIEXPORT jint JNICALL Java_com_yanming_image_Image_setBorderColor
  (JNIEnv *env, jobject obj, jlong hd, jstring color)
  {
          const char* c=(*env)->GetStringUTFChars(env,color,0);
          PixelWand *background;
          background=NewPixelWand();
          PixelSetColor(background,c);
          MagickPassFail status = MagickPass;
          status=MagickSetImageBorderColor((MagickWand*)hd,background);
          DestroyPixelWand(background);
          (*env)->ReleaseStringUTFChars(env,color,c);
          if (status != MagickPass)
           {
              char *description;
              ExceptionType severity;

              description=MagickGetException((MagickWand*)hd,&severity);
              (void) fprintf(stderr,"%.1024s (severity %d)\n",description,severity);
           }
           return (jint)(status == MagickPass ? 0 : 1);
  }


JNIEXPORT jint JNICALL Java_com_yanming_image_Image_setDepth
  (JNIEnv *env, jobject obj, jlong hd, jlong depth)
  {
        MagickPassFail status = MagickPass;
        status=MagickSetImageDepth((MagickWand*)hd, (size_t)depth);
        if (status != MagickPass)
         {
            char *description;
            ExceptionType severity;

            description=MagickGetException((MagickWand*)hd,&severity);
            (void) fprintf(stderr,"%.1024s (severity %d)\n",description,severity);
         }
         return (jint)(status == MagickPass ? 0 : 1);
  }


JNIEXPORT jint JNICALL Java_com_yanming_image_Image_setGravity
  (JNIEnv *env, jobject obj, jlong hd, jstring gravity)
  {
        const char* g=(*env)->GetStringUTFChars(env,gravity,0);
        MagickPassFail status = MagickPass;
        status=MagickSetImageGravity((MagickWand*)hd,StringToGravityType(g));
        (*env)->ReleaseStringUTFChars(env,gravity,g);
        if (status != MagickPass)
         {
            char *description;
            ExceptionType severity;

            description=MagickGetException((MagickWand*)hd,&severity);
            (void) fprintf(stderr,"%.1024s (severity %d)\n",description,severity);
         }
         return (jint)(status == MagickPass ? 0 : 1);
  }

JNIEXPORT jint JNICALL Java_com_yanming_image_Image_readImage
  (JNIEnv *env, jobject obj, jlong hd,jstring inFile)
  {
        const char* f=(*env)->GetStringUTFChars(env,inFile,0);
        MagickPassFail status = MagickPass;

        status = MagickReadImage((MagickWand*)hd,f);
        (*env)->ReleaseStringUTFChars(env, inFile, f);
        if (status != MagickPass)
         {
            char *description;
            ExceptionType severity;

            description=MagickGetException((MagickWand*)hd,&severity);
            (void) fprintf(stderr,"%.1024s (severity %d)\n",description,severity);
         }
         return (jint)(status == MagickPass ? 0 : 1);
  }


JNIEXPORT jint JNICALL Java_com_yanming_image_Image_readImageBlob
  (JNIEnv *env, jobject obj,jlong hd, jbyteArray dArray, jlong len)
  {
        MagickPassFail status = MagickPass;
        const  char* data=(const  char*)(*env)->GetByteArrayElements(env,dArray,0);
        status=MagickReadImageBlob((MagickWand*)hd,(const unsigned char*)data,(size_t)len),
        (*env)->ReleaseByteArrayElements(env,dArray,(jbyte*)data,0);
        if (status != MagickPass)
        {
            char *description;
            ExceptionType severity;

            description=MagickGetException((MagickWand*)hd,&severity);
            (void) fprintf(stderr,"%.1024s (severity %d)\n",description,severity);
        }
        return (jint)(status == MagickPass ? 0 : 1);
  }


JNIEXPORT jint JNICALL Java_com_yanming_image_Image_writeImage
  (JNIEnv *env, jobject obj, jlong hd, jstring outFile)
  {
        const char* f=(*env)->GetStringUTFChars(env,outFile,0);
        MagickPassFail status = MagickPass;
        status = MagickWriteImage((MagickWand*)hd,f);
        (*env)->ReleaseStringUTFChars(env,outFile,f);
        if (status != MagickPass)
        {
            char *description;
            ExceptionType severity;

            description=MagickGetException((MagickWand*)hd,&severity);
            (void) fprintf(stderr,"%.1024s (severity %d)\n",description,severity);
        }
        return (jint)(status == MagickPass ? 0 : 1);
  }


JNIEXPORT jint JNICALL Java_com_yanming_image_Image_strip
  (JNIEnv *env, jobject obj, jlong hd)
  {
    MagickPassFail status =MagickStripImage((MagickWand*)hd);
    if (status != MagickPass)
    {
        char *description;
        ExceptionType severity;

        description=MagickGetException((MagickWand*)hd,&severity);
        (void) fprintf(stderr,"%.1024s (severity %d)\n",description,severity);
    }
    return (jint)(status == MagickPass ? 0 : 1);
  }


JNIEXPORT jint JNICALL Java_com_yanming_image_Image_crop
  (JNIEnv *env, jobject obj, jlong hd, jlong width, jlong height, jlong x, jlong y)
  {
        MagickPassFail status =MagickCropImage((MagickWand*)hd, (const unsigned long)width,(const unsigned long)height, (const long)x, (const long) y);
        if (status != MagickPass)
        {
            char *description;
            ExceptionType severity;

            description=MagickGetException((MagickWand*)hd,&severity);
            (void) fprintf(stderr,"%.1024s (severity %d)\n",description,severity);
        }
        return (jint)(status == MagickPass ? 0 : 1);
  }


JNIEXPORT jint JNICALL Java_com_yanming_image_Image_scale
  (JNIEnv *env, jobject obj, jlong hd, jlong columns, jlong rows)
  {
        MagickPassFail status =MagickScaleImage((MagickWand*)hd,(const unsigned long)columns,(const unsigned long)rows);
        if (status != MagickPass)
        {
            char *description;
            ExceptionType severity;

            description=MagickGetException((MagickWand*)hd,&severity);
            (void) fprintf(stderr,"%.1024s (severity %d)\n",description,severity);
        }
        return (jint)(status == MagickPass ? 0 : 1);
  }


JNIEXPORT jint JNICALL Java_com_yanming_image_Image_sample
  (JNIEnv *env, jobject obj, jlong hd, jlong columns,jlong rows)
  {
        MagickPassFail status =MagickSampleImage((MagickWand*)hd,(const unsigned long)columns,(const unsigned long)rows);
        if (status != MagickPass)
        {
          char *description;
          ExceptionType severity;

          description=MagickGetException((MagickWand*)hd,&severity);
          (void) fprintf(stderr,"%.1024s (severity %d)\n", description,severity);
        }

        return (jint)(status == MagickPass ? 0 : 1);
  }


JNIEXPORT jint JNICALL Java_com_yanming_image_Image_sharpen
  (JNIEnv *env, jobject obj, jlong hd, jdouble radius, jdouble sigma){
        MagickPassFail status=MagickPass;
        status=MagickSharpenImage((MagickWand*)hd,(const double)radius,(const double)sigma);
        if (status != MagickPass)
        {
          char *description;
          ExceptionType severity;

          description=MagickGetException((MagickWand*)hd,&severity);
          (void) fprintf(stderr,"%.1024s (severity %d)\n", description,severity);
        }

        return (jint)(status == MagickPass ? 0 : 1);
  }


JNIEXPORT jint JNICALL Java_com_yanming_image_Image_rotate
  (JNIEnv *env, jobject obj, jlong hd,jdouble degrees,jstring bStr){
        MagickPassFail status=MagickPass;
        const char* b=(*env)->GetStringUTFChars(env,bStr,0);
        PixelWand *background;
        background=NewPixelWand();
        PixelSetColor(background,b);
        status=MagickRotateImage((MagickWand*)hd,background,(double)degrees);
        DestroyPixelWand(background);
        (*env)->ReleaseStringUTFChars(env,bStr,b);
        if (status != MagickPass)
        {
          char *description;
          ExceptionType severity;

          description=MagickGetException((MagickWand*)hd,&severity);
          (void) fprintf(stderr,"%.1024s (severity %d)\n", description,severity);
        }

        return (jint)(status == MagickPass ? 0 : 1);
  }


JNIEXPORT jint JNICALL Java_com_yanming_image_Image_roll
  (JNIEnv *env, jobject obj, jlong hd, jlong xOffset,jlong yOffset){
        MagickPassFail status=MagickPass;
        status=MagickRollImage((MagickWand*)hd,(const long)xOffset,(const long)yOffset);
        if (status != MagickPass)
        {
          char *description;
          ExceptionType severity;

          description=MagickGetException((MagickWand*)hd,&severity);
          (void) fprintf(stderr,"%.1024s (severity %d)\n", description,severity);
        }

        return (jint)(status == MagickPass ? 0 : 1);
  }
JNIEXPORT jint JNICALL Java_com_yanming_image_Image_extent
  (JNIEnv *env, jobject obj, jlong hd, jlong width, jlong height, jlong x, jlong y)
  {
        MagickPassFail status=MagickPass;
        status=MagickExtentImage((MagickWand*)hd,(size_t)width,(size_t)height,(ssize_t)x,(ssize_t)y);
        if (status != MagickPass)
        {
          char *description;
          ExceptionType severity;

          description=MagickGetException((MagickWand*)hd,&severity);
          (void) fprintf(stderr,"%.1024s (severity %d)\n", description,severity);
        }

        return (jint)(status == MagickPass ? 0 : 1);
  }

JNIEXPORT jint JNICALL Java_com_yanming_image_Image_resize
  (JNIEnv *env, jobject obj, jlong hd, jlong columns,jlong rows, jdouble blur,jstring f){
        const char* filterStr=(*env)->GetStringUTFChars(env,f,0);
        const FilterTypes filter=StringToFilterTypes(filterStr);
        MagickPassFail status=MagickPass;
        status=MagickResizeImage((MagickWand*)hd,(const unsigned long)columns,(const unsigned long)rows,filter,(const double)blur);
        (*env)->ReleaseStringUTFChars(env,f,filterStr);
        if (status != MagickPass)
        {
          char *description;
          ExceptionType severity;

          description=MagickGetException((MagickWand*)hd,&severity);
          (void) fprintf(stderr,"%.1024s (severity %d)\n", description,severity);
        }

        return (jint)(status == MagickPass ? 0 : 1);
  }