#include <iostream>
#include<stdio.h>
#include<cmath>
#include<Fstream>

using namespace std;
ofstream outf;
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
	void setnVertices(int n,int m);
	void addEdge(int u, int v,int w);
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
    int minDistance(int *dist, bool *sptSet);
    int solution(int *dist);
    void path(int *p, int j);
    void dijkstra(int src,int dest);
    void bellmanford(int src,int dest);


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

void Graph::setnVertices(int n,int m)
{
	this->nVertices = n ;
	this->nEdges=m;

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

void Graph::addEdge(int u, int v, int w)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    this->nEdges++ ;
    matrix[u][v] = w;
    if(!directed) matrix[v][u] = w;

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
int Graph::minDistance(int *dist, bool *sptSet)
{

    int min = INT_MAX, min_index;
    for (int i = 0; i < nVertices; i++)
        if (sptSet[i] == false && dist[i] <= min)
            min = dist[i], min_index = i;

    return min_index;
}

int Graph::solution(int *dist)
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < nVertices; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

void Graph::path(int *p, int j)
{
    // Base Case : If j is source
    if (p[j] == - 1)
        {
        outf<<j;
        return;
        }
    path(p, p[j]);

    outf<<" -> "<<j;
}

void Graph::dijkstra(int src, int dest)
{
    int dist[nVertices];

    bool sptSet[nVertices];//stores if a vertex is in the path
    int parent[nVertices];

    for (int i = 0; i < nVertices; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;
    parent[src]=-1;

    for (int j = 0; j < nVertices - 1; j++) {
        int u = minDistance(dist, sptSet);

        sptSet[u] = true;

        for (int i = 0; i < nVertices; i++)

            if (!sptSet[i] && abs(matrix[u][i]) && dist[u] != INT_MAX && dist[u] + abs(matrix[u][i]) < dist[i])//sptset checks if the vertex is visited once like poping from stack
                {
                dist[i] = dist[u] + abs(matrix[u][i]);
                parent[i]=u;
                }

    }

    //solution(dist);
    outf<<dist[dest]<<endl;
    path(parent,dest);
    outf<<endl;
    //path(parent,4);
}

/*void Graph:: relax(int u, int v, int w)
{
    if (dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
}*/

void Graph::bellmanford(int src,int dest)
{
    int dist[nVertices];
    int parent[nVertices];
    //bool flag = true;
    //int i,j;

    for (int i = 0; i < nVertices ; i++)
        dist[i] = INT_MAX;

    dist[src] = 0;
    parent[src]=-1;

    for (int i = 1; i < nVertices + nEdges; i++)
    {
        for (int j = 0; j < nVertices; j++)
        {
            for (int k= 0; k < nVertices; k++)
            {
            if( matrix[j][k]!=0 && dist[j]!=INT_MAX && dist[j] + matrix[j][k] < dist[k])
                {
                    //cout<<matrix[j][k]<<endl;
                    parent[k]=j;
                    dist[k] = dist[j] + matrix[j][k];
                }

            }
        }
    }
    //solution(dist);&& dist[i]!=INT_MAX
    //int flag=1;
    //for(int i=0;i<nVertices;i++)
        //cout<<dist[i]<<endl;
    for (int i = 0; i < nVertices; i++)
    {
        for(int j = 0; j < nVertices; j++)
        {
            if (matrix[i][j]!=0 && /*dist[i]!=INT_MAX  &&*/  dist[i] + matrix[i][j] < dist[j])
            {
                cout<<"This graph contains negative edge cycle\n";
                //flag = false;
                return;

            }
        }
    }
    //cout<<flag;

        outf<<dist[dest]<<endl;
        path(parent,dest);


    //return;
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




main(){

    int n,u,v,w,m,src,dest;
    int choice;
    bool dir;
    /*printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    if(choice == 1)dir = true;
    else if(choice == 2)dir = false;
*/
    Graph g(1);
    /*printf("Enter number of vertices: ");
    scanf("%d", &n);
    cin>>m;
    g.setnVertices(n,m);
    for(int i =0; i<N ; i++)
        {
          cin>>u>>v>>w;
          g.addEdge(u,v,w);

        }
    g.dijkstra(0,5);
    g.bellmanford(0,5);*/
    ifstream inf;
    inf.open("input.txt");
    inf>>n>>m;
    g.setnVertices(n,m);
    for(int i =0; i<m ; i++)
        {
          inf>>u>>v>>w;
          g.addEdge(u,v,w);
        }
    inf>>src>>dest;
    //g.dijkstra(src,dest);
    //g.bellmanford(src,dest);
    //ofstream outf;
    outf.open("output.txt", ios::trunc);//ios::app = for appending at last ios::ate = set the start,default begining
    outf<<"BellmanFord Algorithm:"<<endl;
    g.bellmanford(src,dest);
    outf<<endl<<"Dijkstra Algorithm:"<<endl;
    g.dijkstra(src,dest);
}
