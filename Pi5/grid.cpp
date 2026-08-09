#include "grid.hpp"

//intialize cell size, rows and columns, and the vector`````````
grid::grid() : cellSize(5), rows(50), columns(50), cells(rows, std::vector<cell>(columns)) {}

void grid::setCell(int row, int column, Cell_State state){
    if(row < 0 || row > this->rows){
        return;
    }

    if(column < 0 || column > this->columns){
        return;
    }
    cells[row][column].state = state;
}

Cell_State grid::getCell(int row, int column) const {
    return cells[row][column].state;
}

int grid::getCol(){
    return columns;
}

int grid::getRow(){
    return rows;
}

Node* grid::getNode(int x, int y){
    return &cells[x][y].node;
}
