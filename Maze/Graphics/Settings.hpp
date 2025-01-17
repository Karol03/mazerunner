#pragma once

#include <utility>

#define DRAW_SLOW   0
#define DRAW_NORMAL 1
#define DRAW_FAST   2

#define _600x600_ maze::graphics::Resolution{600, 600}
#define _640x480_ maze::graphics::Resolution{640, 480}
#define _800x600_ maze::graphics::Resolution{800, 600}
#define _800x800_ maze::graphics::Resolution{800, 800}
#define _1080x1080_ maze::graphics::Resolution{1080, 1080}
#define _1280x720_ maze::graphics::Resolution{1280, 720}
#define _1920x1080_ maze::graphics::Resolution{1920, 1080}

namespace maze
{
namespace graphics
{

using DrawSpeed = int;
using Resolution = std::pair<unsigned, unsigned>;

}  // namespace graphics
}  // namespace maze
