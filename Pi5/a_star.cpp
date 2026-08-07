#include "a_star.hpp"

a_star::a_star(){}

std::vector<Node> a_star::findPath(grid* grid, Node* start, Node* goal){
    std::priority_queue<Node*, std::vector<Node*>, compareNode> open_list;
    std::vector<Node*> closed_list;

    open_list.push(start); //intialize the open_list with start 
    start->setG(0); //set cost from start to current(start in this case)
    start->setH(computeH(start, goal)); //compute the heuristic 
    start->setF(start->getH(), start->getG()); //set f to be g + h
    start->setParent(nullptr); //starts parent is null always. 
    

    while(open_list.size() > 0){ //while our open_list isn't empty, we pop out the lowests Fs
        Node* current = open_list.top();

        if(current == goal){
            return reconstruct_path(current); //here is where well backtrack and create a vector with coordinates to follow
        }

        //else we pop it from open list then move it closed list
        open_list.pop();
        closed_list.push_back(current);

        //now we check its neighbors, up(0, -1), down(0, 1), right(1, 0), left (-1, 0)
        int dx[4] = {0, 0, 1, 1};
        int dy[4] = {-1, 1, 0, 0};
        for(int i = 0; i < 4; i++){
            int nx = current->getX() + dx[i];
            int ny = current->getY() + dx[i];
        }

    }
}

int a_star::computeH(Node* a, Node* b){
    //Manhattan distance | x1 - x2| + | y1 - y2|
    int xa = a->getX(); 
    int ya = a->getY();
    int xb = b->getX();
    int yb = b->getY();

    return abs((xa - xb)) + abs((ya - yb));
}

