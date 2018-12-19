//
// Created by Administrator on 2018/12/19.
//
#include <jni.h>

#ifndef DNYJNI_JAVACALLHELLPER_H
#define DNYJNI_JAVACALLHELLPER_H

class JavaCallHellper {
public:
    JavaCallHellper(JavaVM *vm, JNIEnv *env, jobject instance);

    ~JavaCallHellper();

    //回调java的方法
    void onError(int threadId, int errorId);

    void onPrepare(int threadId);

private:
    JavaVM *vm;
    JNIEnv *env;
    jobject instance;
    jmethodID onErrorId;
    jmethodID onPrepareId;
};

#endif //DNYJNI_JAVACALLHELLPER_H
