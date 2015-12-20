#include <iostream>
#include "Maze.h"

using namespace std;

int main() {
//    cout << "Hello, World!" << endl;
    Maze maze = Maze(5, 5, true);
    maze.display();
//    maze = Maze(5, 5, false);
//    maze.display();
//    maze = Maze(10, 10, false);
//    maze.display();

    return 0;
}
