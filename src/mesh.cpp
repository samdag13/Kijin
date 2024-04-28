
#include "gfx_core.h"
#include "vertex_array.h"
#include "index_buffer.h"
#include "mesh.h"
#include "vertex_buffer.h"
#include "texture.h"
#include "vertex_buffer_layout.h"

#pragma region MESH_INIT
Mesh::Mesh()
{
    VA = std::make_unique<VertexArray>();
}

Mesh::~Mesh()
{
}

void Mesh::SetTexture(const std::string &path)
{
    TexturePack = std::make_unique<Texture>(path);
}

void Mesh::SetVertices(float *vertices, unsigned int vertex_size, unsigned int vertex_count, unsigned int *indices, unsigned int index_count)
{
    VB = std::make_unique<VertexBuffer>(vertices, vertex_size * vertex_count);

    Layout = std::make_unique<VertexBufferLayout>();
    Layout->Push<float>(3);
    Layout->Push<float>(4);
    Layout->Push<float>(2);

    VA->AddBuffer(VB.get(), Layout.get());
    IB = std::make_unique<IndexBuffer>(indices, index_count);

    VA->Unbind();
    VB->Unbind();
    IB->Unbind();
}
#pragma endregion MESH_INIT

#pragma region RENDERABLE_INTERFACE

void Mesh::Draw() const
{
    GLCall(glDrawElements(GL_TRIANGLES, IB->GetCount(), GL_UNSIGNED_INT, nullptr));
}

void Mesh::Bind() const
{
    if (TexturePack)
        TexturePack->Bind();
    VA->Bind();
    IB->Bind();
}

void Mesh::Unbind() const
{
    VA->Unbind();
    IB->Unbind();
    if (TexturePack)
        TexturePack->Unbind();
}

#pragma endregion RENDERABLE_INTERFACE
