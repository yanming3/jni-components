package com.yam.image;

/**
 * Created by allan on 16/9/21.
 */
public class Image extends NativeLoader {

    private long pointer;

    public Image(String inFile) {
        this.pointer = newImageHandle();
        this.readImage(pointer, inFile);
    }

    public long getHeight() {
        return this.getHeight(this.pointer);
    }

    public long getWidth() {
        return this.getWidth(this.pointer);
    }

    public String getFormat() {
        return this.getFormat(this.pointer);
    }

    public void setFormat(String format) {
        this.setFormat(this.pointer, format);
    }

    public void setGravity() {
        this.setGravity(this.pointer, "Center");
    }

    public void strip() {
        this.strip(this.pointer);
    }

    public void crop(long width, long height, long x, long y) {
        this.crop(this.pointer, width, height, x, y);
    }

    public void rotate(double degrees, String background) {
        this.rotate(this.pointer, degrees, background);
    }

    public void scale(long columns, long rows) {
        this.scale(this.pointer, columns, rows);
    }

    public void sample(long width, long height) {
        this.sample(this.pointer, width, height);
    }

    public void resize(long columns, long rows, long blur) {
        this.resize(this.pointer, columns, rows, blur, "Lanczos");
    }

    public void extent(long width, long height, long x, long y) {
        this.extent(this.pointer, width, height, x, y);
    }

    public void writeImage(String file) {
        this.writeImage(this.pointer, file);
    }

    public void close() {
        this.destroyImageHandle(this.pointer);
        this.destroy();
    }

    /**
     * 初始化
     */
    private native void init();

    /**
     * 对象销毁
     */
    private native void destroy();


    private native long newImageHandle();

    private native void destroyImageHandle(long pointer);

    private native long getHeight(long pointer);

    private native long getWidth(long pointer);

    /**
     * 获取文件格式
     *
     * @param pointer
     * @return
     */
    private native String getFormat(long pointer);

    /**
     * 设置文件格式
     *
     * @param pointer
     * @param format
     */
    private native int setFormat(long pointer, String format);

    /**
     * 设置压缩质量
     *
     * @param pointer
     * @param quallity
     */
    private native int setCompressQuality(long pointer, long quallity);

    /**
     * 设置背景色
     *
     * @param pointer
     * @param color
     */
    private native int setBackgroundColor(long pointer, String color);

    /**
     * 设置边框颜色
     *
     * @param pointer
     * @param color
     */
    private native int setBorderColor(long pointer, String color);

    /**
     * 设置图像深度
     *
     * @param pointer
     * @param depth
     */
    private native int setDepth(long pointer, long depth);

    /**
     * 设置位置,例如center,northwest
     *
     * @param pointer
     * @param gravity
     */
    private native int setGravity(long pointer, String gravity);

    /**
     * 读取文件
     *
     * @param inFile 文件全路径
     */
    private native int readImage(long pointer, String inFile);

    /**
     * 读取文件(二进制)
     *
     * @param data 二进制数组
     * @param size
     */
    private native int readImageBlob(long pointer, byte[] data, long size);

    /**
     * 输出图片
     *
     * @param pointer
     * @param file    图片全路径
     */
    private native int writeImage(long pointer, String file);

    /**
     * 删除图片的元数据,例如Exif信息;
     *
     * @param pointer
     */
    private native int strip(long pointer);

    /**
     * 截取图片的部分
     *
     * @param pointer
     * @param width   图片宽度
     * @param height  图片高度
     * @param x       起始水平坐标
     * @param y       起始纵坐标
     */
    private native int crop(long pointer, long width, long height, long x, long y);

    /**
     * 缩放图片到指定尺寸
     *
     * @param pointer
     * @param columns
     * @param rows
     */
    private native int scale(long pointer, long columns, long rows);

    /**
     * 缩放图片到指定尺寸,和scale的不同在于它是通过像素采样
     *
     * @param width
     * @param height
     * @return
     */
    private native int sample(long pointer, long width, long height);

    /**
     * 对图片进行高斯锐化,通过增加相邻像素的对比度来使模糊图像变清晰;
     *
     * @param pointer
     * @param radius  半径
     * @param sigma   对比度
     */
    private native int sharpen(long pointer, double radius, double sigma);

    /**
     * 旋转
     *
     * @param degrees
     * @return
     */
    private native int rotate(long pointer, double degrees, String background);


    private native int roll(long pointer, long xOffset, long yOffset);


    private native int extent(long pointer, long width, long height, long x, long y);

    /**
     * 通过滤镜缩放图片
     *
     * @param columns
     * @param rows
     * @param blur    大于1为模糊,小于1为锐化
     * @return
     */
    private native int resize(long pointer, long columns, long rows, double blur, String filter);
}
