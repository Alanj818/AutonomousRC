#ifndef A_STAR
#define A_STAR

#include <iostream>
#include <stdio.h>
#include <vector>
#include "Node.hpp"
#include "grid.hpp"

class a_star{
    public:
        a_star();
        std::vector<Node*> findPath(grid* grid, Node* start, Node* goal); //start node, where we want to go, the actual grid to compute the path finding
        int computeH(Node* a, Node* b); //just a little function to compute Heuristic of a Node
        std::vector<Node*> reconstruct_path(Node* curr);
        bool isClosed(int x, int y, const std::vector<Node*>& open_list);
    
    private:
        struct compareNode{ //type to pass for priority_queue to compare Nodes with the lowest f at the top 
            bool operator()(const Node* a, const Node* b) const{
                return a->getF() > b->getF();
            }
        };
};

#endif