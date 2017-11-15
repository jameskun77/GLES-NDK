//
// Created by Jameskun on 2017/11/14.
//

#include <jni.h>
#include <android/asset_manager_jni.h>
#include <GLES3/gl3.h>

#include "RenderEngine.h"


extern "C" {
JNIEXPORT void JNICALL Java_com_example_textureblend_JNILib_init(JNIEnv* env,jobject obj,int width, int height,jobject jAssetMgr);
JNIEXPORT void JNICALL Java_com_example_textureblend_JNILib_step(JNIEnv* env,jobject obj);
JNIEXPORT void JNICALL Java_com_example_textureblend_JNILib_setTextures(JNIEnv* env,jobject obj,jintArray texture);
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