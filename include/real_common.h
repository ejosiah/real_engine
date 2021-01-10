#pragma once

#include <string_view>

namespace real{

    using Flags = unsigned int;

    template<typename StatusCode>
    struct ResultType{
        std::string_view message;
        StatusCode statusCode;
    };
}