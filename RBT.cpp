#include<iostream>
#include<bits/stdc++.h>

#define inf 9999
using namespace std;
ofstream outf;

class RBT
{
    struct node
    {
        int data;
        node* left;
        node* right;
        node *parent;
        int color; // 1 -> Red, 0 -> Black
    };

    node *root,*nill;

    /*node* makeEmpty(node* t)
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
*/


    node* searchtree(node* t, int x)
    {
        if(t == nill)
        {
          return nill;
        }
        else if(x < t->data)
            return searchtree(t->left, x);
        else if(x > t->data)
            return searchtree(t->right, x);
        else
        {
            return t;
        }

    }
    node *minimum(node *t) {
		while (t->left != nill) {
			t = t->left;
		}
		return t;
	}


    void rbTransplant(node *u, node *v){
		if (u->parent == nill)
			root = v;

		else if (u == u->parent->left)
			u->parent->left = v;

		else
			u->parent->right = v;

		v->parent = u->parent;
	}


	void leftRotate(node *x) {
		node *y = x->right;
		x->right = y->left;
		if (y->left != nill) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nill) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(node *x) {
		node *y = x->left;
		x->left = y->right;
		if (y->right != nill) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nill) {
			this->root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}


    node* insert(int k)
    {

        node *t = nill;
		t->data = k;
		t->color = 1; // new node must be red		t->left = NULL; t->right = NULL; 		t->parent = NULL;



		node *y = nill;
		node *x = this->root;

		while (x != nill) {
			y = x;
			if (t->data < x->data)
				x = x->left;
			else
				x = x->right;

		}

		// y = parent of x
		t->parent = y;
		if (y == nill) {
			root = t;
		}
		else if (t->data < y->data) {
			y->left = t;
		}
		else {
			y->right = t;
		}

		// if new node is a root node, simply return
		if (t->parent == nill){
			t->color = 0;
			return t;
		}

		// if the grandparent is null, simply return
		if (t->parent->parent == nill) {
			return t;
		}
        insert_fix(t);
        return t;
    }
    void insert_fix(node *k)
    {
        node *u;
		while (k->color != 0 && k->parent->color == 1) {
			if (k->parent == k->parent->parent->right) {
				u = k->parent->parent->left; // uncle
				if (u->color == 1) {
					// case 1
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->left) {
						// case 2

						k = k->parent;
						rightRotate(k);
					}
					// case 3
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			}
			else {
				u = k->parent->parent->right; // uncle

				if (u->color == 1) {

					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else {
					if (k == k->parent->right) {

						k = k->parent;
						leftRotate(k);
					}

					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root)
				break;

		}
		root->color = 0;

    }
    /*node* findMin(node* t)
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
*/
    node* del(int k, node* t)
    {


		node *z = searchtree(t,k);
		node *x, *y;

		/*while (t != nill){
			if (t->data == k) {
				z = t;
			}

			if (t->data <= k) {
				t = t->right;
			} else {
				t = t->left;
			}
		}*/
    //cout<<"del";
		y = z;
		int y_original_color = y->color;
		//z has 1 child
		if (z->left == nill) {
			x = z->right;
			rbTransplant(z, z->right);
			cout<<"del";
		}
		else if (z->right == nill) {
			x = z->left;
			rbTransplant(z, z->left);
		}
		//z has 2 children
		else {
			y = minimum(z->right);//predessesor
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) {
				x->parent = y;
			}
			else {
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}

			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		    cout<<"del";

		if (y_original_color == 0)
			delete_fix(x);


        return t;
    }

    void delete_fix(node *x)
    {
    node *s;
		while (x != root && x->color == 0) {
			if (x == x->parent->left) {
				s = x->parent->right;
				if (s->color == 1) {
					// case 1
					s->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					s = x->parent->right;
				}
                if(s == NULL)
                x = x->parent;

				else if (s->left->color == 0 && s->right->color == 0) {
					// case 2
					s->color = 1;
					x = x->parent;
				}

				else {
					if (s->right->color == 0) {
						// case 3
						s->left->color = 0;
						s->color = 1;
						rightRotate(s);
						s = x->parent->right;
					}

					// case 4
					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			}
			else {
				s = x->parent->left;
				if (s->color == 1) {
					// case 1
					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->left;
				}
                if(s == NULL)
                    x = x->parent;
				else if (s->right->color == 0 && s->right->color == 0) {
					// case 2
					s->color = 1;
					x = x->parent;
				}
				else {
					if (s->left->color == 0) {
						// case 3
						s->right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->parent->left;
					}

					// case 4
					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		if(x != nill)
            x->color = 0;

    }


    void inorder(node* t)
    {
        if(t == nill)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }

    void preorder(node* t)
    {
        if(t == nill)
            return;
        cout << t->data << " ";
        preorder(t->left);
        preorder(t->right);

    }


    void print(node *t)
    {
        if(t == nill) return;
        cout << t->data<< ":";
        if(t->color == 1) cout <<"r";
        else cout << "b";

        if(t->left == nill && t->right == nill) return;
        cout << "(";
        print(t->left);
        cout <<")";
        cout <<"(";
        print(t->right);
        cout << ")";
    }



public:
    RBT()
    {
        nill = new node;
        nill->color=0;
        nill->data=-inf;
        nill->left=nill->right=nill->parent=NULL;
        root = nill;
    }

    void Insert(int x)
    {
        root = insert(x);
    }

    void Delete(int x)
    {
        root = del(x, root);
    }

   /* void Inorder()
    {
        inorder(root);
        cout << endl;
    }

    void Preorder()
    {
        preorder(root);
        cout << endl;
    }
    */
    void Search(int x)
    {
        if(searchtree(root, x))
        {
           cout<<"TRUE"<<endl;
        }
        else
           cout<<"FALSE"<<endl;
    }

    void Print()
    {
        //cout<<"p";
        print(root);
    }

};

int main()
{
    RBT T;
	char c;
	int n;
    ifstream Inf;
    Inf.open("input2.txt");
    //inf>>c>n;
    outf.open("output1.txt", ios::trunc);//ios::app = for appending at last ios::ate = set the start,default begining


	while(1)
    {
        Inf>>c>>n;

        if(c=='I')
        {
            T.Insert(n);
            T.Print();
        }
        if(c=='D')
        {
            T.Delete(n);
            T.Print();
        }
        if(c='F')
        {
            T.Search(n);
            /*if(T.Search(n)!=NULL)
                outf<<"TRUE";
            else outf<<"FALSE";*/
        }

    }

    /*

        RBT t;
    t.Insert(20);
    t.Insert(25);
    t.Print();
    t.Insert(15);
    t.Insert(10);
    t.Insert(30);
    //t.Inorder();
    t.Delete(20);
    //t.Preorder();
    t.Insert(25);
    t.Search(30);
    t.Search(15);
*/
    return 0;
}
