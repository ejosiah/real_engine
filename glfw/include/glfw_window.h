#pragma once

#include "Window.h"
#include "GLFW/glfw3.h"
#include <glm/vec2.hpp>

namespace real{
    class GlfwWindow : Window {


        GlfwWindow(std::string title, glm::vec2 dim, bool full = false);

        virtual ~GlfwWindow();

        virtual WindowResult init() override;

        [[nodiscard]] bool isVisible() const override {
            return window != nullptr;
        };


        [[nodiscard]] virtual GraphicsContext getContext() const {
            return {};
        };

        [[nodiscard]] glm::vec2 getWindowSize() const {
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            return {width, height};
        };

        virtual void setWindowHints(){};

        static void OnError(int error, const char* desc);

        static void onKeyPress(GLFWwindow* window, int key, int scanCode, int action, int mods);

        static void onMouseMove(GLFWwindow* window, double x, double y);

        static void onMouseClick(GLFWwindow* window, int button, int action, int mods);

        static void onWindowResize(GLFWwindow* window, int width, int height);

        static GlfwWindow& getSelf(GLFWwindow* window);

    protected:
        std::string title;
        glm::vec2 dimensions;
        bool fullscreen;
        GLFWwindow* window;
        GLFWmonitor* monitor;
    };
}