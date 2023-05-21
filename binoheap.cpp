#include <iostream>
#include <cstdlib>
#include<bits/stdc++.h>

using namespace std;


struct node
{
    int n;
    int degree;
    node* parent;
    node* child;
    node* sibling;
};


class Bheap
{
        node *H;
        node *Hr;
        int count;
public:
        Bheap();
        node* Initializeheap();
        void Link(node* y, node* z);
        node* Create_node(int k);
        void Union(node* H2);
        node* Insert(node* x);
        node* Merge(node* H1, node* H2);
        node* Find_Min();
        node* Extract_Min();
        void Revert_list(node* y);
        void Print();

};

Bheap::Bheap()
{
            H = Initializeheap();
            Hr = Initializeheap();
}
node* Bheap::Initializeheap()
{
    node* np;
    np = NULL;
    return np;
}


void Bheap::Link(node* y, node* z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}

node* Bheap::Create_node(int k)
{
    node* p = new node;
    p->n = k;
    return p;
}


node* Bheap::Insert(node* x)
{
    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    Union(x);
    return H;
}


void Bheap::Union(node* H2)
{
    H= Merge(H , H2);
    if (H == NULL)
        return ;
    node* prev_x;
    node* next_x;
    node* x;
    prev_x = NULL;
    x = H;
    next_x = x->sibling;
    while (next_x != NULL)
    {
        if ((x->degree != next_x->degree) || ((next_x->sibling != NULL)
            && (next_x->sibling)->degree == x->degree))
        {
            prev_x = x;
            x = next_x;
        }
        else
	    {
            if (x->n <= next_x->n)
            {
                x->sibling = next_x->sibling;
                Link(next_x, x);
            }
            else
            {
                if (prev_x == NULL)
                    H = next_x;
                else
                    prev_x->sibling = next_x;
                Link(x, next_x);
                x = next_x;
            }
	    }
        next_x = x->sibling;
    }
    return;
}


node* Bheap::Merge(node* H1,node* H2)
{
    node* y,*z,*a,*b;//a b temporary
    y = H1;
    z = H2;
    if (y != NULL)
    {
        if (z != NULL)
        {
            if (y->degree <= z->degree)
                H = y;
            else H = z; //if (y->degree > z->degree)

        }
        else
            H = y;
    }
    else
        H = z;



    while (y != NULL && z != NULL)
    {
        if (y->degree < z->degree)
        {
            y = y->sibling;
        }
        else if (y->degree == z->degree)
        {
            a = y->sibling;
            y->sibling = z;
            y = a;
        }
        else
        {
            b = z->sibling;
            z->sibling = y;
            z = b;
        }
    }
    return H;
}

node* Bheap::Find_Min(){
    if(H == NULL){
        cout<<"Nothing to Find"<<endl;
        return H;
    }

    int min = H->n;
    node* p = H;

    while (p->sibling != NULL)
    {
        if ((p->sibling)->n < min)
        {
            min = (p->sibling)->n;

        }
        p = p->sibling;
    }

    return p;
}


node* Bheap::Extract_Min()
{
    Hr = NULL;
    node* t = NULL;

    if (H == NULL)
    {
        cout<<"Nothing to Extract"<<endl;
        return H;
    }

    node* x = H;
    int min = x->n;
    node* p = x;
    while (p->sibling != NULL)//Find min
    {
        if ((p->sibling)->n < min)
        {
            min = (p->sibling)->n;
            t = p;
            x = p->sibling;
        }
        p = p->sibling;
    }
    if (t == NULL && x->sibling == NULL)
        H = NULL;
    else if (t == NULL)
        H = x->sibling;
    else if (t->sibling == NULL)
        t = NULL;
    else
        t->sibling = x->sibling;
    if (x->child != NULL)
    {
        Revert_list(x->child);
        (x->child)->sibling = NULL;
    }
    Union(Hr);
    return x;
}

void Bheap::Revert_list(node* y)
{
    if (y->sibling != NULL)
    {
        Revert_list(y->sibling);
        (y->sibling)->sibling = y;
    }
    else
    {
        Hr = y;
    }
}



void Bheap::Print()
{

    cout<<"Printing Binomial Heap..."<<endl;
    node* root = H;
    node* Node = NULL;
    while(root != NULL){
        cout<<"Binomial Tree, B"<<root->degree<<endl;
        queue<node*> q1,q2;
        int level = 0;
        Node = root;
        q1.push(Node);
        while(!q1.empty() || !q2.empty()){
            if(!q1.empty()){
                cout<<"Level "<<level<<" : ";
                level++;
                while(!q1.empty()){
                    Node = q1.front(); q1.pop();
                    cout << Node->n <<" ";
                    Node = Node->child;
                    while(Node != NULL){
                        q2.push(Node);
                        Node = Node->sibling;
                    }
                }
                cout<<"\n";
            }
            if(!q2.empty()){
                cout<<"Level "<<level<<" : ";
                level++;
                while(!q2.empty()){
                    Node = q2.front(); q2.pop();
                    cout << Node->n <<" ";
                    Node = Node->child;
                    while(Node != NULL){
                        q1.push(Node);
                        Node = Node->sibling;
                    }
                }
                cout<<"\n";
            }
        }
        root = root->sibling;
    }
    Node = NULL;
    root = NULL;
    delete root;
    delete Node;

}

int main()
{

    Bheap H;
    node* p;
    node* H1;
    string line;
    freopen("output.txt","w",stdout);
    ifstream file("input.txt");
    char c;
    int n;
    if(file.is_open())
    {
        while(getline(file,line))
        {
            istringstream is(line);
            is >> c;
            if(c == 'I'){
                is >> n;
                H.Insert(H.Create_node(n));
            }
            else if(c == 'F'){
                cout<<"Find-min returned "<<H.Find_Min()->n<<endl;
            }
            else if(c == 'E'){
                cout <<"Extract-min returned "<<H.Extract_Min()->n<<endl;
            }
            else if(c == 'P'){
                H.Print();
            }
            else if(c == 'U'){
                while(is >> n){
                    H.Insert(H.Create_node(n));
                }
                H.Union(H1);
            }
        }
        file.close();
    }

    else cout << "Could not open file!" << endl;


    return 0;
}



