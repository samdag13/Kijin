#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{

public:
    Camera();
    ~Camera();

    glm::mat4 look_at();

private:
    glm::vec2 FieldOfView;
    glm::vec2 AspectRatio;
    glm::vec2 NearFar;

    glm::vec3 Position;
    glm::vec3 Direction;
    glm::vec3 Right;
    glm::vec3 Up;

    glm::mat4x4 VP;
};