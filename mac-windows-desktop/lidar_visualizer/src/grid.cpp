#include "grid.hpp"

grid::grid(float cell_size, sf::Vector2u window_size) : cell_size(cell_size), window_size(window_size), cell_state( static_cast<int>(window_size.y / cell_size), std::vector<cellData>(static_cast<int>(window_size.x / cell_size), cellData::Unknown)) {}

void grid::drawGrid(sf::RenderWindow& window){

    sf::RectangleShape cell;
    cell.setSize({cell_size - .5f, cell_size - .5f});

    for(int x = 0; x < cell_state.size(); x++){
        for(int y = 0; y < cell_state[0].size(); y++){
            if(cell_state[x][y] == cellData::Obstacle){
                cell.setFillColor(sf::Color::Black);
                cell.setPosition({static_cast<float>(y * cell_size), static_cast<float>(x * cell_size)});
                window.draw(cell);
            } else if(cell_state[x][y] == cellData::Free){
                cell.setFillColor(sf::Color::Cyan);
                cell.setPosition({static_cast<float>(y * cell_size), static_cast<float>(x * cell_size)});
                window.draw(cell);
            } else if(cell_state[x][y] == cellData::Taken){
                cell.setFillColor(sf::Color::Magenta);
                cell.setPosition({static_cast<float>(y * cell_size), static_cast<float>(x * cell_size)});
                window.draw(cell);
            } else if (cell_state[x][y] == cellData::Unknown){
                cell.setFillColor(sf::Color(194, 236, 230));
                cell.setPosition({static_cast<float>(y * cell_size), static_cast<float>(x * cell_size)});
                window.draw(cell);
            }
            
        }
    }
}

void grid::setCell(int x, int y, cellData state){
    if(x < 0 || x >= static_cast<int>(cell_state.size())){
        return;
    }

    if(y < 0 || y >= static_cast<int>(cell_state[0].size())){
        return;
    }
    cell_state[x][y] = state;
}

sf::Vector2i grid::lidarToGrid(float lidar_distance, int servo_angle, sf::Vector2f robot_position){
    float angle = servo_angle * (M_PI / 180.f);
    float height = -lidar_distance * sin(angle);
    float width = lidar_distance * cos(angle);
    int col = static_cast<int>((robot_position.x + width) / cell_size);
    int row = static_cast<int>((robot_position.y + height) / cell_size);
    float step = 5.f;

    for(float d = 0.f; d < lidar_distance; d += step){
        float dx = cos(angle) * d;
        float dy = -sin(angle) * d;
        int x = static_cast<int>((robot_position.x + dx) / cell_size);
        int y = static_cast<int>((robot_position.y + dy) / cell_size);

        setCell(y, x, cellData::Free);
    }
    return {col, row};
}

void grid::setCell(const std::vector<int>& x, const std::vector<int>& y, cellData state){
    if(x.size() != y.size()){
        return;
    }

    for(size_t i = 0; i < x.size(); i++){
        setCell(x[i], y[i], state);
    }
}

void grid::handleInput(){
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)){
        resetGrid();
    }
}

void grid::resetGrid(){
    for(auto& col : cell_state){
        for(auto& row : col){
            row = cellData::Unknown;
        }
    }
}

