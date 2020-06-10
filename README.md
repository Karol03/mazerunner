Prepared with
- MSVC2017 compiler (No random seed issue)
- SFML 2.5.1 version in use
<br />

Compilation flags:<br />
-DLOGGER_ON  -  enable console prints,<br />
-DLOG_SAVE_TO_FILE  -  disable console prints
 and redirect all logs to 'mazerunner.log' file
<br />

<h2>Maze part description</h2>

<h3>


Application run arguments:</h3>
argv[1] - file containing prepared maze,<br />
argv[2] - solving method,<br />
argv[3] - file for save results <optional>,<br />
argv[4] - draw the solving <optional><br />
argv[5] - speed of drawning (0 - slow, 1 - normal, 2 - fast) <optional><br />

<h3>Maze file structure:
</h3>
First line contains (separate number using spaces) in order maze width, maze height, begin point coords, end point coords
next <height> lines contains <width> values 0 or 1, where: 0 - free space, 1 - wall
<br/>

Restrictions:<br />
- begin and end points must be different<br />
- both width and height must be greater than 1<br />

<h3>Available solving methods:</h3>
1  -  random way<br />
2  -  breadth first search<br />
3  -  dreadth first search<br />
4  -  dijkstra algorithm<br />
5  -  A*<br />
6  -  Bidirectional search (double A*)<br />

All maze run statistics are saving in 'result.csv' file which is compatibile with regular *.csv format.<br />
First line contains category names. Each row contains one result separeted by semi-colon.<br />

<h2>Maze generator part description</h2>
The mazes are generated by Hunt&Kill algorithm.
<br/>

<h2>Research part description</h2>
Research part has been created to make it easiest to run many different configurations and store all the results.
You can add own testcase configuration to the 'Research.cpp' file.
