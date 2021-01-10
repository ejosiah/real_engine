#include "RealEngine.h"

namespace real {

    RealEngine::RealEngine(std::unique_ptr<Renderer> renderer, std::unique_ptr<Window> window,
                           std::unique_ptr<Scene> scene)
            : renderer(std::move(renderer))
            , window(std::move(window))
            , scene(std::move(scene)) {}

    void RealEngine::run() {
        init();
        mainLoop();
        shutdown();
    }

    void RealEngine::init() {
        window->init();
        scene->init();
        inputManager.init(*scene);
        renderer->init(window->getContext(), *scene);
    }

    void RealEngine::mainLoop() {
        while(window->isVisible()){
            window->pollEvents();
            inputManager.processEvents();
            // TODO timer update
            float currentTime = 0;
            scene->update(currentTime);
            renderer->render(*scene);
        }
    }
}
