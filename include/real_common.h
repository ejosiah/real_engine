#pragma once

#include <vector>
#include <algorithm>
#include <string_view>
#include <tuple>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

#ifdef NDEBUG
constexpr bool debug = false;
#else
constexpr bool debug = true;

#endif

#define REPORT_ERROR(result) if(result.status == Status::FAILURE) throw std::runtime_error(result.message.data())

#define GET(result)  [&]{ \
    auto [outcome, value] = result; \
    REPORT_ERROR(outcome);       \
    return value;\
}();

namespace real {

    using Flags = unsigned int;


    enum class Status {
        SUCCESS, FAILURE
    };

    struct Result {
        std::string_view message;
        Status status;

        template<typename Func>
        Result map(Func &&func) {
            if (status == Status::FAILURE) return *this;
            return func();
        }
    };

    template<typename T>
    using Either_t = std::tuple<Result, T>;
}