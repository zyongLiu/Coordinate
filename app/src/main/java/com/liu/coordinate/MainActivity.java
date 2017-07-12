package com.liu.coordinate;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import java.util.Random;

public class MainActivity extends AppCompatActivity {
    private TextView mTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mTextView = (TextView) findViewById(R.id.tv);

        Thread thread = new Thread(
                new Runnable() {
                    @Override
                    public void run() {
                        long startTime = System.currentTimeMillis();
                        for (int i = 0; i < 20000; i++) {
                            CoordinateBDUtil.wgs2bd(new double[]{
                                    (new Random().nextFloat() * 360) - 180
                                    , (new Random().nextFloat() * 180) - 90
                            });
                        }
                        System.out.println("CoordinateBDUtil完成2万个点,用时:" + (System.currentTimeMillis() - startTime));
                    }
                }
        );

        Thread thread2 = new Thread(new Runnable() {
            @Override
            public void run() {
                long startTime = System.currentTimeMillis();
                NdkJniUtils jni = new NdkJniUtils();
                for (int i = 0; i < 20000; i++) {
                    jni.wgs2bd(new double[]{
                            (new Random().nextFloat() * 360) - 180
                            , (new Random().nextFloat() * 180) - 90
                    });
                }
                System.out.println("JNI完成2万个点,用时:" + (System.currentTimeMillis() - startTime));
            }
        });


        thread2.start();
        thread.start();

    }

}
