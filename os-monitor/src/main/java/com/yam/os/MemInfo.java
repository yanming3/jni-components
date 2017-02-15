package com.yam.os;

import java.io.Serializable;

/**
 * Created by allan on 17/2/14.
 */
public class MemInfo implements Serializable{
    private static final long serialVersionUID = 3865649091932659341L;

    private int total;

    private int free;

    private int buffers;

    private int cached;

    public int getTotal() {
        return total;
    }

    public void setTotal(int total) {
        this.total = total;
    }

    public int getFree() {
        return free;
    }

    public void setFree(int free) {
        this.free = free;
    }

    public int getBuffers() {
        return buffers;
    }

    public void setBuffers(int buffers) {
        this.buffers = buffers;
    }

    public int getCached() {
        return cached;
    }

    public void setCached(int cached) {
        this.cached = cached;
    }
}
