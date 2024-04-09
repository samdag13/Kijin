#include "vertex_array.h"
#include "renderer.h"
#include "vertex_buffer_layout.h"

#include <cstdint>

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}

/* @brief: Binds thevertex array and the vertex buffer we want to set up with it. Also sets the vb layout
 */

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    Bind();
    vb.Bind();
    const std::vector<VertexBufferElement> &elements = layout.GetElements();
    unsigned int offset = 0;
    for (unsigned int i = 0; i < elements.size(); i++)
    {
        const auto &element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized,
                                     layout.GetStride(), reinterpret_cast<const void *>(static_cast<uintptr_t>(offset))));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}
