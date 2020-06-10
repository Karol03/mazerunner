#pragma once

#include <utility>
#include <string>

namespace research
{
namespace tests
{

using Coordinates = std::pair<unsigned, unsigned>;

enum class DrawningSpeed : int
{
    ESlow   = 0,
    ENormal = 1,
    EFast   = 2
};

struct MazeConfig
{
    std::string ownMazeName{};
    Coordinates size{};
    Coordinates beginPoint{};
    Coordinates endPoint{};
};

struct TestConfig
{
    std::string resultsFileName{};
    unsigned repetitionTimes{0};
    bool isDrawingOn{false};
    DrawningSpeed drawSpeed{DrawningSpeed::ENormal};
};

}  // namespace tests
}  // namespace research
