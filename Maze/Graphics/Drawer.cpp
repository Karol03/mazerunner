#include "Drawer.hpp"

#include <algorithm>
#include <sstream>
#include <chrono>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../../Utils/Logger.hpp"

#define _3_SECONDS_ 3000u

#ifdef _WIN32
    #include <windows.h>

    void sleep(unsigned milliseconds)
    {
        Sleep(milliseconds);
    }
#else
    #include <unistd.h>

    void sleep(unsigned milliseconds)
    {
        usleep(milliseconds * 1000); // takes microseconds
    }
#endif

namespace maze
{
namespace graphics
{
namespace details
{

sf::RenderWindow* prepareWindow(const std::string& title,
                                const Resolution& resolution)
{
    sf::RenderWindow* window;
    window = new sf::RenderWindow(sf::VideoMode(resolution.first, resolution.second),
                                  title);
    window->clear();
    return window;
}

sf::RectangleShape* prepareMap(const FlatMap& map, const Resolution& resolution)
{
    const auto mapsize = map.size();
    sf::RectangleShape* rectangles
            = new sf::RectangleShape[mapsize.width * mapsize.height];

    auto w = static_cast<float>(resolution.first)/static_cast<float>(mapsize.width);
    auto h = static_cast<float>(resolution.second)/static_cast<float>(mapsize.height);

    for(auto i{0u}; i < mapsize.height; ++i)
    {
        for(auto j{0u}; j < mapsize.width; ++j)
        {
            const auto block = i * mapsize.width + j;
            const auto x = static_cast<float>(j) * w;
            const auto y = static_cast<float>(i) * h;

            rectangles[block] = sf::RectangleShape(sf::Vector2f(w, h));
            if (map.isAvailable(j, i))
            {
                rectangles[block].setFillColor(sf::Color::White);
            }
            else
            {
                rectangles[block].setFillColor(sf::Color::Black);
            }
            rectangles[block].setPosition(x, y);
        }
    }
    return rectangles;
}

void draw(sf::RenderWindow* window,
          sf::RectangleShape* rectangles,
          const unsigned size)
{
    for(auto i{0u}; i < size; ++i)
    {
        window->draw(rectangles[i]);
    }
    window->display();
}

double drawT(sf::RenderWindow* window,
            sf::RectangleShape* rectangles,
            const unsigned size)
{
    auto begin = std::chrono::high_resolution_clock::now();
    draw(window, rectangles, size);
    auto end = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration<double>(end - begin);
    return time.count();
}

bool isExitPressed(sf::RenderWindow* window)
{
    sf::Event event;
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

unsigned countDelay(FrameRate framerate, double frameDrawTime)  // in ms
{
    constexpr auto MAX_DELAY{100u};
    const auto delay = static_cast<unsigned>(
                std::abs((1.0 / framerate) - frameDrawTime) * 1000.0);
    return std::min(MAX_DELAY, delay);
}

void colorAsRed(sf::RectangleShape* rectangles, const unsigned number)
{
    rectangles[number].setFillColor(sf::Color::Red);
}

void colorAsBlue(sf::RectangleShape* rectangles, const unsigned number)
{
    rectangles[number].setFillColor(sf::Color::Blue);
}

void presentPath(sf::RenderWindow* window,
                 sf::RectangleShape* rectangles,
                 const unsigned sleepTime,
                 const unsigned size,
                 const unsigned width,
                 solver::tools::Path& discovered,
                 solver::tools::Path& trace)
{
    details::draw(window, rectangles, size);

    for (const auto& step : discovered.trace())
    {
        if (isExitPressed(window))
        {
            LOG("Exit");
            return;
        }
        const auto& number = step.y * width + step.x;
        colorAsRed(rectangles, number);
        draw(window, rectangles, size);
        sleep(sleepTime);
    }

    sleep(_3_SECONDS_);

    for (const auto& step : trace.trace())
    {
        if (isExitPressed(window))
        {
            LOG("Exit");
            return;
        }
        const auto& number = step.y * width + step.x;
        colorAsBlue(rectangles, number);
        draw(window, rectangles, size);
        sleep(sleepTime);
    }

    while (not isExitPressed(window));
    LOG("Presenting finished. Press 'x' to exit");
}

}  // namespace details


Drawer::Drawer(Resolution resolution, FrameRate frames)
    : m_resolution{std::move(resolution)}
    , m_framerate{frames}
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
    auto rectangles = details::prepareMap(*source->map, m_resolution);

    const auto elements = source->map->size().width * source->map->size().height;
    const auto framDrawTime = details::drawT(window, rectangles, elements);
    const auto delayTime = details::countDelay(m_framerate, framDrawTime);
    LOG("Sleep time count as:", delayTime, "ms");

    details::presentPath(window, rectangles, delayTime, elements,
                         source->map->size().width,
                         source->discovered,
                         source->trace);

    window->close();
    delete [] rectangles;
    delete window;
}

}  // namspace graphics
}  // namespace maze

