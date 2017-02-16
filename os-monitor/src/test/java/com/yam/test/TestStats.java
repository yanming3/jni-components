package com.yam.test;

import com.yam.os.*;

import static org.junit.Assert.*;

import org.junit.Test;

import java.util.List;

/**
 * Created by allan on 17/2/15.
 */
public class TestStats {
    @Test
    public void testGetCupInfo() {
        CpuInfo info = OsStats.getCpuInfo();
        assertNotNull(info);
        System.out.println(info.getSystem());
    }

    @Test
    public void testGetDiskInfo() {
        List<DiskInfo> list = OsStats.getDiskInfo();
        assert (list.size() > 0);
        System.out.printf("disk size is %d\n", list.size());
        for (DiskInfo d : list) {
            System.out.printf("%s %s %d", d.getFileSystem(), d.getMountPoint(), d.getSize());
        }
    }

    @Test
    public void testGetMemInfo() {
        MemInfo m = OsStats.getMemInfo();
        assertNotNull(m);
        System.out.printf("MemTotal=%d", m.getTotal());
    }

    @Test
    public void testGetNetInfo() {
        List<NetInfo> list = OsStats.getNetInfo();
        assert (list.size() > 0);

        System.out.printf("disk size is %d\n", list.size());
        for (NetInfo d : list) {
            System.out.printf("%s %d", d.getName(), d.getRbytes());
        }
    }
}
