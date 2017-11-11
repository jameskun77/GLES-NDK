//
// Created by Jameskun on 2017/11/11.
//

#include "RenderEngine.h"
#include "Shader.h"
#include "Utility.h"

#define  RenderEngine_TAG  "InitEngine"
#define  Render_LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,RenderEngine_TAG,__VA_ARGS__)

class RenderEngine::Imp
{
public:
    GLuint mSurfaceWidth;
    GLuint mSurfaceHeight;

    Shader mShader;

    unsigned int mVAO;
    unsigned int mVBO;
};

RenderEngine::RenderEngine():mImpUPtr(std::make_unique<Imp>())
{
    auto& imp_ = *mImpUPtr;
    imp_.mVAO = Utility::genQuadVAO(imp_.mVBO);
}

RenderEngine::~RenderEngine()
{

}

RenderEngine& RenderEngine::GetInstance()
{
    static RenderEngine renderEngine;
    return  renderEngine;
}

bool RenderEngine::setupGraphics(int w,int h,AAssetManager* assetMgr)
{
    auto& imp_ = *mImpUPtr;

    if(0 == w || 0 == h || NULL == assetMgr)
    {
        Render_LOGE("setupGraphics param illegal");
        return false;
    }


    imp_.mShader.init("vertexShader.glsl","fragmentShader.glsl",assetMgr);

    imp_.mSurfaceWidth = w;
    imp_.mSurfaceHeight = h;

    glViewport(0, 0, w, h);

    return true;
}

void RenderEngine::renderFrame()
{
    auto& imp_ = *mImpUPtr;

    glClearColor(0.0f,0.2f,0.2f,1.0f);
    glClear( GL_COLOR_BUFFER_BIT);

    glBindVertexArray(imp_.mVAO);

    imp_.mShader.use();

    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    imp_.mShader.setMatrix4("model",model);

    glm::mat4 view;
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    imp_.mShader.setMatrix4("view",view);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float)imp_.mSurfaceWidth / (float)imp_.mSurfaceHeight, 0.1f, 10.0f);
    imp_.mShader.setMatrix4("projection",projection);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}



