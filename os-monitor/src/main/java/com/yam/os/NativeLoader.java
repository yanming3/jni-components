package com.yam.os;

import java.io.*;
import java.net.URL;
import java.util.Locale;

/**
 * Created by allan on 17/2/15.
 */
public class NativeLoader {
    private static final String NATIVE_RESOURCE_HOME = "META-INF/native/";
    private static final String OSNAME;
    private static final File WORKDIR;
    private static boolean loaded = false;

    static {
        OSNAME = System.getProperty("os.name", "").toLowerCase(Locale.US).replaceAll("[^a-z0-9]+", "");
        WORKDIR = new File(System.getProperty("java.io.tmpdir"));
        try {
            load("osmonitor", NativeLoader.class.getClassLoader());
            loaded = true;
        } catch (UnsatisfiedLinkError ignore) {

        }
    }

    private static void load(String name, ClassLoader loader) {
        String libname = System.mapLibraryName(name);
        String path = NATIVE_RESOURCE_HOME + libname;

        URL url = loader.getResource(path);
        if (url == null && isOSX()) {
            if (path.endsWith(".jnilib")) {
                url = loader.getResource(NATIVE_RESOURCE_HOME + "lib" + name + ".dynlib");
            } else {
                url = loader.getResource(NATIVE_RESOURCE_HOME + "lib" + name + ".jnilib");
            }
        }

        if (url == null) {
            // Fall back to normal loading of JNI stuff
            System.loadLibrary(name);
            return;
        }

        int index = libname.lastIndexOf('.');
        String prefix = libname.substring(0, index);
        String suffix = libname.substring(index, libname.length());
        InputStream in = null;
        OutputStream out = null;
        File tmpFile = null;
        boolean loaded = false;
        try {
            tmpFile = File.createTempFile(prefix, suffix, WORKDIR);
            in = url.openStream();
            out = new FileOutputStream(tmpFile);

            byte[] buffer = new byte[8192];
            int length;
            while ((length = in.read(buffer)) > 0) {
                out.write(buffer, 0, length);
            }
            out.flush();
            out.close();
            out = null;

            System.load(tmpFile.getPath());
            loaded = true;
        } catch (Exception e) {
            throw (UnsatisfiedLinkError) new UnsatisfiedLinkError(
                    "could not load a native library: " + name).initCause(e);
        } finally {
            if (in != null) {
                try {
                    in.close();
                } catch (IOException ignore) {
                    // ignore
                }
            }
            if (out != null) {
                try {
                    out.close();
                } catch (IOException ignore) {
                    // ignore
                }
            }
            if (tmpFile != null) {
                if (loaded) {
                    tmpFile.deleteOnExit();
                } else {
                    if (!tmpFile.delete()) {
                        tmpFile.deleteOnExit();
                    }
                }
            }
        }
    }

    private static boolean isOSX() {
        return OSNAME.startsWith("macosx") || OSNAME.startsWith("osx");
    }

    public static boolean isLoaded() {
        return loaded;
    }
}
