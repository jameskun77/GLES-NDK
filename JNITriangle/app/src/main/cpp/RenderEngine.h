//
// Created by Jameskun on 2017/11/11.
//

#ifndef JNITRIANGLE_RENDERENGINE_H
#define JNITRIANGLE_RENDERENGINE_H

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
};

#endif //JNITRIANGLE_RENDERENGINE_H
