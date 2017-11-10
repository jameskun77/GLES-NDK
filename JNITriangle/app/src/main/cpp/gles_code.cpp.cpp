//
// Created by Jameskun on 2017/11/10.
//

#include <jni.h>
#include <android/log.h>
#include <android/asset_manager_jni.h>

#include "Shader.h"

#define LOG_TAG "GLES_CODE"
#define GLESCODE_LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define GLESCODE_LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static void printGLString(const char *name, GLenum s)
{
    const char *v = (const char *) glGetString(s);
    GLESCODE_LOGI("GL %s = %s\n", name, v);
}

GLuint gProgram;
GLuint gvPositionHandle;
GLuint gSurfaceWidth;
GLuint gSurfaceHeight;

Shader gShader;

bool setupGraphics(int w,int h,AAssetManager* assetMgr)
{
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    gSurfaceWidth = w;
    gSurfaceHeight = h;

    gShader.init("vertexShader.glsl","fragmentShader.glsl",assetMgr);
    gProgram = gShader.getProgramID();

    if (!gProgram)
    {
        GLESCODE_LOGE("Could not create program.");
        return false;
    }

    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");

    glViewport(0, 0, w, h);
    return true;
}

const GLfloat gTriangleVertices[] = { 0.0f, 0.5f,0.0f, -0.5f, -0.5f,0.0f, 0.5f, -0.5f,0.0f };
void renderFrame()
{
    glClearColor(0.0f,0.0f,0.5f,1.0f);
    glClear( GL_COLOR_BUFFER_BIT);

    glUseProgram(gProgram);

    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    gShader.setMatrix4("model",model);

    glm::mat4 view;
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    gShader.setMatrix4("view",view);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float)gSurfaceWidth / (float)gSurfaceHeight, 0.1f, 10.0f);
    gShader.setMatrix4("projection",projection);

    glVertexAttribPointer(gvPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
    glEnableVertexAttribArray(gvPositionHandle);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

extern "C" {
JNIEXPORT void JNICALL Java_com_example_jnitriangle_JNILib_init(JNIEnv* env,jobject obj,int width, int height,jobject jAssetMgr);
JNIEXPORT void JNICALL Java_com_example_jnitriangle_JNILib_step(JNIEnv* env,jobject obj);
};

JNIEXPORT void JNICALL Java_com_example_jnitriangle_JNILib_init(JNIEnv* env,jobject obj,int width, int height,jobject jAssetMgr)
{
    auto assetManager = AAssetManager_fromJava(env, jAssetMgr);
    setupGraphics(width, height,assetManager);
}

JNIEXPORT void JNICALL Java_com_example_jnitriangle_JNILib_step(JNIEnv* env,jobject obj)
{
    renderFrame();
}