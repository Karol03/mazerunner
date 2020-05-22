#pragma once

#include <memory>
#include "../Solver/Result.hpp"

namespace maze
{
namespace file
{

class ResultsSaver
{
public:
    explicit ResultsSaver(std::string fileName);
    void save(const std::unique_ptr<solver::Result>& results);

private:
    bool isEmpty(std::ofstream& file) const;
    void addHeader(std::ofstream& file) const;

private:
    std::string m_fileName;
};

}  // namespace file
}  // namespace maze
