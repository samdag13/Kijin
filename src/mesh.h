
#pragma once
#include "renderable.h"

class Texture;
class VertexBuffer;
class IndexBuffer;
class VertexArray;
class VertexBufferLayout;
class Mesh : public Renderable
{
public:
    Mesh();
    ~Mesh();

    void SetTexture(const std::string &path);
    void SetVertices(float *vertices, unsigned int vertex_size, unsigned int vertex_count, unsigned int *indices, unsigned int index_count);

#pragma region RENDERABLE_INTERFACE
    void Draw() const override;
    void Bind() const override;
    void Unbind() const override;
#pragma endregion RENDERABLE_INTERFACE

private:
    std::unique_ptr<VertexBuffer> VB;
    std::unique_ptr<IndexBuffer> IB;
    std::unique_ptr<VertexArray> VA;
    std::unique_ptr<Texture> TexturePack;
    std::unique_ptr<VertexBufferLayout> Layout;
};