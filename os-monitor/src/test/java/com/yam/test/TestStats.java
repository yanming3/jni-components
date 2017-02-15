package com.yam.test;

import com.yam.os.CpuInfo;
import com.yam.os.OsStats;
import org.junit.Test;

/**
 * Created by allan on 17/2/15.
 */
public class TestStats {
    @Test
    public void testGetCupInfo() {
        CpuInfo info = OsStats.getCpuInfo();
        System.out.println(info.getSystem());
    }
}
