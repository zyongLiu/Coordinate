package com.liu.testjni;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private TextView mTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mTextView= (TextView) findViewById(R.id.tv);
//        NdkJniUtils jni = new NdkJniUtils();
//
//        double[] r=jni.wgs2bd(new double[]{123D,321D});
//        mTextView.setText(jni.getCLanguageString()+"/n"+r[0]+","+r[1]);

        Thread thread=new Thread(
                new Runnable() {
                    @Override
                    public void run() {
                        long startTime=System.currentTimeMillis();
                        for (int i=0;i<1000;i++){
                            CoordinateBDUtil.wgs2bd(new double[]{123D,321D});
                        }
                        System.out.println("CoordinateBDUtil完成,用时:"+(System.currentTimeMillis()-startTime));
                    }
                }
        );

       Thread thread2= new Thread(new Runnable() {
            @Override
            public void run() {
                long startTime=System.currentTimeMillis();
                NdkJniUtils jni = new NdkJniUtils();
                for (int i=0;i<1000;i++){
                    jni.wgs2bd(new double[]{123D,321D});
                }
                System.out.println("JNI完成,用时:"+(System.currentTimeMillis()-startTime));
            }
        });


        thread2.start();
        thread.start();

    }

}
