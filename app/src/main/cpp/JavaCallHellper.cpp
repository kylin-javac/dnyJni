#include "JavaCallHellper.h"
#include "macro.h"

JavaCallHellper::JavaCallHellper(JavaVM *vm, JNIEnv *env, jobject instance) {
    this->vm = vm;
    this->env = env;
    // 一旦涉及到jobject 跨方法 跨线程 就需要创建全局引用
    this->instance = env->NewGlobalRef(instance);
    jclass clzz = env->GetObjectClass(instance);
    onErrorId = env->GetMethodID(clzz, "onError", "(I)V");
    onPrepareId = env->GetMethodID(clzz, "onPrepare", "()V");
}

void JavaCallHellper::onError(int threadId, int errorId) {
    if (threadId == THREAD_MAIN) {
        env->CallVoidMethod(instance, onErrorId, errorId);
    } else {
        JNIEnv *env1;
        vm->AttachCurrentThread(&env1, 0);
        env1->CallVoidMethod(instance, onErrorId, errorId);
        vm->DetachCurrentThread();
    }
}

void JavaCallHellper::onPrepare(int threadId) {
    if (threadId == THREAD_MAIN) {
        env->CallVoidMethod(instance, onPrepareId);
    } else {
        JNIEnv *env1;
        vm->AttachCurrentThread(&env1, 0);
        env1->CallVoidMethod(instance, onPrepareId);
        vm->DetachCurrentThread();
    }

}

JavaCallHellper::~JavaCallHellper() {
    env->DeleteGlobalRef(instance);
}