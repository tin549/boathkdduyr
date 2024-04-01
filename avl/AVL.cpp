#include <iostream>
#include "AVL_tree.h"

int main()
{
    AVL_tree* tree = new AVL_tree();
    Node* n;
    n=new Node(10);
     tree->InsertNodeRe(n);
      n=new Node(8);
     tree->InsertNodeRe(n);
      n=new Node(4);
     tree->InsertNodeRe(n);

    n = new Node(10);
    tree->InsertNode(n);
    n = new Node(19);
    tree->InsertNode(n);
    n = new Node(20);
    tree->InsertNode(n);
    n = new Node(25);
    tree->InsertNode(n);
    n = new Node(8);
    tree->InsertNode(n);
    n=new Node(4);
    tree->InsertNode(n);
    n=new Node(1);
    tree->InsertNode(n);
    n=new Node(15);
    tree->InsertNode(n);
    tree->TravelNLR();
}