#include "Vertex.h"
#include "keys.h"
#include <fmt/format.h>

int main(){

    fmt::print("sizeof(Vertex) = {}\n", sizeof(real::Vertex));
    fmt::print("{}", static_cast<unsigned int>(real::Key::A));
    real::Key key = static_cast<real::Key>(64);
    fmt::print("\n{}", static_cast<unsigned int>(key));
    return 0;
}