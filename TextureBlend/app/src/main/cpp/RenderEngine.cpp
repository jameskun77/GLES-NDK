//
// Created by Jameskun on 2017/11/14.
//

#include "RenderEngine.h"
#include "Shader.h"
#include "Utility.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
    unsigned int mEBO;
    unsigned int mTexture1;

public:
    void initVAO(AAssetManager* assetMgr)
    {
        float quadVertices[] = {
                //pos                 //color             //uv
                0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
                0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
                -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
                -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
        };

        unsigned int indices[] = {
                0,1,3,
                1,2,3
        };

        glGenVertexArrays(1, &mVAO);
        glGenBuffers(1, &mVBO);
        glGenBuffers(1,&mEBO);

        glBindVertexArray(mVAO);
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,mEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),&indices,GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);

    }
};


RenderEngine::RenderEngine():mImpUPtr(std::make_unique<Imp>())
{
    auto& imp_ = *mImpUPtr;
    //imp_.mVAO = Utility::genQuadVAO(imp_.mVBO);
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
    imp_.initVAO(assetMgr);

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
    imp_.mShader.setInt("texture1",0);

    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    imp_.mShader.setMatrix4("model",model);

    glm::mat4 view;
    view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    imp_.mShader.setMatrix4("view",view);

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), (float)imp_.mSurfaceWidth / (float)imp_.mSurfaceHeight, 0.1f, 10.0f);
    imp_.mShader.setMatrix4("projection",projection);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,imp_.mTexture1);

    //glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void RenderEngine::setTexture(unsigned int textureID)
{
    auto& imp_ = *mImpUPtr;

    imp_.mTexture1 = textureID;
}
