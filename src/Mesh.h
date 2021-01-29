#pragma once
#include <tuple>
#include <vector>

using Mesh = std::tuple<std::vector<uint32_t>, std::vector<float>>;

#define Indices 0
#define Vertices 1