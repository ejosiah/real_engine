#pragma once

#include "InputManager.h"
#include "Window.h"
#include "Renderer.h"
#include "Scene.h"
#include <memory>
namespace real {
    class RealEngine {
    public:
        RealEngine(std::unique_ptr<Renderer> renderer, std::unique_ptr<Window> window, std::unique_ptr<Scene> scene);

        void run();

    private:
        void init();

        void mainLoop();

        void shutdown();

    private:
        std::unique_ptr<Renderer> renderer;
        std::unique_ptr<Window> window;
        std::unique_ptr<Scene> scene;
        InputManager inputManager;
        bool windowResized;
    };
}