#include "com_liu_testjni_NdkJniUtils.h"
#define _USE_MATH_DEFINES
#include <stddef.h>
#include <android/log.h>
#include <Math.h>
#define LOG_TAG   "libplasma"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define EE 0.00669342162296594323
#define a 6378245.0
#define x_pi 3.14159265358979324 * 3000.0 / 180.0

double transformLat(double lat,double lon);
double transformLon(double lat, double lon);
void wgs2gcj1(double *array,double lat, double lon);
void gcj2bd1(double *array,double lat, double lon);

/*
 * Class:     io_github_yanbober_ndkapplication_NdkJniUtils
 * Method:    getCLanguageString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_liu_testjni_NdkJniUtils_getCLanguageString
  (JNIEnv *env, jobject obj){
     return (*env)->NewStringUTF(env,"This just a test for Android Studio NDK JNI developer!");
 }

double transformLat(double lat,double lon){
    double ret = -100.0 + 2.0 * lat + 3.0 * lon + 0.2 * lon * lon + 0.1 * lat * lon + 0.2 * sqrt(abs(lat));
       ret += (20.0 * sin(6.0 * lat * M_PI) + 20.0 * sin(2.0 * lat * M_PI)) * 2.0 / 3.0;
       ret += (20.0 * sin(lon * M_PI) + 40.0 * sin(lon / 3.0 * M_PI)) * 2.0 / 3.0;
       ret += (160.0 * sin(lon / 12.0 * M_PI) + 320 * sin(lon * M_PI  / 30.0)) * 2.0 / 3.0;
       return ret;
}

double transformLon(double lat, double lon) {
        double ret = 300.0 + lat + 2.0 * lon + 0.1 * lat * lat + 0.1 * lat * lon + 0.1 * sqrt(abs(lat));
        ret += (20.0 * sin(6.0 * lat * M_PI) + 20.0 * sin(2.0 * lat * M_PI)) * 2.0 / 3.0;
        ret += (20.0 * sin(lat * M_PI) + 40.0 * sin(lat / 3.0 * M_PI)) * 2.0 / 3.0;
        ret += (150.0 * sin(lat / 12.0 * M_PI) + 300.0 * sin(lat / 30.0 * M_PI)) * 2.0 / 3.0;
        return ret;
    }

    void wgs2gcj1(double *array,double lat, double lon) {
            double dLat = transformLat(lon - 105.0, lat - 35.0);
            double dLon = transformLon(lon - 105.0, lat - 35.0);
            double radLat = lat / 180.0 * M_PI;
            double magic = sin(radLat);
            magic = 1 - EE * magic * magic;
            double sqrtMagic = sqrt(magic);
            dLat = (dLat * 180.0) / ((a * (1 - EE)) / (magic * sqrtMagic) * M_PI);
            dLon = (dLon * 180.0) / (a / sqrtMagic * cos(radLat) * M_PI);
            double mgLat = lat + dLat;
            double mgLon = lon + dLon;
            array[0]=mgLat;
            array[1]=mgLon;
        }

void gcj2bd1(double *array,double lat, double lon) {
        double x = lon, y = lat;
        double z = sqrt(x * x + y * y) + 0.00002 * sin(y * x_pi);
        double theta = atan2(y, x) + 0.000003 * cos(x * x_pi);
        double bd_lon = z * cos(theta) + 0.0065;
        double bd_lat = z * sin(theta) + 0.006;
        array[0]=bd_lat;
        array[1]=bd_lon;
    }

JNIEXPORT jobjectArray JNICALL Java_com_liu_testjni_NdkJniUtils_wgs2bd
   (JNIEnv *env, jobject obj, jobjectArray arr){
   int len=(*env)->GetArrayLength(env,arr);
//   LOGE("LEN=%d\n",len);
   jdouble* elems=(*env)->GetDoubleArrayElements(env,arr,NULL);

   double lat=elems[0],lon=elems[1];

    double wgs2gcj[2]={0,0};
    double *array=wgs2gcj;
    wgs2gcj1(array,lat,lon);

    double gcj2bd[2] = {1, 1};
    double *array1=gcj2bd;
    gcj2bd1(array1,lat,lon);

//   LOGE("%f——————————————%f\n",lat,lon);
//   LOGE("%f———————wgs2gcj———————%f\n",wgs2gcj[0],wgs2gcj[1]);
//   LOGE("%f———————gcj2bd———————%f\n",gcj2bd[0],gcj2bd[1]);

    elems[0]=gcj2bd[0];
    elems[1]=gcj2bd[1];

   (*env)->SetDoubleArrayRegion(env,arr,0,len,elems);
   return arr;
 }
