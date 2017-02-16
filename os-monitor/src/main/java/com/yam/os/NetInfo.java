package com.yam.os;

import java.io.Serializable;

/**
 * Created by allan on 17/2/14.
 */
public class NetInfo implements Serializable {

    private static final long serialVersionUID = -4487679097732697899L;

    private String name;

    private long rbytes;

    private long rpackets;

    private long rerrs;

    private long rdrop;

    private long fifo;

    private long frame;

    private long compressed;

    private long multicast;

    private long tbytes;

    private long tpackets;

    private long terrs;

    private long tdrop;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public long getRbytes() {
        return rbytes;
    }

    public void setRbytes(long rbytes) {
        this.rbytes = rbytes;
    }

    public long getRpackets() {
        return rpackets;
    }

    public void setRpackets(long rpackets) {
        this.rpackets = rpackets;
    }

    public long getRerrs() {
        return rerrs;
    }

    public void setRerrs(long rerrs) {
        this.rerrs = rerrs;
    }

    public long getRdrop() {
        return rdrop;
    }

    public void setRdrop(long rdrop) {
        this.rdrop = rdrop;
    }

    public long getFifo() {
        return fifo;
    }

    public void setFifo(long fifo) {
        this.fifo = fifo;
    }

    public long getFrame() {
        return frame;
    }

    public void setFrame(long frame) {
        this.frame = frame;
    }

    public long getCompressed() {
        return compressed;
    }

    public void setCompressed(long compressed) {
        this.compressed = compressed;
    }

    public long getMulticast() {
        return multicast;
    }

    public void setMulticast(long multicast) {
        this.multicast = multicast;
    }

    public long getTbytes() {
        return tbytes;
    }

    public void setTbytes(long tbytes) {
        this.tbytes = tbytes;
    }

    public long getTpackets() {
        return tpackets;
    }

    public void setTpackets(long tpackets) {
        this.tpackets = tpackets;
    }

    public long getTerrs() {
        return terrs;
    }

    public void setTerrs(long terrs) {
        this.terrs = terrs;
    }

    public long getTdrop() {
        return tdrop;
    }

    public void setTdrop(long tdrop) {
        this.tdrop = tdrop;
    }
}
