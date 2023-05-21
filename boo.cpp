#include<bits/stdc++.h>
using namespace std;

#define INFINITY 1e8+1

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
    int *dist, *parent;
    bool *visited, hasNegativeEdgeCycle=false;

public:
    Graph();
    void setnVertices(int n);
    bool addEdge(int u, int v, int w);
    void printGraph();
    void removeEdge(int u, int v);
    edge* searchEdge(int u, int v); /// jhamela
    void reWeightEdge(int u, int v, int w);
    bool isedge(int u, int v);
    double getWeight(int u, int v);
    /// *** all pair shortest path functions *** ///
    void floydWarshall();
    bool bellmanFord(int source);
    void dijkstra(int source);
    void johnsonAlgo();
    double getShortestPathWeight(int u, int v);
    void printShortestPath(int u, int v);
    void printDistanceMatrix();
    void printPredecessorMatrix();
    void cleanSPInfo();
};

Graph::Graph()
{
    //adjList.resinVer
    nVertices=0;
}

void Graph::setnVertices(int n)
{
    nVertices=n+1;
    n++;
    adjList.resize(n);
    distanceMatrix = new double*[n];
    parentMatrix = new double*[n];
    visited = new bool[n];
    dist = new int[n];
    parent = new int[n];
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

void Graph::printGraph()
{
    for(int i=1;i<nVertices;i++){
        cout<<i<<" : ";
        for(auto it=adjList[i].begin();it!=adjList[i].end();it++){
            cout<<it->getV()<<"("<<it->getWeight()<<") ";
        }
        cout<<endl;
    }
}

void Graph::removeEdge(int u, int v)
{
    for(auto it=adjList[u].begin();it!=adjList[u].end();it++){
        if(it->getV()==v) {adjList[u].erase(it); break;}
    }
}

edge* Graph::searchEdge(int u, int v)
{
    for(auto it=adjList[u].begin();it!=adjList[u].end();it++){
        if(it->getV()==v) {break ;}
    }
    return nullptr;
}

void Graph::reWeightEdge(int u, int v, int w)
{
    for(auto it=adjList[u].begin();it!=adjList[u].end();it++){
        if(it->getV()==v){
            it->setWeight(w);
            return;
        }
    }
    addEdge(u,v,w);
}

bool Graph::isedge(int u, int v)
{
    for(auto it=adjList[u].begin();it!=adjList[u].end();it++){
        if(it->getV()==v) {return true;}
    }
    return false;
}
double Graph::getWeight(int u, int v)
{
    for(auto it=adjList[u].begin();it!=adjList[u].end();it++){
        if(it->getV()==v) {return it->getWeight();}
    }
    return 1e7;
}

void Graph::floydWarshall()
{
    cleanSPInfo();
    for(int i=1;i<nVertices;i++){
        distanceMatrix[i][i]=0;
    }
    for(int i=1;i<nVertices;i++){
        for(auto it=adjList[i].begin();it!=adjList[i].end();it++){
            distanceMatrix[i][it->getV()]=it->getWeight();
            parentMatrix[i][it->getV()]=i;
        }
    }
    for(int k=1;k<nVertices;k++){
        for(int i=1;i<nVertices;i++){
            for(int j=1;j<nVertices;j++){
                if(distanceMatrix[i][j]>distanceMatrix[i][k]+distanceMatrix[k][j]
                   && distanceMatrix[i][k]<INFINITY && distanceMatrix[k][j]<INFINITY){
                    distanceMatrix[i][j]=distanceMatrix[i][k]+distanceMatrix[k][j];
                    parentMatrix[i][j]=k;
                    cout<<"parentMarix["<<i<<"]"<<"["<<j<<"]"<<parentMatrix[i][j]<<endl;
                }
            }
        }
    }
    printPredecessorMatrix();
}

bool Graph::bellmanFord(int source)
{
    for(int i=1;i<nVertices;i++){
        dist[i]=INFINITY;
    }
    dist[source]=0;
    for(int i=1;i<nVertices;i++){
        for(int u=1;u<nVertices;u++){
            for(auto it=adjList[u].begin();it!=adjList[u].end();it++){
                int v=it->getV();
                int w=it->getWeight();
                dist[v]=min(dist[v],dist[u]+w);
            }
        }
    }

    for(int u=1;u<nVertices;u++){
        for(auto it=adjList[u].begin();it!=adjList[u].end();it++){
            int v=it->getV(), w=it->getWeight();
            if(dist[v]>dist[u]+w){
                return true;
            }
        }
    }

    return false;
}

void Graph::dijkstra(int source)
{
    for(int i=1;i<nVertices;i++) {
        dist[i]=INFINITY;
        parent[i]=-1;
        visited[i]=false;
    }
    dist[source]=0;
    for(int i=1;i<nVertices;i++){
        q.push(make_pair(dist[i],i));
    }
    while(!q.empty()){
        int u=q.top().second;
        q.pop();
        visited[u]=true;
        for(auto it=adjList[u].begin();it!=adjList[u].end();it++){
            int v=it->getV(), w=it->getWeight();
            if(!visited[v]){
                if(dist[v]>dist[u]+w){
                    dist[v]=dist[u]+w;
                    parent[v]=u;
                    q.push(make_pair(dist[v],v));
                }
            }
        }
    }
}

void Graph::johnsonAlgo()
{
    cleanSPInfo();
    nVertices++;
    adjList.resize(nVertices);
    int source=nVertices-1, *newDist=new int[nVertices];
    for(int i=1;i<nVertices;i++){
        addEdge(source,i,0);
    }
    if(dist){
        delete[] dist;
        dist=0;
    }
    dist = new int[nVertices];
    hasNegativeEdgeCycle=bellmanFord(source);
    if(hasNegativeEdgeCycle){
        cout<<"The graph contain negative edge cyle"<<endl;
        return;
    }
    nVertices--;
    for(int i=1;i<nVertices;i++) newDist[i]=dist[i];
    for(int u=1;u<nVertices;u++){
        for(auto it=adjList[u].begin();it!=adjList[u].end();it++){
            int v=it->getV(), w=it->getWeight();
            w=w+newDist[u]-newDist[v];
            it->setWeight(w);
        }
    }
    for(int i=1;i<nVertices;i++){
        dijkstra(i);
        for(int j=1;j<nVertices;j++){
            distanceMatrix[i][j]=dist[j];
            parentMatrix[i][j]=parent[j];
        }
    }
    for(int u=1;u<nVertices;u++){
        for(auto it=adjList[u].begin();it!=adjList[u].end();it++){
            int v=it->getV(), w=it->getWeight();
            w=w+newDist[v]-newDist[u];
            it->setWeight(w);
        }
    }
    for(int i=1;i<nVertices;i++){
        for(int j=1;j<nVertices;j++){
            if(distanceMatrix[i][j]!=INFINITY)
                distanceMatrix[i][j]=distanceMatrix[i][j]+newDist[j]-newDist[i];
        }
    }
}

double Graph::getShortestPathWeight(int u, int v)
{
    cout<<"Shortest Path weight : "<<distanceMatrix[u][v]<<endl;
}

void Graph::printShortestPath(int source, int dest)
{
    int path[nVertices],weight[nVertices], pathLength=0,u=source,v=dest;
    while(parentMatrix[u][v]!=-1){
        v=parentMatrix[u][v];
        path[pathLength++]=v;
    }
    cout<<source<<"->";
    for(int i=pathLength-2;i>=0;i--){
        cout<<path[i]<<"("<<distanceMatrix[path[i+1]][path[i]]<<")"<<"->";
    }
    cout<<dest<<"("<<distanceMatrix[path[0]][dest]<<")"<<endl;
}

void Graph::printDistanceMatrix()
{
    if(hasNegativeEdgeCycle) return;
    cout<<"The distance Matrix is : "<<endl;
    for(int i=1;i<nVertices;i++){
        for(int j=1;j<nVertices;j++){
            if(distanceMatrix[i][j]==INFINITY) {
                cout<<"INF"<<" ";
                continue;
            }
            cout<<distanceMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

void Graph::printPredecessorMatrix()
{
    cout<<"Predecessor Matrix : "<<endl;
    for(int i=1;i<nVertices;i++){
        for(int j=1;j<nVertices;j++){
            if(parentMatrix[i][j]==-1) cout<<"NIL"<<" ";
            else cout<<parentMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

void Graph::cleanSPInfo()
{
    for(int i=1;i<nVertices;i++){
        for(int j=1;j<nVertices;j++){
            distanceMatrix[i][j]=INFINITY;
            parentMatrix[i][j]=-1;
        }
    }
}

int main()
{
//    Graph g;
//    g.setnVertices(4);
//    g.addEdge(0,1,2);
//    g.addEdge(1,0,-1);
//    g.addEdge(2,3,-1);
//    g.addEdge(2,1,4);
//    g.addEdge(3,0,1);
//    g.addEdge(3,1,2);
//
//    g.printGraph();
//    g.johnsonAlgo();
//    g.printDistanceMatrix();
//    g.printPredecessorMatrix();
//    g.getShortestPathWeight(2,0);
//    g.printShortestPath(2,0);
//    cout<<"++++++++++++++++++"<<endl;
//    g.floydWarshall();
//    g.printDistanceMatrix();
//    g.printPredecessorMatrix();
//    g.getShortestPathWeight(2,0);
//    g.printShortestPath(2,0);

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
    cout<<"1. Clear the values of the distance and parent matrices."<<endl;
    cout<<"2. Implement Floyd-Warshall Algorithm."<<endl;
    cout<<"3. Implement Johnson’s Algorithm."<<endl;
    cout<<"4. Print shortest path and it's weight."<<endl;
    cout<<"5. Print graph."<<endl;
    cout<<"6. Print Distance Mtarix."<<endl;
    cout<<"7. Print Predecessor Matrix."<<endl;
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
            cout<<"Floyd-Warshall algorithm implemented"<<endl;
        }
        else if(c==3)
        {
            g.johnsonAlgo();
            cout<<"Johnson’s algorithm implemented"<<endl;
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


