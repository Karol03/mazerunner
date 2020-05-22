#include "MazeApp.hpp"

#include "File/FileLoader.hpp"
#include "File/ResultsSaver.hpp"
#include "Graphics/Drawer.hpp"
#include "Solver/Solver.hpp"
#include "../Utils/Logger.hpp"
#include "../Utils/ArgsReader.hpp"

namespace maze
{

auto MazeApp::decodeOptions(int argc, char** argv)
{
    return utils::ArgsReader::parse(argc, argv);
}

int MazeApp::run(int argc, char** argv)
{
    auto config = decodeOptions(argc, argv);
    if (not config.isCorrect)
    {
        LOG("Incorrect input options");
        return -1;
    }

    if (not readFromFile(config.fileName))
    {
        LOG("File cannot be parsed to the maze");
        return -2;
    }

    if (auto results = solver::Solver(std::move(m_flatMap), config.solver).run())
    {
        file::ResultsSaver{config.resultsFileName}.save(results);
        if (config.isGraphicOn)
        {
            graphics::Drawer{_1080x1080_, _30_FPS}.display(results);
        }
    }
    return 0;
}

bool MazeApp::readFromFile(const std::string& fileName)
{
    file::FileLoader file{fileName};
    m_flatMap.reset(file.read());
    if (m_flatMap)
    {
        LOG("Area read as:\n", *m_flatMap);
    }
    else
    {
        LOG("Parsing error, no FlatMap created from file", fileName);
        return false;
    }
    return true;
}

}  // namespace maze
