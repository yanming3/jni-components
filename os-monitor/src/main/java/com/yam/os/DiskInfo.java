package com.yam.os;

import java.io.Serializable;

/**
 * Created by allan on 17/2/15.
 */
public class DiskInfo implements Serializable {

    private static final long serialVersionUID = 4649176594449795305L;

    /**
     * 文件系统名称
     */
    private String fileSystem;

    /**
     * 文件系统的总大小,单位为K
     */
    private long size;

    /**
     * 已使用大小,单位为K
     */
    private long used;

    /**
     * 可用大小,单位为K
     */
    private long avail;

    private long usedPercent;
    /**
     * 加载点
     */
    private String mountPoint;

    public String getFileSystem() {
        return fileSystem;
    }

    public void setFileSystem(String fileSystem) {
        this.fileSystem = fileSystem;
    }

    public long getSize() {
        return size;
    }

    public void setSize(long size) {
        this.size = size;
    }

    public long getUsed() {
        return used;
    }

    public void setUsed(long used) {
        this.used = used;
    }

    public long getAvail() {
        return avail;
    }

    public void setAvail(long avail) {
        this.avail = avail;
    }

    public String getMountPoint() {
        return mountPoint;
    }

    public void setMountPoint(String mountPoint) {
        this.mountPoint = mountPoint;
    }

    public long getUsedPercent() {
        return usedPercent;
    }

    public void setUsedPercent(long usedPercent) {
        this.usedPercent = usedPercent;
    }
}
