#ifndef NODE_H
#define NODE_H
#include <limits>

class Node{
    public: 
        Node();
        int getX() const; 
        void setX(int n);
        int getY() const; 
        void setY(int n);
        int getH() const; 
        void setH(int n);
        int getG() const;
        void setG(int n); 
        int getF() const;
        void setF(int g, int h);

        Node* getParent() const;
        void setParent(Node* n);
    private: 
        int x; 
        int y; 
        int g; 
        int h; 
        int f;
        Node* parent;

};

#endif