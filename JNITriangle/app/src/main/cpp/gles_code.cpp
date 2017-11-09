//
// Created by Jameskun on 2017/11/3.
//

#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <vector>
#include <string.h>

#include <android/asset_manager_jni.h>

#define LOG_TAG "jnigles2"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

auto gVertexShader =
        "attribute vec4 vPosition;\n"
        "void main() {\n"
        "  gl_Position = vPosition;\n"
        "}\n";

auto gFragmentShader =
        "precision mediump float;\n"
        "void main() {\n"
        "  gl_FragColor = vec4(0.0, 0.8, 0.0, 1.0);\n"
        "}\n";

GLuint loadShader(GLenum shaderType,const char* sourcePath,AAssetManager* assetMgr)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader)
    {
        AAsset* assetFile = AAssetManager_open(assetMgr,sourcePath,AASSET_MODE_BUFFER);
        assert(assetFile);
        auto length = AAsset_getLength(assetFile);

        std::vector<uint8_t > buf;
        buf.resize(length);
        memcpy(buf.data(),AAsset_getBuffer(assetFile),length);
        AAsset_close(assetFile);

        const char* pSource = (char*)buf.data();
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen)
            {
                char* buf = (char*) malloc(infoLen);
                if (buf)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint loadShader(GLenum shaderType,const char* shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader)
    {

        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen)
            {
                char* buf = (char*) malloc(infoLen);
                if (buf)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource,AAssetManager* assetMgr)
{
    //GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, "vertexShader.glsl",assetMgr);
    if (!vertexShader)
    {
        return 0;
    }

    //GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER,"fragmentShader.glsl", assetMgr);
    if (!pixelShader)
    {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program)
    {
        glAttachShader(program, vertexShader);
        glAttachShader(program, pixelShader);
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength)
            {
                char* buf = (char*) malloc(bufLength);
                if (buf)
                {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint gProgram;
GLuint gvPositionHandle;

bool setupGraphics(int w,int h,AAssetManager* assetMgr)
{
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    gProgram = createProgram(gVertexShader, gFragmentShader,assetMgr);
    if (!gProgram)
    {
        LOGE("Could not create program.");
        return false;
    }
    gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");

    glViewport(0, 0, w, h);
    return true;
}

const GLfloat gTriangleVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f };
void renderFrame()
{
    glClearColor(0.0f,0.0f,0.5f,1.0f);
    glClear( GL_COLOR_BUFFER_BIT);

    glUseProgram(gProgram);

    glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
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