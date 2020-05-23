#pragma once

#include <utility>
#include <string>

namespace research
{
namespace tests
{

using Coordinates = std::pair<unsigned, unsigned>;

struct MazeConfig
{
    Coordinates size{};
    Coordinates beginPoint{};
    Coordinates endPoint{};
};

struct TestConfig
{
    std::string resultsFileName{};
    unsigned repetitionTimes{0};
    bool isDrawingOn{false};
};

}  // namespace tests
}  // namespace research
