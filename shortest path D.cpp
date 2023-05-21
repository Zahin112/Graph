#include<bits/stdc++.h>
using namespace std;

#define INFINITY 1000000000

class Graph
{
    vector<vector<pair<int,int>>> adjList;
    int nVertices, edges;
    priority_queue <pair<int,int> , vector<pair<int,int>>, greater<pair<int,int>>> q;
    bool *visited, hasNegativeWeight, hasNegativeEdgeCycle=false;
    int *distance,*path,noOfVertex, *parent;
public:
    Graph(int n, int e);
    void addEdge(int u, int v, int w);
    void calculateShortestPath();
    void bellmanFord(int source,int dest);
    void dijkstra(int source,int dest);
    void printShortestPath(int source,int dest);
    void printGraph();
    ~Graph();
};

Graph::Graph(int n,int e)
{
    adjList.resize(n);
    nVertices=n;
    noOfVertex=0;
    edges=e;
    visited=new bool[n];
    distance=new int[n];
    path=new int[edges];
    parent=new int[n];
}

void Graph::addEdge(int u, int v, int w)
{
    if(w<0) hasNegativeWeight=true;
    adjList[u].push_back(make_pair(v,w));
}

void Graph::printGraph()
{
    for(int u=0;u<nVertices;u++){
        cout<<u<<" : ";
        for(auto it=adjList[u].begin();it!=adjList[u].end();it++){
            cout<<it->first<<"("<<it->second<<") ";
        }
        cout<<endl;
    }
    cout<<endl;
}

Graph::~Graph()
{
    if(distance) delete[] distance;
    if(visited) delete[] visited;
    distance=0;
    visited=0;
}

void Graph::dijkstra(int source, int dest)
{
    noOfVertex=0;
    parent[source]=-1;
    for(int i=0;i<nVertices;i++) visited[i]=false;
    for(int i=0;i<nVertices;i++) distance[i]=INFINITY;
    distance[source]=0;
    for(int i=0;i<nVertices;i++){
        q.push(make_pair(distance[i],i));
    }
    while(!q.empty()){
        int u=q.top().second;
        q.pop();
        visited[u]=true;
        if(u==dest) return;
        for(auto it=adjList[u].begin();it!=adjList[u].end();it++){
            int v=it->first, w=it->second;
            if(w<0) w=-w;
            if(!visited[v]){
                if(distance[v]>distance[u]+w){
                    distance[v]=distance[u]+w;
                    parent[v]=u;
                    q.push(make_pair(distance[v],v));
                }
            }
        }
    }
}

void Graph::bellmanFord(int source,int dest)
{
    noOfVertex=0;
    parent[source]=-1;
    for(int i=0;i<nVertices;i++) distance[i]=INFINITY;
    distance[source]=0;
    queue<int> bq;  ///bellmanFrod queue
    for(int i=0;i<nVertices-1;i++){
        for(int j=0;j<nVertices;j++) visited[j]=false;
        bq.push(source);
        while(!bq.empty()){
            int u=bq.front();
            bq.pop();
            visited[u]=true;
            for(auto it=adjList[u].begin();it!=adjList[u].end();it++){
                int v=it->first, w=it->second;
                if(distance[v]>distance[u]+w){
                    distance[v]=distance[u]+w;
                    parent[v]=u;
                }
                if(!visited[v]) {
                    bq.push(v);
                    visited[v]=true;
                }
            }
        }
    }
    for(int j=0;j<nVertices;j++) visited[j]=false;
    bq.push(source);
    while(!bq.empty()){
        int u=bq.front();
        bq.pop();
        visited[u]=true;
        for(auto it=adjList[u].begin();it!=adjList[u].end();it++){
            int v=it->first, w=it->second;
            if(distance[v]>distance[u]+w)  {hasNegativeEdgeCycle=true; return;}
            if(!visited[v]) {
                bq.push(v);
                visited[v]=true;
            }
        }
    }
}

void Graph::printShortestPath(int source, int dest)
{
    cout<<"Bellamnford algorithm : "<<endl;
    bellmanFord(source,dest);
    if(distance[dest]==INFINITY) cout<<"Unrechable"<<endl;
    else{
        cout<<distance[dest]<<endl;
        int i=dest;
        while(parent[i]!=-1){
            path[noOfVertex++]=parent[i];
            i=parent[i];
        }
        for(int i=noOfVertex-1;i>=0;i--) cout<<path[i]<<"->";
        cout<<dest<<endl;
    }

    cout<<"Dijkstra algorithm : "<<endl;
    dijkstra(source,dest);
    if(distance[dest]==INFINITY) cout<<"Unrechable"<<endl;
    else{
        cout<<distance[dest]<<endl;
        int i=dest;
        noOfVertex=0;
        while(parent[i]!=-1){
            path[noOfVertex++]=parent[i];
            i=parent[i];
        }
        for(int i=noOfVertex-1;i>=0;i--) cout<<path[i]<<"->";
        cout<<dest<<endl;
    }
}

int main()
{
    int n,edges,s,d;
    freopen("input.txt", "r", stdin);
    cin>>n>>edges;
    Graph g(n,edges);
    for(int i=0;i<edges;i++)
    {
        int u,v,w; cin>>u>>v>>w;
        g.addEdge(u,v,w);
    }

    g.printGraph();
    cin>>s>>d;
    freopen("output.txt", "w",stdout);
    g.printShortestPath(s,d);

}

