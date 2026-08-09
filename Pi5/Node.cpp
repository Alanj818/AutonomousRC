#include "Node.hpp"

Node::Node(){}

//GETTER UND SETTER FUR X
int Node::getX() const {
        return x;
}

void Node::setX(int x){
        this->x = x;
}

//GETTER UND SETTER FUR Y
int Node::getY() const {
        return y;
}

void Node::setY(int y){
        this->y = y;
}

//GETTER UND SETTER FUR H
int Node::getH() const {
        return h;
}

void Node::setH(int h){
        this->h = h;
}

//GETTER UND SETTER FUR G
int Node::getG() const{
        return g;
}

void Node::setG(int g){
        this->g = g;
}

//GETTER UND SETTER FUR F
int Node::getF() const{
        return g + h;
}

void Node::setF(int g, int h){
        f = g + h;
}

//GETTER UND SETTER FUR ÜBERNODE
Node* Node::getParent() const{
        return parent;
}

void Node::setParent(Node* n){
        this->parent = n;
}

void Node::setIsClosed(bool n){
        isClosed = n;
}

bool Node::getIsClosed(){
        return isClosed;
}

void Node::setIsOpen(bool n){
        isOpen = n;
}
