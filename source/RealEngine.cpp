#include <stdexcept>
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
        REPORT_ERROR(window->init());
        REPORT_ERROR(scene->init());
        REPORT_ERROR(inputManager.init(*scene));
        REPORT_ERROR(renderer->init(window->getContext(), *scene));
    }

    void RealEngine::mainLoop() {
        while(window->isVisible()){
            if(window->resized()){
                window->resized(false);
                scene->resize(window->getWindowSize());
                renderer->resize(window->getWindowSize());
                continue;
            }

            window->pollEvents();
            inputManager.processEvents();

            // TODO timer update
            float currentTime = 0;
            scene->update(currentTime);
            renderer->render(*scene);
        }
    }

    void RealEngine::shutdown() {

    }
}
