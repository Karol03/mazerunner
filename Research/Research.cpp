#include "Research.hpp"

#include "../MazeGenerator/MazeGenerator.hpp"
#include "../Utils/Operators.hpp"
#include "../Utils/Logger.hpp"
#include "ResearchMacros.hpp"

namespace research
{

using namespace tests;

Tester Research::preapre()
{
    auto tester = Tester::initialize();
    LOG("Preparing testcases");

    TESTCASE("Dummy test 1",
             TestConfig{RESULT_FILE_NAME, REPEAT_TIMES(1), DRAWNING_ON, DrawningSpeed::ESlow},
             MazeConfig{GENERATE_MAZE, SIZE(10, 10), BEGIN_AT(0, 2), END_AT(9, 2)});

    TESTCASE("Dummy test 2",
             TestConfig{RESULT_FILE_NAME, REPEAT_TIMES(1), DRAWNING_ON, DrawningSpeed::ENormal},
             MazeConfig{GENERATE_MAZE, SIZE(20, 20), BEGIN_AT(6, 0), END_AT(19, 18)});

    TESTCASE("Dummy test 3",
             TestConfig{RESULT_FILE_NAME, REPEAT_TIMES(1), DRAWNING_ON},
             MazeConfig{GENERATE_MAZE, SIZE(20, 20), BEGIN_AT(6, 0), END_AT(19, 18)});

    TESTCASE("Dummy test 4",
             TestConfig{RESULT_FILE_NAME, REPEAT_TIMES(1), DRAWNING_ON, DrawningSpeed::EFast},
             MazeConfig{GENERATE_MAZE, SIZE(100, 100), BEGIN_AT(6, 0), END_AT(99, 98)});

    LOG("Preapred", tester.testcases(), "testcases");
    return tester;
}

int Research::run(int, char**)
{
    return preapre().run();
}

}  // namespace research
