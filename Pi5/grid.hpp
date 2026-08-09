#ifndef GRID_H
#define GRID_H

#include "Node.hpp"
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
        int getCol();
        int getRow();
        Node* getNode(int x, int y);


    private:
        //50x50 map for now
        struct cell{
            Cell_State state;
            Node node;
        };

        std::vector<std::vector<cell>> cells;
        //each cell will be 5cm 
        int cellSize;
        int rows; 
        int columns;
};

#endif