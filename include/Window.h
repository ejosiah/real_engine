#pragma once

#include <real_common.h>
#include "events.h"
#include "GraphicsContext.h"

namespace real{

    class Window{
    public:

        virtual ~Window() = default;

        virtual Result init() = 0;

        virtual void pollEvents() const = 0;

        virtual void terminate() = 0;

        [[nodiscard]] inline bool resized() const {
            return _windowResized;
        };

        inline void resized(bool val) {
            _windowResized = val;
        }

        [[nodiscard]] virtual bool isVisible() const = 0;

        [[nodiscard]] virtual const GraphicsContext& getContext() const = 0;

        [[nodiscard]] inline glm::vec2 getWindowSize() const {
            return _dimensions;
        };

        inline void addMouseClickListener(MouseClickListener&& listener){
            mouseClickListeners.push_back(listener);
        }

        inline void addMouseMoveListener(MouseMoveListener&& listener){
            mouseMoveListeners.push_back(listener);
        }

        inline void addKeyPressListener(KeyPressListener&& listener){
            keyPressListeners.push_back(listener);
        }

        inline void addKeyReleaseListener(KeyReleaseListener&& listener){
            keyReleaseListeners.push_back(listener);
        }

        inline void addWindowResizeListeners(WindowResizeListener&& listener){
            windowResizeListeners.push_back(listener);
        }

    protected:
        inline void fireWindowResize(const ResizeEvent& event){
            for(auto& listener : windowResizeListeners){
                listener(event);
            }
        }

        inline void fireMouseClick(const MouseEvent& event){
            for(auto& listener : mouseClickListeners){
                listener(event);
            }
        }

        inline void fireMouseMove(const MouseEvent& event){
            for(auto& listener : mouseMoveListeners){
                listener(event);
            }
        }

        inline void fireKeyPress(const KeyEvent& event){
            for(auto& listener : keyPressListeners){
                listener(event);
            }
        }

        inline void fireKeyRelease(const KeyEvent& event){
            for(auto& listener : keyReleaseListeners){
                listener(event);
            }
        }

    protected:
        MouseEvent mouseEvent;
        KeyEvent keyEvent;
        ResizeEvent resizeEvent;
        bool _windowResized = false;
        glm::vec2 _dimensions;

    private:
        std::vector<MouseClickListener> mouseClickListeners;
        std::vector<MouseMoveListener> mouseMoveListeners;
        std::vector<KeyPressListener> keyPressListeners;
        std::vector<KeyReleaseListener> keyReleaseListeners;
        std::vector<WindowResizeListener> windowResizeListeners;
    };
}