#ifndef GRID_H
#define GRID_H

#include <vector>
#include <iostream>
#include <stdio.h>

enum Cell_State{
    Free, 
    Scanned, 
    Obstacle,
    Unkown
};

class grid{
    public:
        grid();
        void setCell(int row, int column, Cell_State state); 
        Cell_State getCell(int row, int column) const; 


    private:
        //50x50 map for now
        std::vector<std::vector<Cell_State>> cells;
        //each cell will be 5cm 
        int cellSize;
        int rows; 
        int columns;
};

#endif