#pragma once

#include <android/log.h>
#include <android/asset_manager_jni.h>

#include <GLES3/gl3.h>

#include <string>
#include <string.h>
#include <vector>
#include <assert.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define  Shader_TAG  "compileShader"
#define  SHADER_LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,Shader_TAG,__VA_ARGS__)

class Shader
{
public:
    Shader()
    {

    }

    void init(const GLchar* vertexPath, const GLchar* fragmentPath,AAssetManager* assetMgr)
    {
        mAssetMgr = assetMgr;

        std::vector<uint8_t> vertexCode;
        std::vector<uint8_t> fragmentCode;

        AAsset* assetFileVs = AAssetManager_open(mAssetMgr,vertexPath,AASSET_MODE_BUFFER);
        assert(assetFileVs);
        auto length = AAsset_getLength(assetFileVs);

        vertexCode.resize(length);
        memcpy(vertexCode.data(),AAsset_getBuffer(assetFileVs),length);
        AAsset_close(assetFileVs);

        AAsset* assetFileFs = AAssetManager_open(mAssetMgr,fragmentPath,AASSET_MODE_BUFFER);
        assert(assetFileFs);
        length = AAsset_getLength(assetFileFs);

        fragmentCode.resize(length);
        memcpy(fragmentCode.data(),AAsset_getBuffer(assetFileFs),length);
        AAsset_close(assetFileFs);

        const char* pVertexChar = (char*)vertexCode.data();
        const char* pFragmentChar = (char*)fragmentCode.data();

        unsigned int vertex,fragment;
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex,1,&pVertexChar,NULL);
        glCompileShader(vertex);
        _checkCompileError(vertex,"VERTEX");

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment,1,&pFragmentChar,NULL);
        glCompileShader(fragment);
        _checkCompileError(fragment,"FRAGMENT");

        mProgram = glCreateProgram();
        glAttachShader(mProgram,vertex);
        glAttachShader(mProgram,fragment);
        glLinkProgram(mProgram);

        _checkCompileError(mProgram,"PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void use()
    {
        glUseProgram(mProgram);
    }

    //uniform set
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(mProgram, name.c_str()), (int)value);
    }

    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(mProgram, name.c_str()), value);
    }

    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(mProgram, name.c_str()), value);
    }

    void setVec3(const std::string &name, const glm::vec3& value) const
    {
        glUniform3fv(glGetUniformLocation(mProgram, name.c_str()), 1, &value[0]);
    }

    void setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(mProgram, name.c_str()), x, y, z);
    }

    void setMatrix3(const std::string &name, const glm::mat3& mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void setMatrix4(const std::string &name, const glm::mat4& mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(mProgram, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:
    void _checkCompileError(unsigned int shader,std::string type)
    {
        GLint compiled;
        GLchar infoLog[1024];
        if(type != "PROGRAM")
        {
            glGetShaderiv(shader,GL_COMPILE_STATUS,&compiled);
            if(!compiled)
            {
                glGetShaderInfoLog(shader,1024,NULL,infoLog);
                SHADER_LOGE("Shader error: %s\n",infoLog);
            }
        }
        else
        {
            glGetProgramiv(shader,GL_LINK_STATUS,&compiled);
            if(!compiled)
            {
                glGetShaderInfoLog(shader,1024,NULL,infoLog);
                SHADER_LOGE("Program error: %s\n",infoLog);
            }
        }
    }

public:
    unsigned int mProgram{};
    AAssetManager* mAssetMgr{};
};