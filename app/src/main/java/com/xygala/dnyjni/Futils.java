package com.xygala.dnyjni;

public class Futils {
    static {
        System.loadLibrary("native-lib");
    }

    public void onError(int errorCode){
        System.out.println("Java接到回调:666666666666"+errorCode);
    }
    public void onPrepare(){
        System.out.println("可以播放了..........");
    }
    public native String stringFromJNI();

    public native void native_prepare(String dataSource);
}
