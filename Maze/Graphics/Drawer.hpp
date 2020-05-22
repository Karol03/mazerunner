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
           FrameRate frames = _30_FPS);

    void display(const std::unique_ptr<solver::Result>& source);

private:
    Resolution m_resolution;
    FrameRate m_framerate;
};

}  // namspace graphics
}  // namespace maze
