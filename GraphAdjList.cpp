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
	rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
	length-- ;
	delete data;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;  // doubling memory when array is full
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	int *color;
	int *parent;
	int *dist;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source);
	void dfshelp(int s,int *visited);
    void dfs(int s);
    int getOutDegree(int u);
    int getInDegree(int u);
    void calculate(int v,int n,bool dir);

 //will run bfs in the graph

};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    adjList[u].removeItem(v);
    if(!directed) adjList[v].removeItem(u);
    //write this function
}

bool Graph::isEdge(int u, int v)
{
    if((adjList[u].searchItem(v)==NULL_VALUE)&&(adjList[v].searchItem(u)==NULL_VALUE))
        return false;
    else return true;
    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph::getDegree(int u)
{
    return adjList[u].getLength();
    //returns the degree of vertex u
}

void Graph::printAdjVertices(int u)
{
    for(int i=0;i<adjList[u].getLength();i++)
        cout<<adjList[u].getItem(i)<<"\t";
    //prints all adjacent vertices of a vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    for(int i=0;i<adjList[u].getLength();i++)
    {
        for(int j=0;j<adjList[v].getLength();j++)
        {
            if(adjList[u].getItem(i)==adjList[v].getItem(j))
                return true;
        }
    }
    return false;//returns true if vertices u and v have common adjacent vertices

}

void Graph::bfs(int source)
{
   /* bool *visited = new bool[nVertices];
    for(int i = 0; i < nVertices; i++)
        visited[i] = false;
    Queue q;
    visited[source] = true;
    //queue.push_back(source);
    q.enqueue(source);
    int i;
    while(!q.empty())
    {
        cout << q.dequeue() << " ";
        for (i = 0; i <= adjList[source].getLength(); ++i)
        {if (!visited[i])
            {visited[i] = true;
            q.enqueue(adjList[source].getItem(i));
            }
        }
    }*/

    Queue q;
    for(int i=0; i<nVertices;i++)
    {
        if(i==source){
        color[i] = GREY;
        dist[i] = 0;
        }
        else{
             color[i] = WHITE;
             dist[i] = INFINITY;
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
        if(isEdge(s,i))
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

    //complete this function
    //initialize BFS variables for all n vertices first

}

int Graph::getDist(int u, int v)
{
    bfs(u);
    return dist[v];
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    return INFINITY ;
}



void Graph::dfshelp(int s,int *visited)
{
    cout<< s <<endl;
    visited[s]= 1;

    for (int i=0; i<nVertices; i++)
    {
        if(!visited[i] && isEdge(s,i))
            dfshelp(i,visited);
    }
}
void Graph::dfs(int s)
{

    int *visited= new int(nVertices);
    for(int i =0 ;i<nVertices; i++)
    {
        visited[i]=0;
    }

    dfshelp(s,visited);


}
void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

int Graph::getOutDegree(int i)
{
    return adjList[i].getLength();
}

int Graph::getInDegree(int s)
{
    if(directed)
    {
        int n=0;
        for(int i=0;i<nVertices;i++)
        {
        if(i!=s)
        {
           for(int j=0; j<adjList[i].getLength();j++)
            {
            if(adjList[i].getItem(j)==s)
                n++;
            }
        }

        }

        return n;

    }
}

void Graph::calculate(int v,int n,bool dir)
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
        cout<<"gs";
        g1.bfs(rand()%v);
        cout<<"ge";
        auto stop = chrono::high_resolution_clock::now();
        //cout<<"gt";
        cout<<duration_cast<chrono::nanoseconds>(stop - start).count();

        //cout<<duration.count();
    }

    cout<<t/10;


    //cout<<"done"<<v;

}

Graph::~Graph()
{
    delete[] adjList;
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
            g.dfs(x);
        }
        else if(ch==10)
        {
            break;
        }
    }

}
