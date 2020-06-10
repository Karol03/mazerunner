#include "Drawer.hpp"

#include <algorithm>
#include <functional>
#include <sstream>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../../Utils/Logger.hpp"

#define _1_SECOND_ 1000u

#ifdef _WIN32
    #include <windows.h>

    void sleep(unsigned milliseconds)
    {
        if (milliseconds > 0)
            Sleep(milliseconds);
    }
#else
    #include <unistd.h>

    void sleep(unsigned milliseconds)
    {
        if (milliseconds > 0)
            usleep(milliseconds * 1000); // takes microseconds
    }
#endif

namespace maze
{
namespace graphics
{
namespace details
{
namespace
{
const auto VERTEXES_IN_QUAD = 4;
}  // namespace

sf::RenderWindow prepareWindow(const std::string& title,
                               const Resolution& resolution)
{
    return sf::RenderWindow(sf::VideoMode(resolution.first, resolution.second),
                            title);
}

sf::Vertex* prepareMap(const FlatMap& map, const Resolution& resolution)
{
    const auto mapsize = map.size();
    auto rectangles = new sf::Vertex[mapsize.width * mapsize.height * VERTEXES_IN_QUAD]();

    auto w = static_cast<float>(resolution.first)/static_cast<float>(mapsize.width);
    auto h = static_cast<float>(resolution.second)/static_cast<float>(mapsize.height);

    for(auto i{0u}; i < mapsize.height; ++i)
    {
        for(auto j{0u}; j < mapsize.width; ++j)
        {
            const auto x = static_cast<float>(j) * w;
            const auto y = static_cast<float>(i) * h;
            const auto quadNo = (i * mapsize.width + j) * VERTEXES_IN_QUAD;
            auto* quad = &rectangles[quadNo];

            quad[0].position = sf::Vector2f(x, y);
            quad[1].position = sf::Vector2f(x + w, y);
            quad[2].position = sf::Vector2f(x + w, y + h);
            quad[3].position = sf::Vector2f(x, y + h);

            if (map.isAvailable(j, i))
            {
                quad[0].color = sf::Color::White;
                quad[1].color = sf::Color::White;
                quad[2].color = sf::Color::White;
                quad[3].color = sf::Color::White;
            }
            else
            {
                quad[0].color = sf::Color::Black;
                quad[1].color = sf::Color::Black;
                quad[2].color = sf::Color::Black;
                quad[3].color = sf::Color::Black;
            }
        }
    }
    return rectangles;
}

void draw(sf::RenderWindow* window,
          sf::Vertex* rectangles,
          std::size_t size)
{
    window->clear();
    window->draw(rectangles, size * VERTEXES_IN_QUAD, sf::Quads);
    window->display();
}

bool isExitPressed(sf::RenderWindow* window)
{
    sf::Event event;
    if (not window->isOpen())
    {
        return true;
    }
    while(window->pollEvent(event)) {
        switch(event.type) {
            case sf::Event::Closed:
                window->close();
                return true;
            break;
            default:
            break;
        }
    }
    return false;
}

void colorQuadRed(sf::Vertex* quad)
{
    quad[0].color = sf::Color::Red;
    quad[1].color = sf::Color::Red;
    quad[2].color = sf::Color::Red;
    quad[3].color = sf::Color::Red;
}

void colorQuadBlue(sf::Vertex* quad)
{
    quad[0].color = sf::Color::Blue;
    quad[1].color = sf::Color::Blue;
    quad[2].color = sf::Color::Blue;
    quad[3].color = sf::Color::Blue;
}

bool drawPath(sf::RenderWindow* window,
              sf::Vertex* rectangles,
              const unsigned width,
              const std::size_t size,
              solver::tools::Path& path,
              std::function<void(sf::Vertex*)> fillFunc,
              unsigned frameDelay)
{
    for (const auto& step : path.trace())
    {
        if (isExitPressed(window))
        {
            LOG("Exit");
            return true;
        }
        const auto position = (step.y * width + step.x) * VERTEXES_IN_QUAD;
        auto* currentQuad = &rectangles[position];
        fillFunc(currentQuad);
        draw(window, rectangles, size);
        sleep(frameDelay);
    }
    return false;
}


void presentPath(sf::RenderWindow* window,
                 sf::Vertex* rectangles,
                 const unsigned size,
                 const unsigned width,
                 solver::tools::Path& discovered,
                 solver::tools::Path& trace,
                 unsigned frameDelay)
{
    auto isExit = false;
    isExit = details::drawPath(window,
                               rectangles,
                               width,
                               size,
                               discovered,
                               &colorQuadRed,
                               frameDelay);
    sleep(_1_SECOND_);
    isExit = details::drawPath(window,
                               rectangles,
                               width,
                               size,
                               trace,
                               &colorQuadBlue,
                               frameDelay);
    if (isExit)
    {
        return;
    }
    while (not isExitPressed(window));
    LOG("Presenting finished. Press 'x' to exit");
}

}  // namespace details


Drawer::Drawer(Resolution resolution, DrawSpeed drawSpeed)
    : m_resolution{std::move(resolution)}
    , m_drawSpeed{drawSpeed}
{}

void Drawer::display(const std::unique_ptr<solver::Result>& source)
{
    if (not source)
    {
        LOG("No result to display");
        return;
    }
    LOG("Displaying..");

    std::stringstream title;
    title << "Maze solving by " << source->method;

    auto window = details::prepareWindow(title.str(), m_resolution);
    window.clear();

    auto rectangles = details::prepareMap(*source->map, m_resolution);
    const auto size = source->map->size().width * source->map->size().height;

    details::draw(&window, rectangles, size);

    details::presentPath(&window,
                         rectangles,
                         size,
                         source->map->size().width,
                         source->discovered,
                         source->trace,
                         frameDelay(m_drawSpeed));
    delete [] rectangles;
    window.close();
}

unsigned Drawer::frameDelay(int drawspeed)
{
    if (drawspeed == DRAW_NORMAL)
    {
        return 5u;
    }
    else if (drawspeed == DRAW_SLOW)
    {
        return 25u;
    }
    return 0u;
}

}  // namspace graphics
}  // namespace maze

