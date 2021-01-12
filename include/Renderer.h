#pragma once

#include "GraphicsContext.h"
#include "Scene.h"

namespace real {

    class Renderer{
    public:
        virtual Result init(const GraphicsContext& gContext, const Scene& scene) = 0;

        virtual void render(const Scene& scene) = 0;

        virtual void resize(const glm::vec2& dimensions) = 0;
    };
}