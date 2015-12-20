//
// Created by Josh on 12/18/2015.
//

#include <iostream>
#include <stack>
#include <stdio.h>
#include "Maze.h"

using namespace std;


Maze::Maze(int height, int width, bool theDebug) {
    srand(time(NULL));
    debug = theDebug;
    myRows = (height * 2) + 1;
    myCols = (width * 2) + 1;
    numCells = height * width;
    myMaze = new Cell*[myCols]; //todo might be backwards
    visited = 0;
//    lastGoodCell = std::stack<Cell>;
//    solution = std::stack<Cell>;
    solutionFound = false;

    fillMaze();

}

void Maze::display() {
    std::cout << "S = Start point \nE = End point \nX = Wall or border\n' ' = Path\n* = Soluiton path\n";
    for (int i = 0; i < myRows; i++) {
        for (int j = 0; j < myCols; j++) {
            if (myMaze[i][j].isBorder ||
                    (!myMaze[i][j].visited && !myMaze[i][j].isPath) && (!myMaze[i][j].isStart && !myMaze[i][j].isEnd)) {
                std::cout << "X ";
            } else if (myMaze[i][j].isStart) {
                std::cout << "S ";
            } else if (myMaze[i][j].isEnd) {
                std::cout << "E ";
            } else if (solutionSet.find(myMaze[i][j])) {
                std::cout << "* ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Maze::fillMaze() {
    for (int i = 0; i < myRows; i++) {
        myMaze[i] = new Cell[myCols]; //todo this might be backwards
        for (int j = 0; j < myCols; j++) {

            if (i == 0 || i == myRows - 1 || j == 0 || j == myCols - 1) { //todo investigate this suggestion
                myMaze[i][j] = Cell(i, j, true);
            } else {
                myMaze[i][j] = Cell(i, j, false);
            }
        }
    }
    myMaze[0][1].isStart = true;
    myMaze[myRows - 1][myCols - 2].isEnd = true;

    myMaze[0][1].isBorder = false;
    myMaze[myRows - 1][myCols - 2].isBorder = false;
    dig();
}

void Maze::dig() {
    myMaze[1][1].visited = true;
    Cell current = myMaze[1][1];
    solution.push(current);
    solutionSet.insert(current);

    visited = 1;

    while (visited < numCells) {
        std::vector neighbors = unvisitedNeighbors(current.row, current.col);

        if (neighbors.size() > 0) {
            if (debug) debugDisplay();

            int neighborIndex = rand() % neighbors.size();
            Cell randNeighbor = neighbors[neighborIndex];
            randNeighbor.visited = true;

            if (randNeighbor.row < current.row) {
                myMaze[current.row - 1][current.col].isPath = true;

            } else if (randNeighbor.row > current.row) {
                myMaze[current.row + 1][current.col].isPath = true;

            } else if (randNeighbor.col < current.col) {
                myMaze[current.row][current.col - 1].isPath = true;

            } else if (randNeighbor.col > current.col) {
                myMaze[current.row][current.col + 1].isPath = true;
            }

            if (current.row == myRows - 2 && current.col == myCols - 2) {
                solutionFound = true;
                solution.push(current);
                solutionSet.insert(current);
            }

            if (!solutionFound) {
                solution.push(current);
                solutionSet.insert(current);
            }

            ++visited;
        } else {
            if (lastGoodCell.size() != 0) {
                current = lastGoodCell.top();
                lastGoodCell.pop();
            }
            if (solution.size() != 0 && solutionFound) {
                solution.pop();
                solutionSet.erase(current);
            }

        }

    }
}

std::vector<Cell> Maze::unvisitedNeighbors(int row, int col) {
    std::vector result;

    if (row - 2 >= 0 && !myMaze[row - 2][col].visited && !myMaze[row - 2][col].isBorder) {
        result.push_back(myMaze[row - 2][col]);
    }
    if (row + 2 < myRows && !myMaze[row + 2][col].visited && !myMaze[row + 2][col].isBorder) {
        result.push_back(myMaze[row + 2][col]);
    }
    if (col - 2 >= 0 && !myMaze[row][col - 2].visited && !myMaze[row][col - 2].isBorder) {
        result.push_back(myMaze[row][col - 2]);
    }
    if (col + 2 < myCols && !myMaze[row][col + 2].visited && !myMaze[row][col + 2].isBorder) {
        result.push_back(myMaze[row][col + 2]);
    }


    return result;
}

void Maze::debugDisplay() {
    for (int i = 0; i < myRows; i++) {
        for (int j = 0; j < myCols; j++) {
            if (myMaze[i][j].visited) {
                std::cout << "  ";
            } else if (myMaze[i][j].isBorder || (!myMaze[i][j].visited && !myMaze[i][j].isPath)) {
                std::cout << "X ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << "\n";
    }
}

Cell::Cell(int theRow, int theCol, bool theBorder) {
    row = theRow;
    col = theCol;
    visited = false;
    isStart = false;
    isEnd = false;
    isPath = false;
    isBorder = theBorder;
}

Cell::Cell() {
    row = 0;
    col = 0;
    visited = false;
    isStart = false;
    isEnd = false;
    isPath = false;
    isBorder = false;

}
