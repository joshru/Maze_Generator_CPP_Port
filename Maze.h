//
// Created by Josh on 12/18/2015.
//

#ifndef MAZE_GENERATOR_PORT_MAZE_H
#define MAZE_GENERATOR_PORT_MAZE_H


#include <stdlib.h>
#include <stack>
#include <vector>
//#include <bits/stl_stack.h>
//#include <bits/stl_vector.h>
//#include <bits/stl_set.h>

class Cell {
public:
    int row;
    int col;
    bool visited;
    bool isStart;
    bool isEnd;
    bool isBorder;
    bool isPath;

    Cell(int theRow, int theCol, bool theBorder);
    Cell();
    void print();
};

class Maze {
public:
//    const int r = rand();
//    Cell **myMaze;
    int visited;
    Maze(int, int, bool);
    void display();


    std::stack<Cell> lastGoodCell;
    std::stack<Cell> solution;
    std::stack<Cell> solutionSet;
    bool solutionFound;
    bool debug;
    int myRows;
    int myCols;
    int numCells;
    void init();
    void fillMaze();
    void dig();
    std::vector<Cell> unvisitedNeighbors(int, int);
    void debugDisplay();

};



#endif //MAZE_GENERATOR_PORT_MAZE_H

