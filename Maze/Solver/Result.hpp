#pragma once

#include "Method.hpp"
#include "Tools/Path.hpp"
#include "../FlatMap.hpp"

namespace maze
{
namespace solver
{

struct Result
{
    static std::string header();
    std::string toString() const;

    std::unique_ptr<FlatMap> map;
    tools::Path trace;
    tools::Path discovered;
    double time{0};
    Method method{Method::ENot_set};
};

}  // namespace maze
}  // namespace solver
