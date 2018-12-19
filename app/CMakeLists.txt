cmake_minimum_required(VERSION 3.4.1)
# 创建一个变量 source_file 它的值就是src/main/cpp/ 所有的.cpp文件
file(GLOB source_file src/main/cpp/*.cpp)
add_library(
             native-lib
             SHARED
             ${source_file} )

include_directories(src/main/cpp/include)
set(USE_NDK_UNIFIED_HEADERS TRUE) # TRUE or FALSE

if (${USE_NDK_UNIFIED_HEADERS})
    if (${ANDROID_ABI} STREQUAL "x86_64")
        include_directories(${ANDROID_SYSROOT}/usr/include/x86_64-linux-android)
    elseif (${ANDROID_ABI} STREQUAL "x86")
        include_directories(${ANDROID_SYSROOT}/usr/include/i686-linux-android)
    elseif (${ANDROID_ABI} STREQUAL "arm64-v8a")
        include_directories(${ANDROID_SYSROOT}/usr/include/aarch64-linux-android)
    elseif (${ANDROID_ABI} MATCHES "^armeabi(-v7a)?$")
        include_directories(${ANDROID_SYSROOT}/usr/include/arm-linux-androideabi)
    elseif (${ANDROID_ABI} STREQUAL "mips")
        include_directories(${ANDROID_SYSROOT}/usr/include/mipsel-linux-android)
    elseif (${ANDROID_ABI} STREQUAL "mips64")
        include_directories(${ANDROID_SYSROOT}/usr/include/mips64el-linux-android)
    endif()
endif()
set(CMAKE_SYSTEM_VERSION 16)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGES} -L${CMAKE_SOURCE_DIR}/src/main/cpp/libs/${ANDROID_ABI}")
target_link_libraries(
                        native-lib
                        avformat avcodec avfilter    avutil swresample swscale
                        log z)
