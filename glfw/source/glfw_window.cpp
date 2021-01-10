#include "glfw_window.h"

namespace real{

    GlfwWindow::GlfwWindow(std::string title, glm::vec2 dim, bool full)
    : title(title)
    , dimensions(dim)
    , fullscreen(full)
    , window(nullptr)
    , monitor(nullptr)
    {

    }

    GlfwWindow::~GlfwWindow(){
        if(window){
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        glfwDestroyWindow(window);
        glfwTerminate();
        window = nullptr;
    }

    Window::WindowResult GlfwWindow::init() {

        glfwSetErrorCallback(OnError);

       auto status = glfwInit();

       if(!status) return { "Glfw initialization failed", Status::FAILURE};
       setWindowHints();
       monitor = fullscreen ? glfwGetPrimaryMonitor() : nullptr;

       glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
       window = glfwCreateWindow(dimensions.x, dimensions.y, title.c_str(), monitor, nullptr);

       if(!window){
           glfwTerminate();
           return { "GLFW window initialization failed!", Status::FAILURE};
       }

       glfwSetWindowUserPointer(window, this);

       glfwSetKeyCallback(window, onKeyPress);
       glfwSetMouseButtonCallback(window, onMouseClick);
       glfwSetCursorPosCallback(window, onMouseMove);
       glfwSetFramebufferSizeCallback(window, onWindowResize);

       return { "GLFW successfully initialized", Status::SUCCESS};
    }

    GlfwWindow& GlfwWindow::getSelf(GLFWwindow *window) {
        return *reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
    }

    void GlfwWindow::OnError(int error, const char* desc){

    }

    void GlfwWindow::onKeyPress(GLFWwindow *window, int key, int scanCode, int action, int mods) {
        auto self = getSelf(window);
    }

    void GlfwWindow::onMouseMove(GLFWwindow *window, double x, double y) {
        auto self = getSelf(window);
        self.mouseEvent.pos.x = static_cast<float>(x);
        self.mouseEvent.pos.y = static_cast<float>(y);
        self.fireMouseMove(self.mouseEvent);
    }

    void GlfwWindow::onMouseClick(GLFWwindow *window, int button, int action, int mods) {
        auto self = getSelf(window);
        auto& mouseEvent = self.mouseEvent;
        switch(button){
            case GLFW_MOUSE_BUTTON_LEFT:
                mouseEvent.button = MouseEvent::Button::LEFT;
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                mouseEvent.button = MouseEvent::Button::RIGHT;
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                mouseEvent.button = MouseEvent::Button::MIDDLE;
                break;
            default:
                mouseEvent.button = MouseEvent::Button::NONE;
        }

        switch(action){
            case GLFW_PRESS:
                mouseEvent.state = MouseEvent::State::PRESS;
                break;
            case GLFW_RELEASE:
                mouseEvent.state = MouseEvent::State::RELEASE;
                break;
            default:
                mouseEvent.state = MouseEvent::State::NONE;
        }
        // TODO mods
        self.fireMouseClick(mouseEvent);
    }

    void GlfwWindow::onWindowResize(GLFWwindow *window, int width, int height) {
        auto self = getSelf(window);
        self.resizeEvent.extent.x = static_cast<float>(width);
        self.resizeEvent.extent.y = static_cast<float>(height);
        self.fireWindowResize(self.resizeEvent);
    }

}