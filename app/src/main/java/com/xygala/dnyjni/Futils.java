package com.xygala.dnyjni;

public class Futils {
    static {
        System.loadLibrary("native-lib");
    }

    public void onError(int errorCode){
        System.out.println("Java接到回调:"+errorCode);
    }
    public void onPrepare(){
//        if (null != listener){
//            listener.onPrepare();
//        }
    }
    public native String stringFromJNI();

    public native void native_prepare(String dataSource);
}
