#pragma once

#include "real_common.h"
#include <glm/glm.hpp>
#include "Camera.h"

namespace real {

    class Scene{
    public:
        explicit Scene(std::string_view name);

        virtual Result init();

        [[nodiscard]] inline std::string_view name() const{
            return _name;
        }

        inline const Camera& camera(){
            return activeCam->camera();
        }

        void update(float time);

        void resize(glm::vec2 dimensions);

    private:
        std::string_view _name;
        CameraController* activeCam;
        std::vector<CameraController> cameras;

    };
}