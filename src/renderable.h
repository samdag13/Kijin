#pragma once

class Renderable
{
public:
    virtual void Draw() const = 0;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
};