#include <glm/glm.hpp>
#include <array>
#include <vector>

namespace real{
    constexpr int MAX_UVS = 4;

    struct Vertex{
        glm::vec4 position = {0, 0, 0, 1};
        glm::vec3 normal = {0, 1, 0};
        glm::vec3 tangent = {1, 0, 0};
        glm::vec3 bitangent = {0, 0, 1};
        glm::vec3 color = glm::vec3(1);
        std::array<glm::vec2, MAX_UVS> uvs;
    };


    struct VertexInstanceData{
        glm::vec3 color = glm::vec3(1);
        glm::mat4 xform = glm::mat4(1);
    };

    using Mesh = std::vector<Vertex>;
    using MeshInstanceData = std::vector<Vertex>;
}