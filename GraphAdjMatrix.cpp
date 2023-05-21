#include<stdio.h>
#include <algorithm>
#include <chrono>
#include<iostream>
#include<list>
#include<stdlib.h>
//#include<cstdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

using namespace std;
using namespace std::chrono;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    int getfront();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}

int Queue::getfront()
{
    return front;
}

void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;  // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int *visited;
	int ** matrix ;
	int *color;
	int *parent;
	int *dist; //adjacency matrix to store the graph
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u,bool out);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void BFS(int source);
	void DFS(int source);
	int getOutDegree(int u);
    int getInDegree(int u);
    void calculate(int v,int n, bool dir);
	 //will run bfs in the graph
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	visited=0;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    visited = new int[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        visited[i]=0;
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;

}

void Graph::removeEdge(int u, int v)
{
    matrix[u][v]=0;
    if(!directed) matrix[v][u]==0;
    //write this function
}

bool Graph::isEdge(int u, int v)
{
    if(matrix[u][v]||(!directed && matrix[v][u])) return true;


    return false;
    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph::getDegree(int u,bool out=true)
{
    int c=0,i;
    if(!directed)
    {
      for(i=0;i<nVertices;i++)
      {
          if(matrix[u][i]==1) c++;
      }
    }

    else{
        if(out)
        {
            for(i=0;i<nVertices;i++)
            {
                 if(matrix[u][i]==1) c++;
            }
        }
        else{
            for(i=0;i<nVertices;i++)
            {
                 if(matrix[i][u]==1) c++;
            }
        }
    }

    return c;
    //returns the degree of vertex u
}

void Graph::printAdjVertices(int u)
{
    for(int i=0; i<nVertices;i++)
    {
        if(matrix[u][i]==1)
            cout<<i<<endl;
    }
    //prints all adjacent vertices of a vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    for(int i=0; i<nVertices;i++)
    {
        if(matrix[u][i]==1&&matrix[v][i]==1)
           return true;
    }
    return false;
    //returns true if vertices u and v have common adjacent vertices

}

void Graph::BFS(int source)
{
    Queue q;
    for(int i=0; i<nVertices;i++)
    {
        if(i==source){
        color[i] = GREY;
        dist[i] = INFINITY;
        }
        else{
             color[i] = WHITE;
             dist[i] = 0;
        }

        parent[i] = NULL_VALUE;
    }


    q.enqueue(source);

    while(!q.empty())
    {
       int s=q.dequeue();
       cout<<s<<" ";

    for(int i=0; i<nVertices;i++)
    {
        if(matrix[s][i]==1)
        {
            if(color[i]==WHITE)
            {
             color[i] = GREY;
             parent[i] = s;
             dist[i] = dist[s] + 1;
             q.enqueue(i);
            }
        }
    }

    color[s]=BLACK;
    }

    //write this function

}

void Graph::DFS(int i){

    cout<<i<<" ";
    //int j;
    visited[i]=1;
    //cout<<i+1;
    for(int j=0;j<nVertices;j++)
    {
        if(matrix[i][j]==1 && visited[j]==0)
            DFS(j);
    }
}



int Graph::getDist(int u, int v)
{
    BFS(u);
    return dist[v];
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    return INFINITY ;
}


int Graph::getOutDegree(int i)
{
    if(directed)
    {
        int n=0;
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j])
                n++;

        }
        return n;

    }
}

int Graph::getInDegree(int s)
{
    if(directed)
    {
        int n=0;
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[j][s])
                n++;
        }

        return n;

    }
}

void Graph::calculate(int v,int n, bool dir)
{
    srand(5);
    Graph g1=new Graph(dir);
    //cout<<"g";
    float t=0;
    g1.setnVertices(v);
    //cout<<"v";
    for(int i=0;i<n*v;i++)
    {
        g1.addEdge(rand()%v,rand()%v);
    }
    //cout<<"e";
    for(int i=0; i<10;i++)
    {
        auto start = chrono::high_resolution_clock::now();
        //cout<<"gs";
        g1.BFS(rand()%v);
        //cout<<"ge";
        auto stop = chrono::high_resolution_clock::now();
        //cout<<"gt";
        t+=duration_cast<chrono::nanoseconds>(stop - start).count();

        //cout<<duration.count();
    }

    cout<<t/10;


    //cout<<"done"<<v;

}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    for(int i=0; i<nVertices;i++)
    delete[] matrix[i];

    delete[] matrix;
    //write your destructor here
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    if(choice == 1)dir = true;
    else if(choice == 2)dir = false;

    Graph g(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("\n1. Add edge. 2. Remove an edge. 3.Check edge  4. No. of degree. \n");
        printf("5. Print Graph  6. Print adjacent vertices. 7.check common vertices.  8. Calculate Time.\n");
        printf("9. DFS  10. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int x,y;
            cin>>x>>y;
            g.removeEdge(x,y);

        }
        else if(ch==3)
        {
            int x,y;
            cin>>x>>y;
            if(g.isEdge(x,y)) cout<<"True";
            else cout<<"False";
        }
        else if(ch==4)
        {
            int x;
            cin>>x;
            cout<<g.getDegree(x);
        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            int x;
            cin>>x;
            g.printAdjVertices(x);
        }
        else if(ch==7)
        {
            int x,y;
            cin>>x>>y;
            if(g.hasCommonAdjacent(x,y)) cout<<"True";
            else cout<<"False";
        }
        else if(ch==8)
        {
            int x=1000,n=1;
            //cin>>x>>n;
            g.calculate(x,n,dir);
        }
        else if(ch==9)
        {
            int x;
            cout<<"Enter Source: ";
            cin>>x;
            g.DFS(x);
        }
        else if(ch==10)
        {
            break;
        }
    }

}
