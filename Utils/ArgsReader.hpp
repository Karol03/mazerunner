#pragma once

#include "Config.hpp"

namespace utils
{

class ArgsReader
{
public:
    static Config parse(int argc, char** argv);

private:
    static bool isGraphicOn(char** argv);
    static int readDrawSpeed(char** argv);
    static int readSolver(char** argv);
};

}  // namespace utils

