package com.yam.os;

import java.io.Serializable;

/**
 * Created by allan on 17/2/14.
 */
public class NetInfo implements Serializable {

    private static final long serialVersionUID = -4487679097732697899L;

    private String name;

    private long rBytes;

    private long rPackets;

    private long rErrs;

    private long rDrop;

    private long fifo;

    private long frame;

    private long compressed;

    private long multicast;

    private long tBytes;

    private long tPackets;

    private long tErrs;

    private long tDrop;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public long getrBytes() {
        return rBytes;
    }

    public void setrBytes(long rBytes) {
        this.rBytes = rBytes;
    }

    public long getrPackets() {
        return rPackets;
    }

    public void setrPackets(long rPackets) {
        this.rPackets = rPackets;
    }

    public long getrErrs() {
        return rErrs;
    }

    public void setrErrs(long rErrs) {
        this.rErrs = rErrs;
    }

    public long getrDrop() {
        return rDrop;
    }

    public void setrDrop(long rDrop) {
        this.rDrop = rDrop;
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

    public long gettBytes() {
        return tBytes;
    }

    public void settBytes(long tBytes) {
        this.tBytes = tBytes;
    }

    public long gettPackets() {
        return tPackets;
    }

    public void settPackets(long tPackets) {
        this.tPackets = tPackets;
    }

    public long gettErrs() {
        return tErrs;
    }

    public void settErrs(long tErrs) {
        this.tErrs = tErrs;
    }

    public long gettDrop() {
        return tDrop;
    }

    public void settDrop(long tDrop) {
        this.tDrop = tDrop;
    }
}
