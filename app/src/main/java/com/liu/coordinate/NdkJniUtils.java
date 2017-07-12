package com.liu.coordinate;

/**
 * Created by Liu on 2017/3/14.
 */
public class NdkJniUtils {
    public native String getCLanguageString();
    public native double[] wgs2bd(double[] latlng);

    static {
        System.loadLibrary("CoordinateJniLib");   //defaultConfig.ndk.moduleName
    }
}
