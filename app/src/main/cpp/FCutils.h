//
// Created by Administrator on 2018/12/19.
//

#ifndef DNYJNI_FCUTILS_H
#define DNYJNI_FCUTILS_H

#include <pthread.h>
#include "JavaCallHellper.h"

extern "C" {
#include <libavformat/avformat.h>
};

class FCutils {
public:
    FCutils(JavaCallHellper *callHellper, const char *dataSources);

    ~FCutils();

    void prepare();

    void ffmpeg_preare();

private:
    char *dataSoruces;
    pthread_t pid;
    AVFormatContext *formatContext;
    JavaCallHellper *callHellper;
};

#endif //DNYJNI_FCUTILS_H
