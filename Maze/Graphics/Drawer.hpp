#pragma once

#include "Settings.hpp"
#include "../Solver/Result.hpp"

namespace maze
{
namespace graphics
{

class Drawer
{
public:
    Drawer(Resolution resolution = _800x600_,
           DrawSpeed drawSpeed = DRAW_NORMAL);

    void display(const std::unique_ptr<solver::Result>& source);

private:
    unsigned frameDelay(int drawspeed);

private:
    Resolution m_resolution;
    DrawSpeed m_drawSpeed;
};

}  // namspace graphics
}  // namespace maze
