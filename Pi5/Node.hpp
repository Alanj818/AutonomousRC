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
        void setIsOpen(bool n);
        void setIsClosed(bool n);
        bool getIsOpen();
        bool getIsClosed();

        Node* getParent() const;
        void setParent(Node* n);
    private: 
        int x; 
        int y; 
        int g = std::numeric_limits<int>::max(); 
        int h = 0;
        int f = std::numeric_limits<int>::max();
        bool isOpen = false;
        bool isClosed = false;
        Node* parent;

};

#endif