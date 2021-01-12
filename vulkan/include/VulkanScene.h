#pragma once
#include "Scene.h"

namespace vkn{
    class VulkanScene : public real::Scene{
    public:
        explicit VulkanScene(std::string_view name);

        real::Result init() override;

    };
}