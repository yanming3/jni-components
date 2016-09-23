# graphicsmagick-java
提供了通过java方式访问graphicsmagick；

## ImageUtils
 传入参数和gm命令相同，直接调用graphicsmagick的GMCommand API;
 
## Image
调用c wand api,未实现所有api,如果有需要，可以按照例子自行实现

## 打包
采用maven-hawtjni-plugin插件打包，配置参数根据graphicsmagick的按照路径不同，需要修改pom.xml的**configureArgs**

## 例子

```java
String[] paras = new String[]{"convert", "/Users/allan/Downloads/1.jpg", "-thumbnail", "300x300^", "-gravity", "center", "-extent", "300x300", "/Users/allan/Downloads/2.jpg"};
ImageUtils.process(paras.length, paras);

Image image = new Image("/Users/allan/Downloads/1.jpg");
image.crop(50, 50, 50, 50);
image.writeImage("/Users/allan/Downloads/3.jpg");
image.close();
```

