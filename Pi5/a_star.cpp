#include "a_star.hpp"

a_star::a_star(){}

std::vector<Node*> a_star::findPath(grid* grid, Node* start, Node* goal){
    std::priority_queue<Node*, std::vector<Node*>, compareNode> open_list;
    std::vector<Node*> closed_list;

    start->setIsOpen(true);
    start->setG(0); //set cost from start to current(start in this case)
    start->setH(computeH(start, goal)); //compute the heuristic 
    start->setF(start->getH(), start->getG()); //set f to be g + h
    start->setParent(nullptr); //starts parent is null always. 
    open_list.push(start); //intialize the open_list with start 

    while(open_list.size() > 0){ //while our open_list isn't empty, we pop out the lowests Fs
        Node* current = open_list.top();

        if(current->getX() == goal->getX() && current->getY() == goal->getY()){
            return reconstruct_path(current); //here is where well backtrack and create a vector with coordinates to follow
        }

        //else we pop it from open list then move it closed list
        open_list.pop();
        closed_list.push_back(current);
        current->setIsOpen(false);
        current->setIsClosed(true);

        //now we check its neighbors, up(0, -1), down(0, 1), right(1, 0), left (-1, 0)
        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {-1, 1, 0, 0};
        for(int i = 0; i < 4; i++){
            int nx = current->getX() + dx[i];
            int ny = current->getY() + dy[i];
            


            //we will check if its in bounds, valid etc just not now im tired

            //check bounds, doing it the lazy way for now
            if(nx < 0 || ny < 0 || nx >= grid->getCol() || ny >= grid->getRow()){
                continue;
            }

            //check if its an obstacle, we want it to try the "unknown route" so leave that alone
            if(grid->getCell(nx, ny) == Cell_State::Obstacle){
                continue;
            }

            //Check if it was already visited, if it is not open, meaning its closed

            //lets say all is good and this is the best path next
            
            Node* neighbor = grid->getNode(nx, ny); //allocate a new Node object 
            
            //check if its in closed_list, if it is then skip it, it was already evaluated
            if(neighbor->getIsClosed()){
                continue;
            }

            int tent_g = current->getG() + 1; //calculate tent_g (its only a grid not real world values yet so + 1 just means move to next box(0,0) -> (0, 1), one move)
            
            if(!neighbor->getIsOpen()){
                neighbor->setG(tent_g);//set g 
                neighbor->setH(computeH(neighbor, goal));//set h
                neighbor->setF(neighbor->getG(), neighbor->getH());//set f
                neighbor->setParent(current);//set current as its parent  

                open_list.push(neighbor);
                neighbor->setIsOpen(true);
                neighbor->setIsClosed(false);
            } else if(tent_g < neighbor->getG()){
                neighbor->setG(tent_g);//set g 
                neighbor->setH(computeH(neighbor, goal));//set h
                neighbor->setF(neighbor->getG(), neighbor->getH());//set f
                neighbor->setParent(current);//set current as its parent 
                open_list.push(neighbor);
            }
 
        }

    }

    return {};
}

int a_star::computeH(Node* a, Node* b){
    //Manhattan distance | x1 - x2| + | y1 - y2|
    int xa = a->getX(); 
    int ya = a->getY();
    int xb = b->getX();
    int yb = b->getY();

    return abs((xa - xb)) + abs((ya - yb));
}

std::vector<Node*> a_star::reconstruct_path(Node* curr){
    std::vector<Node*> recon;
    while(curr->getParent() != nullptr){
        recon.push_back(curr);
        curr = curr->getParent(); 
    }
    return recon;
}

bool a_star::isClosed(int x, int y, const std::vector<Node*>& closed_list){
    for(Node* node : closed_list){
        if(node->getX() == x && node->getY() == y){
            return true;
        }
    }
    return false;
}

