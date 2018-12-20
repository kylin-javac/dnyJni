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
        callHellper->onError(THREAD_CHILD, FFMPEG_CAN_NOT_OPEN_URL);
        return;
    }
    //2.查找媒体流
    ret = avformat_find_stream_info(formatContext, 0);
    //小于0 失败
    if (ret < 0) {
        //查找资源失败
        callHellper->onError(THREAD_CHILD, FFMPEG_CAN_NOT_FIND_STREAMS);
        return;
    }
    //
    for (int i = 0; i < formatContext->nb_streams; ++i) {
        AVStream *stream = formatContext->streams[i];
        AVCodecParameters *codecpar = stream->codecpar;
        AVCodec *dec = avcodec_find_decoder(codecpar->codec_id);
        if (dec == NULL) {
            LOGE("查找解码器失败");
            callHellper->onError(THREAD_CHILD, FFMPEG_FIND_DECODER_FAIL);
            return;
        }
        //获取解码器的上下文
        AVCodecContext *context = avcodec_alloc_context3(dec);
        if (context == NULL) {
            LOGE("创建上下文失败");
            callHellper->onError(THREAD_CHILD, FFMPEG_ALLOC_CODEC_CONTEXT_FAIL);
            return;
        }
        //3、设置上下文内的一些参数 (context->width)
            //context->width = codecpar->width;
            //context->height = codecpar->height;
        ret = avcodec_parameters_to_context(context, codecpar);
        if (ret < 0) {
            LOGE("设置参数失败");
            callHellper->onError(THREAD_CHILD, FFMPEG_CODEC_CONTEXT_PARAMETERS_FAIL);
            return;
        }
        //打开解码器
        ret = avcodec_open2(context, dec, 0);
        if (ret != 0) {
            LOGE("打开解码器失败");
            callHellper->onError(THREAD_CHILD, FFMPEG_OPEN_DECODER_FAIL);
            return;
        }
        if (codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {//音频

        } else if (codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {//视频

        }
    }
    callHellper->onPrepare(THREAD_CHILD);
}


FCutils::~FCutils() {
    DELETE(dataSoruces);
    DELETE(callHellper);
}
