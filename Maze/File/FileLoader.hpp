#pragma once

#include <string>

#include "../FlatMap.hpp"

namespace maze
{
namespace file
{

class FileLoader
{
public:
    FileLoader(std::string name);
    FlatMap* read();

private:
    std::string m_name;
};

}  // namespace file
}  // namespace maze
