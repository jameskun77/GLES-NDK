//
// Created by Jameskun on 2017/11/14.
//

#include <jni.h>
#include <android/asset_manager_jni.h>
#include <android/bitmap.h>
#include <android/log.h>
#include <GLES3/gl3.h>

#include "RenderEngine.h"

#define  NativeBridge_TAG  "NativeBridge"
#define  Bridge_LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,NativeBridge_TAG,__VA_ARGS__)

extern "C" {
JNIEXPORT void JNICALL Java_com_example_textureblend_JNILib_init(JNIEnv* env,jobject obj,int width, int height,jobject jAssetMgr);
JNIEXPORT void JNICALL Java_com_example_textureblend_JNILib_step(JNIEnv* env,jobject obj);
JNIEXPORT void JNICALL Java_com_example_textureblend_JNILib_setTextures(JNIEnv* env,jobject obj,jintArray texture);
JNIEXPORT void JNICALL Java_com_example_textureblend_JNILib_setTextureData(JNIEnv* env,jobject obj,int col,int row,jintArray textureData);
JNIEXPORT void JNICALL Java_com_example_textureblend_JNILib_setTextureBimap(JNIEnv* env,jobject obj,jobject jbitmap);
};

JNIEXPORT void JNICALL Java_com_example_textureblend_JNILib_init(JNIEnv* env,jobject obj,int width, int height,jobject jAssetMgr)
{
    auto assetManager = AAssetManager_fromJava(env, jAssetMgr);
    RenderEngine::GetInstance().setupGraphics(width,height,assetManager);
}

JNIEXPORT void JNICALL Java_com_example_textureblend_JNILib_step(JNIEnv* env,jobject obj)
{
    RenderEngine::GetInstance().renderFrame();
}

JNIEXPORT void JNICALL Java_com_example_textureblend_JNILib_setTextures(JNIEnv* env,jobject obj,jintArray texture)
{
    auto mTexture = (GLuint *)env->GetIntArrayElements(texture,0);
    RenderEngine::GetInstance().setTexture(*mTexture);
}

JNIEXPORT void JNICALL Java_com_example_textureblend_JNILib_setTextureData(JNIEnv* env,jobject obj,int col,int row,jintArray textureData)
{
    jint* cbuf;
    cbuf=env->GetIntArrayElements(textureData,NULL);
    RenderEngine::GetInstance().createTexture((unsigned char*)cbuf,col,row);
}

JNIEXPORT void JNICALL Java_com_example_textureblend_JNILib_setTextureBimap(JNIEnv* env,jobject obj,jobject jbitmap)
{
    int ret = 0;
    AndroidBitmapInfo bitmapInfo;
    void *pixels = NULL;
    int imgWidth = 2;
    int imgHeight = 2;


    if ((ret = AndroidBitmap_getInfo(env, jbitmap, &bitmapInfo)) < 0) {
        Bridge_LOGE("AndroidBitmap_getInfo error");
    }

    imgWidth = bitmapInfo.width;
    imgHeight = bitmapInfo.height;

    if (bitmapInfo.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        Bridge_LOGE("Java_com_example_hellojni_HelloJni_showBitmap invalid rgb format");
    }

    if ((ret = AndroidBitmap_lockPixels(env, jbitmap, &pixels)) < 0) {
        Bridge_LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
    }

    RenderEngine::GetInstance().createTexture((unsigned char*)pixels,imgWidth,imgHeight);

    AndroidBitmap_unlockPixels(env, jbitmap);
}