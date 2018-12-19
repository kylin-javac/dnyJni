//
// Created by Administrator on 2018/12/19.
//
#include "FCutils.h"
#include "string"
#include "macro.h"
#include "pthread.h"


//创建线程函数
void *task_prepare(void *args) {
    FCutils *fCutils = static_cast<FCutils *>(args);
    fCutils->ffmpeg_preare();
    return 0;
}

FCutils::FCutils(JavaCallHellper *callHellper, const char *dataSources) {
    this->callHellper = callHellper;
    this->dataSoruces = new char[strlen(dataSources)];
    strcpy(this->dataSoruces, dataSources);
}

void FCutils::prepare() {
    //创建一个线程
    pthread_create(&pid, 0, task_prepare, this);
}


//真正开始准备播放的地方
void FCutils::ffmpeg_preare() {
    //0.初始化网络
    avformat_network_init();
    formatContext = 0;
    //1.打开媒体地址
    int ret = avformat_open_input(&formatContext, dataSoruces, 0, 0);
    //ret !=0表示打开失败 ==0表示打开成功
    if (ret != 0) {
        //打开资源失败
        callHellper->onError(THREAD_CHILD,FFMPEG_CAN_NOT_OPEN_URL);
        return;
    }
    //2.查找媒体流
    ret=avformat_find_stream_info(formatContext,0);
    //小于0 失败
    if(ret<0){
        //查找资源失败
        callHellper->onError(THREAD_CHILD,FFMPEG_FIND_DECODER_FAIL);
        return;
    }
    //
    for (int i = 0; i < formatContext->nb_streams; ++i) {
        AVStream *stream=formatContext->streams[i];
        AVCodecParameters  *codecpar =  stream->codecpar;
    }
}


FCutils::~FCutils() {
    DELETE(dataSoruces);
    DELETE(callHellper);
}
