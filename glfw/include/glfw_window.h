#pragma once

#include "Window.h"
#include "GLFW/glfw3.h"
#include <glm/vec2.hpp>
#include "Settings.h"

namespace real{
    class GlfwWindow : public Window {
    public:
        GlfwWindow(std::string_view title, glm::vec2 dim, Settings settings);

        virtual ~GlfwWindow();

        Result init() override;

        void terminate() override;

        [[nodiscard]] bool isVisible() const override {
            return window != nullptr;
        };

        void pollEvents() const override;

        [[nodiscard]] const GraphicsContext& getContext()  const override {
            return gc;
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
        Settings settings;
        GLFWwindow* window;
        GLFWmonitor* monitor;

    private:
        GraphicsContext gc;
    };
}