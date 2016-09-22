package example;

import com.yanming.image.ImageConverter;

public class Main {

    public static void main(String[] args) {
        System.setProperty("java.library.path", "/Users/allan/Study/java/jni-example/src/main/c");
        System.loadLibrary("ImageConverter");
        ImageConverter converter = new ImageConverter("/Users/allan/Downloads/a.jpg");
        System.out.println(converter.getWidth());
        System.out.println(converter.getHeight());
        System.out.println(converter.getFormat());
        converter.setGravity();
        converter.resize(300,300,1);
        converter.extent(300,300,0,50);
        //converter.scaleImage(100,100);
        converter.writeImage("/Users/allan/Downloads/a2.jpg");
        converter.close();
    }
}
