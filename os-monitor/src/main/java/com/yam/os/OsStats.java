package com.yam.os;

import java.util.List;

/**
 * Created by allan on 17/2/14.
 */
public class OsStats extends  NativeLoader{

    public native static CpuInfo getCpuInfo();

    public native static MemInfo getMemInfo();

    public native static List<NetInfo> getNetInfo();

}
