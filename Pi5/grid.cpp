#include "grid.hpp"

//intialize cell size, rows and columns, and the vector`````````
grid::grid() : cellSize(5), rows(50), columns(50), cells(rows, std::vector<Cell_State>(columns, Cell_State::Unkown)) {}

void grid::setCell(int row, int column, Cell_State state){
    if(row < 0 || row > this->rows){
        return;
    }

    if(column < 0 || column > this->columns){
        return;
    }
    cells[row][column] = state;
}

Cell_State grid::getCell(int row, int column) const {
    return cells[row][column];
}

