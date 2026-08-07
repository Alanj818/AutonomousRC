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
        std::vector<Node> findPath(grid* grid, Node* start, Node* goal); //start node, where we want to go, the actual grid to compute the path finding
        Node* findLowestF(std::priority_queue<Node*, std::vector<Node*>, std::greater<int>>& open_list); // returns the node with the lowest F score from the open_list
        int computeH(Node* a, Node* b); //just a little function to compute Heuristic of a Node
        std::vector<Node> reconstruct_path(Node* curr);
    
    private:
        struct compareNode{ //type to pass for priority_queue to compare Nodes with the lowest f at the top 
            bool operator()(const Node* a, const Node* b) const{
                return a->getF() > b->getF();
            }
        };
};

#endif