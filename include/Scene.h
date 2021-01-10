#include <glm/glm.hpp>

namespace real {

    class Scene{
    public:
        virtual void init(){};

        bool requireMouse() const;

        void update(float time);

        void resize(const glm::vec2 dimensions);
    };
}