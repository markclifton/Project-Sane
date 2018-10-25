#pragma once

#include "../../drawable/drawablebasics.h"
#include "../vertexbuffer.h"

namespace buffers
{
    class BasicVBO : public VertexBuffer
    {
    public:
        inline void setAttribPointers() override
        {
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(drawable::Vertex), reinterpret_cast<void*>(offsetof(drawable::Vertex, pos)));
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(drawable::Vertex), reinterpret_cast<void*>(offsetof(drawable::Vertex, color)));
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(drawable::Vertex), reinterpret_cast<void*>(offsetof(drawable::Vertex, uv)));

            glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(drawable::Vertex), reinterpret_cast<void*>(0 * sizeof(glm::vec4) + offsetof(drawable::Vertex, model)));
            glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(drawable::Vertex), reinterpret_cast<void*>(1 * sizeof(glm::vec4) + offsetof(drawable::Vertex, model)));
            glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(drawable::Vertex), reinterpret_cast<void*>(2 * sizeof(glm::vec4) + offsetof(drawable::Vertex, model)));
            glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(drawable::Vertex), reinterpret_cast<void*>(3 * sizeof(glm::vec4) + offsetof(drawable::Vertex, model)));

            //TODO: Look into instancing more...
            //glVertexAttribDivisor(3, 1);
            //glVertexAttribDivisor(4, 1);
            //glVertexAttribDivisor(5, 1);
            //glVertexAttribDivisor(6, 1);
        }
    };
}