#include "renderer.h"
#include "gfx_core.h"
#include "vertex_array.h"
#include "index_buffer.h"
#include "shader.h"
#include "mesh.h"

#include <iostream>

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{

    shader.Bind();
    va.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::DrawRenderables() const
{
    for (const std::unique_ptr<Renderable> &r : Renderables)
    {
        r->Bind();
        r->Draw();
        r->Unbind();
    }
}

void Renderer::AddRenderable(std::unique_ptr<Renderable> object)
{
    Renderables.push_back(std::move(object));
}
