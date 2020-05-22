TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
DEFINES += LOGGER_ON

INCLUDEPATH += C:\SFML-2.5.1\include
DEPENDPATH += C:\SFML-2.5.1\include

LIBS += -LC:\SFML-2.5.1\lib\

CONFIG(debug, debug|relase): LIBS += -lsfml-system-d -lsfml-main-d -lsfml-window-d -lsfml-graphics-d
CONFIG(debug, debug|relase): LIBS += -lsfml-system -lsfml-main -lsfml-window -lsfml-graphics

SOURCES += \
        Maze/Graphics/Drawer.cpp \
        Maze/File/FileLoader.cpp \
        Maze/File/ResultsSaver.cpp \
        Maze/LineReader.cpp \
        Maze/FlatMap.cpp \
        Maze/MazeApp.cpp \
        Maze/Solver/Algorithms/AStar.cpp \
        Maze/Solver/Algorithms/BFS.cpp \
        Maze/Solver/Algorithms/DFS.cpp \
        Maze/Solver/Algorithms/Dijkstra.cpp \
        Maze/Solver/Algorithms/DoubleAStar.cpp \
        Maze/Solver/Method.cpp \
        Maze/Solver/Algorithms/RandomMove.cpp \
        Maze/Solver/Result.cpp \
        Maze/Solver/SolveStrategy.cpp \
        Maze/Solver/Solver.cpp \
        Maze/Solver/Tools/DistanceMap.cpp \
        Maze/Solver/Tools/Path.cpp \
        Maze/Solver/Tools/Random.cpp \
        Maze/Solver/Tools/VisitedMap.cpp \
        Utils/ArgsReader.cpp \
        main.cpp

HEADERS += \
    Maze/Graphics/Drawer.hpp \
    Maze/File/ResultsSaver.hpp \
    Maze/Graphics/Settings.hpp \
    Maze/Solver/Algorithms/AStar.hpp \
    Maze/Solver/Algorithms/BFS.hpp \
    Maze/Solver/Algorithms/Dijkstra.hpp \
    Maze/Solver/Algorithms/DoubleAStar.hpp \
    Maze/Solver/Method.hpp \
    Maze/Solver/Algorithms/RandomMove.hpp \
    Maze/Solver/Result.hpp \
    Maze/Solver/Tools/DistanceMap.hpp \
    Maze/Solver/Tools/Path.hpp \
    Maze/File/FileLoader.hpp \
    Maze/LineReader.hpp \
    Maze/Solver/Algorithms/DFS.hpp \
    Maze/Solver/SolveStrategy.hpp \
    Maze/Solver/Tools/PriorityPoint.hpp \
    Maze/Solver/Tools/Random.hpp \
    Maze/Solver/Tools/VisitedMap.hpp \
    Utils/ArgsReader.hpp \
    Utils/Config.hpp \
    Utils/Logger.hpp \
    Maze/FlatMap.hpp \
    Maze/MazeApp.hpp \
    Maze/Solver/Solver.hpp \
    Utils/Operators.hpp
