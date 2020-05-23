#include "ArgsReader.hpp"

#include "Logger.hpp"
#include "../Maze/Solver/Method.hpp"
#include "Operators.hpp"

namespace utils
{

int ArgsReader::readSolver(char** argv)
{
    const auto solver = atoi(argv[2]);
    if (solver > 0)
    {
        return solver;
    }
    else
    {
        LOG("Solver type argument is incorrect. Try again");
    }
    return 0;
}

bool ArgsReader::isGraphicOn(char** argv)
{
    const auto graphicFlag = std::atoi(argv[4]);
    return graphicFlag == 1;
}

Config ArgsReader::parse(int argc, char** argv)
{
    Config config;
    if (argc == 2 and strcmp(argv[1], "help") == 0)
    {
        LOG("Run the program using the console command\n",
            "maze [file name] [solver type] <result file name> <is drawning on flag>\n",
            "\nAvailbale solver types:\n",
            "1\tRandom steps\n2\tBFS\n3\tDFS\n4\tDijkstra\n5\tA*\n6\tD*\n");
    }
    else if (argc > 2)
    {
        for (int i = 1; i < argc; ++i)
        {
            switch (i)
            {
            case 1:
                config.fileName = argv[1];
                break;
            case 2:
                config.solver = maze::solver::toType(readSolver(argv));
                if (config.solver == maze::solver::Method::ENot_set)
                    return Config{};
                break;
            case 3:
                config.resultsFileName = argv[3];
                break;
            case 4:
                config.isGraphicOn = isGraphicOn(argv);
                break;
            }
        }
        config.isCorrect = true;
    }
    else
    {
        LOG("Wrong number of arguments ", argc, ". Use \"help\" to display instruction");
    }
    return config;
}

}  // namespace utils

