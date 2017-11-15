//
// Created by Jameskun on 2017/11/14.
//

#ifndef TEXTUREBLEND_RENDERENGINE_H
#define TEXTUREBLEND_RENDERENGINE_H

#include <memory>

class AAssetManager;

class RenderEngine
{
protected:
    class Imp;
    std::unique_ptr<Imp> mImpUPtr;

public:
    static RenderEngine& GetInstance();

private:
    RenderEngine();
    ~RenderEngine();

public:
    bool setupGraphics(int w,int h,AAssetManager* assetMgr);
    void renderFrame();
    void setTexture(unsigned int textureID);
};

#endif //TEXTUREBLEND_RENDERENGINE_H
