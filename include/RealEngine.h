#pragma once

#include "InputManager.h"
#include "Window.h"
#include "Renderer.h"
#include "Scene.h"
#include <memory>
namespace real {
    class RealEngine {

    private:
        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<Window> window;
        std::unique_ptr<Scene> scene;
        InputManager inputManager;
    };
}