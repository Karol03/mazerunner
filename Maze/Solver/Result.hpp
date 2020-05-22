#pragma once

#include "Method.hpp"
#include "Tools/Path.hpp"

namespace maze
{
namespace solver
{

struct Result
{
    static std::string header();
    std::string toString() const;

    tools::Path trace;
    tools::Path discovered;
    double time{0};
    unsigned width{0};
    unsigned height{0};
    Method method{Method::ENot_set};
};

}  // namespace maze
}  // namespace solver
