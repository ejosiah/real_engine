#include "real_common.h"
#include "VulkanEngineFactory.h"
#include "Vertex.h"
#include "keys.h"
#include <fmt/format.h>
#include <spdlog/spdlog.h>


int main(){
    if(debug) {
        spdlog::set_level(spdlog::level::debug);
    }

    real::Settings settings;

    auto engine = vkn::createEngine(
            "Test"
            , {800, 600}
            , settings
            , std::make_unique<vkn::VulkanScene>("Test Scene"), debug);

    try{
        engine.run();
    }catch(std::runtime_error& err){
        spdlog::error(err.what());
    }

    return 0;
}