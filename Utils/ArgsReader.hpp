#pragma once

#include "Config.hpp"

namespace utils
{

class ArgsReader
{
public:
    static Config parse(int argc, char** argv);

private:
    static int readSolver(char** argv);
    static bool isGraphicOn(char** argv);
};

}  // namespace utils

