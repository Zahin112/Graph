#include<iostream>

using namespace std;

class BST
{
    struct node
    {
        int data;
        node* left;
        node* right;
    };

    node* root;

    node* makeEmpty(node* t)
    {
        if(t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }

    node* insert(int x, node* t)
    {
        if(t == NULL)
        {
            t = new node;
            t->data = x;
            t->left = t->right = NULL;
        }

        else if(x < t->data)
            t->left = insert(x, t->left);
        else if(x > t->data)
            t->right = insert(x, t->right);
        else
             cout<<"Duplicate"<<endl;
        return t;
    }

    node* findMin(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    node* findMax(node* t)
    {
        if(t == NULL)
            return NULL;
        else if(t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }

    node* remove(int x, node* t)
    {
        node* temp;
        if(t == NULL)
            return NULL;
        else if(x < t->data)
            t->left = remove(x, t->left);
        else if(x > t->data)
            t->right = remove(x, t->right);
        else if(t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if(t->left == NULL)
                t = t->right;
            else if(t->right == NULL)
                t = t->left;
            delete temp;
        }

        return t;
    }

    void inorder(node* t)
    {
        if(t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

    void preorder(node* t)
    {
        if(t == NULL)
            return;
        cout << t->data << " ";
        preorder(t->left);
        preorder(t->right);

    }

    node* find(node* t, int x)
    {
        if(t == NULL)
        {
          return NULL;
        }
        else if(x < t->data)
            return find(t->left, x);
        else if(x > t->data)
            return find(t->right, x);
        else
        {
            return t;
        }

    }

public:
    BST()
    {
        root = NULL;
    }



    void insert(int x)
    {
        root = insert(x, root);
    }

    void Delete(int x)
    {
        root = remove(x, root);
    }

    void Inorder()
    {
        inorder(root);
        cout << endl;
    }

    void Preorder()
    {
        preorder(root);
        cout << endl;
    }

    void Search(int x)
    {
        if(find(root, x))
        {
           cout<<"Found"<<endl;
        }
        else
           cout<<"Not found"<<endl;
    }
};

int main()
{
    BST t;
    t.insert(20);
    t.insert(25);
    t.insert(15);
    t.insert(10);
    t.insert(30);
    t.Inorder();
    t.Delete(20);
    t.Preorder();
    t.insert(25);
    t.Search(30);
    t.Search(15);
    //t.display();
    //t.remove(30);
    //t.display();
}
