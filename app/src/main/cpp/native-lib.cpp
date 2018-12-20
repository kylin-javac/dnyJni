#include <jni.h>
#include <string>
#include <android/log.h>
#include "FCutils.h"



#define  LOGE(...) __android_log_print(ANDROID_LOG_ERROR,"JNI",__VA_ARGS__);
static const char *mClassName = "com/xygala/dnyjni/Futils";
JavaVM *javaVm = 0;
extern "C" JNIEXPORT jstring
stringFromJNI(JNIEnv *env) {
    std::string hello = "动态注册JNI方法......";
    LOGE("JNI stringFromJNI");
    return env->NewStringUTF(av_version_info());
}
extern "C" JNIEXPORT void
native_prepare(JNIEnv *env, jobject instance, jstring dataSource_) {
    const char* datas=env->GetStringUTFChars(dataSource_,0);
    JavaCallHellper *javaCallHellper=new JavaCallHellper(javaVm,env,instance);
    FCutils *fCutils=new FCutils(javaCallHellper,datas);
    fCutils->prepare();

};

static const JNINativeMethod method[] = {
        {"stringFromJNI",  "()Ljava/lang/String;",  (jstring *) stringFromJNI},
        {"native_prepare", "(Ljava/lang/String;)V", (void *) native_prepare}
};

int JNI_OnLoad(JavaVM *vm, void *re) {
    LOGE("init JNI");
    //
    javaVm = vm;
    // 获得JNIEnv
    JNIEnv *env = 0;
    // 小于0 失败 ，等于0 成功
    int r = vm->GetEnv((void **) &env, JNI_VERSION_1_2);
    if (r != JNI_OK) {
        return -1;
    }
    //获得 class对象
    jclass jcls = env->FindClass(mClassName);
    //注册
    env->RegisterNatives(jcls, method, sizeof(method) / sizeof(JNINativeMethod));
    LOGE("init JNI2");
    return JNI_VERSION_1_4;
}


