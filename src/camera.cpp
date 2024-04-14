#include "camera.h"

glm::mat4 camera::look_at()
{   
    glm::mat4 base {
        Right.x,     Right.y,     Right.z,     0.f,
        Up.x,        Up.y,        Up.z,        0.f,
        Direction.x, Direction.y, Direction.z, 0.f,
        0.f,         0.f,         0.f,         0.f
    };
    glm::mat4 pos {
        1.f, 0.f, 0.f, -Position.x,
        0.f, 1.f, 0.f, -Position.y,
        0.f, 0.f, 1.f, -Position.z,
        0.f, 0.f, 0.f, 0.f,
    };
    return base * pos; 
}
