package com.liu.testjni;

/**
 * Created by Liu on 2017/5/9.
 */
public class LatLng {
    private double lat;
    private double lon;

    public LatLng(double lat, double lon) {
        this.lat = lat;
        this.lon = lon;
    }

    public double getLat() {
        return lat;
    }

    public void setLat(double lat) {
        this.lat = lat;
    }

    public double getLon() {
        return lon;
    }

    public void setLon(double lon) {
        this.lon = lon;
    }
}