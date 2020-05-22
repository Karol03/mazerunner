#pragma once

#include <memory>
#include <string>

#include "FlatMap.hpp"

namespace maze
{

class MazeApp
{
public:
    int run(int argc, char** argv);

private:
    bool readFromFile(const std::string& fileName);
    auto decodeOptions(int argc, char** argv);

private:
    std::unique_ptr<FlatMap> m_flatMap;
};

}  // namespace maze
