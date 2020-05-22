#pragma once

#include <string>

#include "../Maze/Solver/Method.hpp"

namespace utils
{

struct Config
{
    std::string fileName{};
    std::string resultsFileName{};
    maze::solver::Method solver{maze::solver::Method::ENot_set};
    bool isGraphicOn{false};
    bool isCorrect{false};
};

}  // namespace utils
