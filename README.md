# 概述
提供了Java调用C的代码样例,GraphicsMagick和os-monitor两个模块采用了不同的JNI实现;

* GraphicsMagick是通过javah命令生成JNI头文件,然后实现函数;
* os-monitor采用JNI_OnLoad调用RegisterNatives实现;

# 模块说明
##GraphicsMagick
   GraphicsMagick是流行的图像处理库,采用C编写,通常大家会使用外部命令调用方式,此处采用JNI方式提高性能;
  
1. ImageUtils
 传入参数和gm命令相同，直接调用graphicsmagick的GMCommand API;
 
2. Image
调用c wand api,未实现所有api,如果有需要，可以按照例子自行实现

## os-monitor
  获取Linux CPU,内存和网络性能参数,包含下述三个方法:
  
1. OsStats.getCpuInfo:获取CPU性能参数;
2. OsStats.getMemInfo:获取内存性能参数;
3. OsStats.getNetInfo:获取网络性能参数;

##
## 打包
采用maven-hawtjni-plugin插件打包，配置参数的部分路径需要根据实际情况进行调整(修改pom.xml的**configureArgs**);

## 例子
见Junit Test;

