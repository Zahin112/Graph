#include<bits/stdc++.h>
#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include<math.h>
#include <fstream>
#define INF 999999
#define NULL_VALUE -999999

using namespace std;

#define INF 9999999

class edge
{
    int u,v;
    double w;
public:
    edge(int u, int v, double w){
        this->u=u;
        this->v=v;
        this->w=w;
    }
    double getWeight(){
        return w;
    }
    int getV(){
        return v;
    }
    int setWeight(int w){
        this->w=w;
    }

};

class Graph
{
    vector<vector<edge>> adjList;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
    int nVertices;
    double **distanceMatrix, **parentMatrix;
    int *dist, *par;
    bool *visited, NegCycle=false;

public:
    Graph();
    void setnVertices(int n);
    bool addEdge(int u, int v, int w);
    void removeEdge(int u, int v);
    edge* searchEdge(int u, int v);
    void reWeightEdge(int u, int v, int w);
    bool isEdge(int u, int v);
    double getWeight(int u, int v);
    void floydWarshall();
    bool bellmanFord(int source);
    void dijkstra(int source);
    void johnsonAlgo();
    double getShortestPathWeight(int u, int v);
    void printShortestPath(int u, int v);
    void printDistanceMatrix();
    void printPredecessorMatrix();
    void cleanSPInfo();
    void printGraph();
    void path(int *p, int j);
    ~Graph();
};

Graph::Graph()
{
    nVertices=0;
}

void Graph::setnVertices(int n)
{
    n++;
    nVertices=n;
    adjList.resize(n);
    distanceMatrix = new double*[n];
    parentMatrix = new double*[n];
    visited = new bool[n];
    dist = new int[n];
    par= new int[n];
    for(int i=1;i<n;i++){
        distanceMatrix[i] = new double[n];
        parentMatrix[i] = new double[n];
    }
}

bool Graph::addEdge(int u, int v, int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
    adjList[u].push_back(edge(u,v,w));
    return true;
}



void Graph::removeEdge(int u, int v)
{
    for(auto i=adjList[u].begin();i!=adjList[u].end();i++){
        if(i->getV()==v)
            {
                adjList[u].erase(i);
                break;
            }
    }
}

edge* Graph::searchEdge(int u, int v)
{
    for(auto i=adjList[u].begin();i!=adjList[u].end();i++){
        if(i->getV()==v)
            break ;
    }
    return nullptr;
}

void Graph::reWeightEdge(int u, int v, int w)
{
    for(auto i=adjList[u].begin();i!=adjList[u].end();i++){
        if(i->getV()==v){
            i->setWeight(w);
            return;
        }
    }
    addEdge(u,v,w);
}

bool Graph::isEdge(int u, int v)
{
    for(auto i=adjList[u].begin();i!=adjList[u].end();i++){
        if(i->getV()==v)
            return true;

    }
    return false;
}
double Graph::getWeight(int u, int v)
{
    for(auto i=adjList[u].begin();i!=adjList[u].end();i++){
        if(i->getV()==v) {return i->getWeight();}
    }
    return INF;
}

bool Graph::bellmanFord(int source)
{
    for(int i=1; i<nVertices; i++){
        dist[i]=INF;
    }
    dist[source]=0;
    for(int i=1; i<nVertices; i++){
        for(int j=1; j<nVertices; j++){
            for(auto k=adjList[j].begin() ;k!=adjList[j].end(); k++){
                int v=k->getV();
                int w=k->getWeight();
                dist[v]=min(dist[v],dist[j]+w);
                //par[k]=j;
            }
        }
    }

    for(int i=1; i<nVertices; i++){
        for(auto j=adjList[i].begin(); j!=adjList[i].end(); j++){
            int v=j->getV();
            int w=j->getWeight();
            if(dist[v]>dist[i]+w){
                return true;
            }
        }
    }

    return false;
}

void Graph::dijkstra(int source)
{
    for(int i=1; i<nVertices; i++)
        {
            dist[i]=INF;
            //par[i]=-1;
            visited[i]=false;
        }

    dist[source]=0;

    for(int i=1; i<nVertices; i++){
        q.push(make_pair(dist[i],i));
    }
    while(!q.empty()){
        int u=q.top().second;
        q.pop();
        visited[u]=true;
        for(auto i=adjList[u].begin();i!=adjList[u].end();i++){
            int v=i->getV(), w=i->getWeight();
            if(!visited[v]){
                if(dist[v]>dist[u]+w){
                    dist[v]=dist[u]+w;
                    parentMatrix[source][v]=u;
                    q.push(make_pair(dist[v],v));
                }
            }
        }
    }
//    while(q.empty()){
//        cout<<q.top().second<< "b"<<endl;
//        q.pop();
//    }
}


void Graph::floydWarshall()
{
    cleanSPInfo();

    for(int i=1;i<nVertices;i++){
            distanceMatrix[i][i]=0;
        for(auto j=adjList[i].begin();j!=adjList[i].end();j++){
                distanceMatrix[i][j->getV()]=j->getWeight();
                parentMatrix[i][j->getV()]=i;
        }
    }

    for(int k=1;k<nVertices;k++){
        for(int i=1;i<nVertices;i++){
            if(i!=k)
            {
              for(int j=1;j<nVertices;j++){
                if(j!=k && (distanceMatrix[i][j]>distanceMatrix[i][k]+distanceMatrix[k][j]))
                    {
                    distanceMatrix[i][j]=distanceMatrix[i][k]+distanceMatrix[k][j];
                    parentMatrix[i][j]=k;
                    }
                }
            }
        }
    }
    cout<<"Floyd-Warshall algorithm implemented"<<endl;
}

