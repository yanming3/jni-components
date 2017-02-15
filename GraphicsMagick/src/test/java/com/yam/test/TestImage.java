package com.yam.test;

import com.yam.image.Image;
import com.yam.image.ImageUtils;
import org.junit.Test;

import java.util.Arrays;
import java.util.List;

/**
 * Created by allan on 17/2/15.
 */
public class TestImage {
    @Test
    public void testC() {
        String[] paras = new String[]{"convert", "/Users/allan/Downloads/1.jpg", "-thumbnail", "300x300^", "-gravity", "center", "-extent", "300x300", "/Users/allan/Downloads/2.jpg"};
        ImageUtils.process(paras.length, paras);

        Image image = new Image("/Users/allan/Downloads/1.jpg");
        image.crop(50, 50, 50, 50);
        image.writeImage("/Users/allan/Downloads/3.jpg");
        image.close();
    }

    //@Test
    public void testExternal() throws Exception {
        String ROOT = "/Users/allan/Downloads/";

        List<String> paras1 = Arrays.asList(new String[]{"gm", "convert", "/Users/allan/Downloads/1.jpg", "-thumbnail", "300x300^", "-gravity", "center", "-extent", "300x300"});
        paras1.add(ROOT + "1_1.jpg");
        ProcessBuilder builder = new ProcessBuilder(paras1);
        builder.start();
    }
}
