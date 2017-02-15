package com.yam.image;

/**
 * Created by allan on 16/9/22.
 */
public class ImageUtils extends NativeLoader{

    private ImageUtils() {

    }

    public native static void process(int count, String[] args);

}
