package com.liu.testjni;

/**
 * Created by Liu on 2017/3/14.
 */
public class NdkJniUtils {
    public native String getCLanguageString();
    public native double[] wgs2bd(double[] latlng);

    static {
        System.loadLibrary("YanboberJniLibName");   //defaultConfig.ndk.moduleName
    }
}
