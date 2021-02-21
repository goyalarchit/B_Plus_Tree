#pragma once
#include<iostream>


const int d = 3;
const int MAX_SIZE = d-1;

class Node{
    bool isLeaf;
    int key[MAX_SIZE],size;
    Node *ptr[d];
    Node *parent;
    void sterlizeNode();
    friend class BPTree;
    friend class BPTreePrinter;

    public:
        Node(); 
};


class BPTree{
    Node *root;
    friend class BPTreePrinter;
    public:
        BPTree();
        Node* findLeafNode(int );
        void search(int);
        void insert(int);
        void insertParent(int,Node*,Node*);
        void range(int, int);
        void count(int);
};