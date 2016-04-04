//
// Created by Josh on 12/18/2015.
//

#include <iostream>
#include <stack>
#include <algorithm>
#include <deque>
#include <stdio.h>
#include "Maze.h"

Cell** myMaze;

//using namespace std;
Maze::Maze(int height, int width, bool debugFlag) {
    srand(time(NULL));

    solutionFound = false;
    visited = 0;
    debug = debugFlag;
    myRows = height;
    myCols = width;
    numCells = height * width;

    myMaze = new Cell*[width];


    init();
    fillMaze();
}

void Maze::init() {
    for (int i = 0; i < myRows; i++) {
        myMaze[i] = new Cell[myCols];
    }
}

void Maze::fillMaze() {
    for (int i = 0; i < myRows; i++) {
        for (int j = 0; j < myCols; j++) {
            if (i == 0 || i == myRows - 1 || j == 0 || j == myCols - 1) {
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

void Maze::debugDisplay() {
    using namespace std;
    for (int i = 0; i < myRows; i++) {
        for (int j = 0; j < myCols; j++) {
            if (myMaze[i][j].visited) {

                cout << "  ";
            } else if (myMaze[i][j].isBorder || (!myMaze[i][j].visited && !myMaze[i][j].isPath)) {
                cout << "X ";
            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void Maze::display() {
    using namespace std;
    for (int i = 0; i < myRows; i++) {
        for (int j = 0; j < myCols; j++) {
            if (myMaze[i][j].isBorder
                || (!myMaze[i][j].visited && !myMaze[i][j].isPath) && (!myMaze[i][j].isStart && !myMaze[i][j].isEnd)) {

                cout << "X ";
            } else if (myMaze[i][j].isStart) {
                cout << "S ";

            } else if (myMaze[i][j].isEnd) {
                cout << "E ";

//            } else if (std::find(solution.begin(), solution.end(), myMaze[i][j]) != solution.end()) {
//                cout << "* ";

            } else {
                cout << "  ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void Maze::dig() {
    myMaze[1][1].visited = true;
    Cell current = myMaze[1][1];
    solution.push_back(current);

    while (visited < numCells) {
        std::vector<Cell> neighbors = unvisitedNeighbors(current.row, current.col);

        if (neighbors.size() > 0) {
            if (debug) debugDisplay();
            auto neighborIndex = rand() % (int) neighbors.size();
            Cell randNeighbor = neighbors.at(neighborIndex);
            randNeighbor.visited = true;

            //figure out which way to tunnel
            if (randNeighbor.row < current.row) {
                myMaze[current.row - 1][current.col].isPath = true;

            } else if (randNeighbor.row > current.row) {
                myMaze[current.row + 1][current.col].isPath = true;

            } else if (randNeighbor.col < current.col) {
                myMaze[current.row][current.col - 1].isPath = true;

            } else if (randNeighbor.col > current.col){
                myMaze[current.row][current.col + 1].isPath = true;
            }

            lastGoodCell.push(current);
            current = randNeighbor;

            //check if endpoint has been reached
            if (current.row == myRows - 2 && current.col == myCols - 2) {
                solutionFound = true;
                solution.push_back(current);
            }

            if (!solutionFound) {
                solution.push_back(current);
            }
            ++visited;

        } else {
            if (!lastGoodCell.empty()) {
                current = lastGoodCell.top();
                lastGoodCell.pop();
            }
            if (!solution.empty() && !solutionFound) {
                solution.pop_back();
            }

        }
    }
}

std::vector<Cell> Maze::unvisitedNeighbors(int row, int col) {
    std::vector<Cell> result;

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

void Cell::print() {
    using namespace std;
    cout << "row: " << row << " col: " << col << endl;
}


