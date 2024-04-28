
#pragma once

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_buffer_layout.h"
#include "texture.h"

class mesh
{
public:
    mesh();
    ~mesh();

    void set_texture(texture t);
    void set_vertex_buff(set_vertex_buff vb);
    void set_index_buff(IndexBuffer ib);
    void set_vertex_arr(VertexArray va);

private:
    VertexBuffer VB;
    IndexBuffer IB;
    VertexBufferLayout VBLayout;
    VertexArray VA;
    Texture TexturePack;

    update_vb_layout();
};