void Graph::johnsonAlgo()
{
    cleanSPInfo();
    nVertices++;
    adjList.resize(nVertices);
    int src=nVertices-1, *modDist=new int[nVertices];
    for(int i=1; i<nVertices; i++){
        addEdge(src,i,0);
    }
    for(int i=1; i<nVertices; i++){
        dist[i]=0;
    }
    NegCycle=bellmanFord(src);
    if(NegCycle){
        cout<<"The graph contain negative edge cyle"<<endl;
        return;
    }

    nVertices--;
    for(int i=1; i<nVertices; i++)
        modDist[i]=dist[i];
    for(int i=1; i<nVertices; i++){
        for(auto j=adjList[i].begin();j!=adjList[i].end();j++){
            int v=j->getV(), w=j->getWeight();
            w=w+modDist[i]-modDist[v];
            j->setWeight(w);
        }
    }
    //printGraph();
    for(int i=1; i<nVertices; i++){
        dijkstra(i);
        for(int j=1; j<nVertices ; j++){
            distanceMatrix[i][j]=dist[j];
        }
    }
    for(int i=1; i<nVertices; i++){
        for(auto j=adjList[i].begin(); j!=adjList[i].end(); j++){
            int v=j->getV();
            int w=j->getWeight();
            w=w+modDist[v]-modDist[i];
            j->setWeight(w);
        }
    }
    for(int i=1; i<nVertices; i++){
        for(int j=1; j<nVertices; j++){
            if(distanceMatrix[i][j]!=INF)
                distanceMatrix[i][j]=distanceMatrix[i][j]+modDist[j]-modDist[i];
        }
    }
    cout<<"Johnson’s algorithm implemented"<<endl;
}

double Graph::getShortestPathWeight(int u, int v)
{
    cout<<distanceMatrix[u][v]<<endl;
}


/*
void Graph::path(int *p, int j)
{
    // Base Case : If j is source
    if (p[j] == - 1)
        {
        cout<<j;
        return;
        }
    path(p, p[j]);

    cout<<" -> "<<j;
}
*/
void Graph::printShortestPath(int u, int v)
{
   if(distanceMatrix[u][v] == INFINITY)
    {
        cout << "NO PATH!" << endl;
        return;
    }
    int p[nVertices],w[nVertices], pathLength=0;
    while(parentMatrix[u][v]!=-1){
        v=parentMatrix[u][v];
        p[pathLength++]=v;
    }
    cout<<u<<"->";
    for(int i=pathLength-2;i>=0;i--){
        cout<<p[i]<<"("<<distanceMatrix[p[i+1]][p[i]]<<")"<<"->";
    }
    cout<<v<<"("<<distanceMatrix[p[0]][v]<<")"<<endl;

}


void Graph::printDistanceMatrix()
{
    if(NegCycle) return;
    cout<<"The distance Matrix is : "<<endl;
    for(int i=1;i<nVertices;i++){
        for(int j=1;j<nVertices;j++){
            if(distanceMatrix[i][j]==INF) {
                cout<<"INF"<<" ";
            }
            else cout<<distanceMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

void Graph::printPredecessorMatrix()
{
    if(NegCycle) return;
    cout<<"The Predecessor Matrix is : "<<endl;
    for(int i=1;i<nVertices;i++){
        for(int j=1;j<nVertices;j++){
            if(parentMatrix[i][j]==-1) {
                cout<<"NIL"<<" ";
            }
            else cout<<parentMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

void Graph::cleanSPInfo()
{
    for(int i=1;i<nVertices;i++){
        for(int j=1;j<nVertices;j++){
            distanceMatrix[i][j]=INF;
            parentMatrix[i][j]=-1;
        }
    }
}

void Graph::printGraph()
{
    for(int i=1;i<nVertices;i++){
        cout<<i<<" : ";
        for(auto j=adjList[i].begin();j!=adjList[i].end();j++){
            cout<<j->getV()<<"("<<j->getWeight()<<") ";
        }
        cout<<endl;
    }
}

Graph::~Graph()
{
    adjList.clear();
    /*for(int i=0; i<nVertices;i++)
    {
        delete[] distance[i];
        delete[] visited[i];
    }
    delete[] distance;
    delete[] visited;*/
    delete distanceMatrix ;
    delete parentMatrix ;
    delete visited;
    delete dist;
    delete par;
}
int main()
{
   int n,m,u,v,w;
    cin>>n>>m;
    Graph g;
    g.setnVertices(n);
    for(int i=0;i<m;i++){
        cin>>u>>v>>w;
        g.addEdge(u,v,w);
    }
    cout<<"Graph Created"<<endl;
    int c;
    /*cout<<"1. Clear the values of the distance and parent matrices. ";
    cout<<"2. Implement Floyd-Warshall Algorithm. ";
    cout<<"3. Implement Johnson’s Algorithm."<<endl;
    cout<<"4. Print shortest path and it's weight. ";
    cout<<"5. Print graph. ";
    cout<<"6. Print Distance Mtarix."<<endl;
    cout<<"7. Print Predecessor Matrix."<<endl;*/
    while(1){
        cin>>c;
        if(c==1)
        {
            g.cleanSPInfo();
            cout<<"APSP matrices cleared"<<endl;
        }
        else if(c==2)
        {
            g.floydWarshall();

        }
        else if(c==3)
        {
            g.johnsonAlgo();

        }
        else if(c==4)
        {
            int s,d;
            cin>>s>>d;
            g.getShortestPathWeight(s,d);
            g.printShortestPath(s,d);
        }
        else if(c==5)
        {
            g.printGraph();
        }
        else if(c==6)
        {
            g.printDistanceMatrix();
        }
        else if(c==7)
        {
            g.printPredecessorMatrix();
        }
        else
        {
            break;
        }
    }

}

