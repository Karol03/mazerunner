Mazerunner

Prepared with MSVC2017 compiler (No random seed issue)

SFML 2.5.1 version in use

<br />

Compilation flags:

-DLOGGER_ON  -  enable console prints

-DLOG_SAVE_TO_FILE  -  disable console prints
 and redirect all logs to 'mazerunner.log' file
<br />

<h1>MAZE APPLICATION DESCRIPTION</h1>

<h3>


Application run arguments:
</h3>
argv[1]  -  file containing prepared maze

argv[2]  -  solving method

argv[3]  -  file for save results <optional>  

argv[4]  -  draw the run <optional>  
<br />



<h3>Maze file structure:
</h3>
first line contains (separate number using spaces) in order maze width, maze height, begin point coords, end point coords

next <height> lines contains <width> values 0 or 1, where: 0 - free space, 1 - wall

e.g.


5 5 0 1 4 1

1 1 1 1 1

0 0 1 0 0

1 0 0 0 1

1 0 0 0 1

1 1 1 1 1

Restrictions:

- begin and end points must be different

- both width and height must be greater than 1



Available solving methods:

1  -  random way

2  -  breadth first search

3  -  dreadth first search

4  -  dijkstra algorithm

5  -  A*

6  -  Bidirectional search (double A*)



