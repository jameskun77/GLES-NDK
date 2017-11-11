//
// Created by Jameskun on 2017/11/11.
//
#include <jni.h>
#include <android/asset_manager_jni.h>

#include "RenderEngine.h"


extern "C" {
JNIEXPORT void JNICALL Java_com_example_jnitriangle_JNILib_init(JNIEnv* env,jobject obj,int width, int height,jobject jAssetMgr);
JNIEXPORT void JNICALL Java_com_example_jnitriangle_JNILib_step(JNIEnv* env,jobject obj);
};

JNIEXPORT void JNICALL Java_com_example_jnitriangle_JNILib_init(JNIEnv* env,jobject obj,int width, int height,jobject jAssetMgr)
{
    auto assetManager = AAssetManager_fromJava(env, jAssetMgr);
    RenderEngine::GetInstance().setupGraphics(width,height,assetManager);
}

JNIEXPORT void JNICALL Java_com_example_jnitriangle_JNILib_step(JNIEnv* env,jobject obj)
{
    RenderEngine::GetInstance().renderFrame();
}
