//
// Created by Steven on 2019/1/6.
//

#ifndef CAMERARECORDERDEMOAPP_FACEDETECTHELPER_H
#define CAMERARECORDERDEMOAPP_FACEDETECTHELPER_H

#include "../include/byted_effect_face_detect.h"
#include "../include/byted_effect_base_define.h"
#include <string>
#include <functional>
#include <malloc.h>
#include <pthread.h>
#include "../include/log.h"
#include "../include/TEUtils.h"

class FaceDetectHelper {
private:
    bool isBmpWriteThreadCreated = false;
    pthread_t bmpWriteThread;
    const char *mEffectLicense;
    const char *mEffectModelPath;

    std::function<void(int, bef_rect)> mDetectFaceCallback;

    byted_effect_handle_t mEffectHandler = NULL;

    void initEffectFaceDetectHandler();

    void destroyEffectHandler();

    char *copyStr(const char *str) {
        if (str == nullptr) return nullptr;
        int len = strlen(str);
        char *result = (char *) malloc(len + 1);
        memcpy(result, str, len);
        result[len] = '\0';
        return result;
    }

public:
    FaceDetectHelper();

    ~FaceDetectHelper();

    void setDetectFaceModelPath(const char *modelPath);

    void detectFace(const unsigned char *image, int pixelFormat, int width, int height,
                    int stride);

    void writeBMP();

    void setDetectFaceCallback(std::function<void(int, bef_rect)> callback) {
        mDetectFaceCallback = callback;
    }

    void setLicense(const char *license) {
        mEffectLicense = copyStr(license);
        LOGE("LICENSE 1 is %s ", mEffectLicense);
    }

};

#endif //CAMERARECORDERDEMOAPP_FACEDETECTHELPER_H
