#include "AVL_tree.h"
#include <iostream>
#include "Node.h"
using namespace std;
AVL_tree::AVL_tree()
{
    //ctor
    this->root = nullptr;
}

AVL_tree::~AVL_tree()
{
    //dtor
}
bool AVL_tree::InsertNode(Node* n) {
    Node* p = this->root;
    Node* T = nullptr;
    if (root == nullptr)
    {
        this->root = n;

        return true;
    }
    while (p != nullptr) {
        T = p;

        if (p->Getkey() > n->Getkey())
            p = p->Getleft();
        else
            if (p->Getkey() < n->Getkey())
                p = p->Getright();
            else
                if (p->Getkey() == n->Getkey())
                    return false;
    }

    if (T->Getkey() > n->Getkey())
        T->Setleft(n);
    else T->Setright(n);
    n->Setparent(T);

    Node* x = n;
    Node* parentX = x->Getparent();
    while (x != nullptr) {
        int bal = this->CheckBal(x);
        switch (bal) {
        case 0:    break;     // Can bang
        case 1:    break;     //left heavy
        case -1:   break;   // right heavy

        case 2:if (x->Getleft()->Getleft() != nullptr)// LEFT-LEFT
        {
            this->RightRotate(x);
            x->Setparent(parentX);
            if (x->Getkey() > parentX->Getkey())
                parentX->Setright(x);
            else parentX->Setleft(x);
        }
              else // Left-Right
        {
            this->LeftRotate(x->Getleft());
            this->RightRotate(x);
            x->Setparent(parentX);
            if (x->Getkey() > parentX->Getkey())
                parentX->Setright(x);
            else parentX->Setleft(x);
        }
              break;
        case -2: if (x->Getright()->Getright() != nullptr)  // RIGHT-RIGHT
        {
            parentX = x->Getparent();
            this->LeftRotate(x);
            x->Setparent(parentX);

            if (parentX != nullptr)
                if (x->Getkey() > parentX->Getkey())
                    parentX->Setright(x);
                else parentX->Setleft(x);
        }
               else // Right-Left
        {
            this->RightRotate(x->Getright());
            this->LeftRotate(x);
            x->Setparent(parentX);

            if (parentX != nullptr)
                if (x->Getkey() > parentX->Getkey())
                    parentX->Setright(x);
                else parentX->Setleft(x);
        }
               break;
        }
        if (x->Getparent() == nullptr)
            this->root = x;
        x = x->Getparent();

    }

    return true;

}
Node* AVL_tree::InsertNode(Node* r, Node* p) {
    if (r == nullptr) {
        r = p;
        return r;
    }
    if (r->Getkey() == p->Getkey())
        return nullptr;
    else if (r->Getkey() > p->Getkey()) {
        r->Setleft(InsertNode(r->Getleft(), p));
        return r->Getleft();
    }
    else {
        r->Setright(InsertNode(r->Getright(), p));
        return r->Getright();
    }

    // Update height
    r->Setheight(1 + max(r->Getleft()->Getheight(), r->Getright()->Getheight()));

    // Update balance factor
    int valBalance = r->Getleft()->Getheight() - r->Getright()->Getheight();
    if (valBalance > 1 && r->Getleft()->Getkey() > p->Getkey()) {
        this->RightRotate(r);
    }

    return r;
}


void AVL_tree::InsertNodeRe(Node* p) {
    this->root = InsertNode(this->root, p);
}
void AVL_tree::NLR(Node* r) {
    if (r != nullptr) {
        cout << r->Getkey() << "\n";
        NLR(r->Getleft());
        NLR(r->Getright());
    }
}
void AVL_tree::LNR(Node* r) {
    if (r != nullptr) {
        LNR(r->Getleft());
        cout << r->Getkey() << " ";
        LNR(r->Getright());
    }
}
void AVL_tree::LRN(Node* r) {
    if (r != nullptr) {
        LRN(r->Getleft());
        LRN(r->Getright());
        cout << r->Getkey() << " ";
    }
}
void AVL_tree::TravelNLR() {
    NLR(this->root);
}
void AVL_tree::TravelLNR() {
    LNR(this->root);
}
void AVL_tree::TravelLRN() {
    LRN(this->root);
}


Node* AVL_tree::search_x(int k) {

    Node* P = root;
    while (P != nullptr) {
        if (P->Getkey() == k)
            return P;
        else if (P->Getkey() > k)
            P = P->Getleft();
        else
            P = P->Getright();
    }
    return P;
}

void AVL_tree::deleteNode(Node* n) {

    {

        if (root == nullptr)
        {
            cout << "Cay rong." << endl;
            return;
        }


        Node* p = this->root;
        Node* parent = nullptr;
        bool isLeftChild = false;

        while (p != nullptr && p->Getkey() != n->Getkey())
        {
            parent = p;

            if (n->Getkey() < p->Getkey())
            {
                p = p->Getleft();
                isLeftChild = true;
            }
            else
            {
                p = p->Getright();
                isLeftChild = false;
            }
        }


        if (p == nullptr)
        {
            cout << "Khong tim thay nut can xoa." << endl;
            return;
        }


        if (p->Getleft() == nullptr && p->Getright() == nullptr)
        {
            if (p == root)
            {
                root = nullptr;
            }
            else
            {
                if (isLeftChild)
                    parent->Setleft(nullptr);
                else
                    parent->Setright(nullptr);
            }

            delete p;
        }
        else if (p->Getright() == nullptr)
        {
            if (p == root)
            {
                root = p->Getleft();
            }
            else
            {
                if (isLeftChild)
                    parent->Setleft(p->Getleft());
                else
                    parent->Setright(p->Getleft());
            }

            delete p;
        }
        else if (p->Getleft() == nullptr)
        {
            if (p == root)
            {
                root = p->Getright();
            }
            else
            {
                if (isLeftChild)
                    parent->Setleft(p->Getright());
                else
                    parent->Setright(p->Getright());
            }

            delete p;
        }
        else
        {
            Node* s = p->Getright();
            Node* sParent = nullptr;

            while (s->Getleft() != nullptr)
            {
                sParent = s;
                s = s->Getleft();
            }

            if (sParent != nullptr)
            {
                sParent->Setleft(s->Getright());
            }
            else
            {
                p->Setright(s->Getright());
            }

            p->Setkey(s->Getkey());
            delete s;
        }
    }
}
void AVL_tree::LeftRotate(Node*& P) {
    Node* Q;
    Node* T;
    Q = P->Getright();
    T = Q->Getleft();
    P->Setright(Q->Getleft());
    Q->Setleft(P);
    P->Setparent(Q);
    if (T != nullptr)
        T->Setparent(P);
    P = Q;
}
void AVL_tree::RightRotate(Node*& P) {
    Node* Q;
    Node* T;
    Q = P->Getleft();
    T = Q->Getright();
    P->Setleft(Q->Getright());
    Q->Setright(P);
    P->Setparent(Q);
    T->Setparent(P);
    P = Q;
}
int AVL_tree::CheckBal(Node* p) {
    int bal = this->GetHeight(p->Getleft()) - this->GetHeight(p->Getright());
    return bal;
}
int AVL_tree::GetHeight(Node* p) {
    if (p == nullptr) return 0;
    else
        return 1 + max(GetHeight(p->Getleft()), GetHeight(p->Getright()));
}
