#include <glm/glm.hpp>

#pragma once

namespace real{

    struct Camera{
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
    };

    class CameraController{
    public:

        inline const Camera& camera() { return _camera; }

    protected:
        Camera _camera;
    };
}
