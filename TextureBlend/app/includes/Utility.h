//
// Created by Jameskun on 2017/11/11.
//
#include <GLES3/gl3.h>


#ifndef JNITRIANGLE_UTILITY_H
#define JNITRIANGLE_UTILITY_H

class Utility
{
public:

    static unsigned int genQuadVAO(unsigned int& VBO)
    {
        unsigned int quadVAO;

        float quadVertices[] = {

                 0.0f,  0.5f, 0.0f,
                -0.5f,  0.0f, 0.0f,
                 0.5f,  0.0f, 0.0f,
        };

        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        return quadVAO;
    }
};

#endif //JNITRIANGLE_UTILITY_H
