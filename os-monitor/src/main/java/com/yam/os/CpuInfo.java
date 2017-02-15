package com.yam.os;


import java.io.Serializable;

/**
 *
 * 从/proc/stat获取CPU使用情况(单位为jiffies)
 */
public class CpuInfo implements Serializable{

    private static final long serialVersionUID = 8057367578714593141L;
    /**
     * 从系统启动开始累计到当前时刻，处于用户态的运行时间，不包含 nice值为负的进程。
     */
    private long user;

    /**
     * 从系统启动开始累计到当前时刻，nice值为负的进程所占用的CPU时间.
     */
    private long nice;

    /**
     * 从系统启动开始累计到当前时刻，处于核心态的运行时间
     */
    private long system;

    /**
     * 从系统启动开始累计到当前时刻，除IO等待时间以外的其它等待时间
     */
    private long idle;

    /**
     * 从系统启动开始累计到当前时刻，IO等待时间(since 2.5.41)
     */
    private long iowait;

    /**
     * 从系统启动开始累计到当前时刻，硬中断时间(since 2.6.0-test4)
     */
    private long irq;

    /**
     * 从系统启动开始累计到当前时刻，软中断时间(since 2.6.0-test4)
     */
    private long softirq;


    public long getUser() {
        return user;
    }

    public void setUser(long user) {
        this.user = user;
    }

    public long getNice() {
        return nice;
    }

    public void setNice(long nice) {
        this.nice = nice;
    }

    public long getSystem() {
        return system;
    }

    public void setSystem(long system) {
        this.system = system;
    }

    public long getIdle() {
        return idle;
    }

    public void setIdle(long idle) {
        this.idle = idle;
    }

    public long getIowait() {
        return iowait;
    }

    public void setIowait(long iowait) {
        this.iowait = iowait;
    }

    public long getIrq() {
        return irq;
    }

    public void setIrq(long irq) {
        this.irq = irq;
    }

    public long getSoftirq() {
        return softirq;
    }

    public void setSoftirq(long softirq) {
        this.softirq = softirq;
    }

}
