#pragma once

#include "renderable.h"

class VertexArray;
class IndexBuffer;
class Shader;
class Mesh;

class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
    void DrawRenderables() const;
    void AddRenderable(std::unique_ptr<Renderable> object);

private:
    std::list<std::unique_ptr<Renderable>> Renderables;
};