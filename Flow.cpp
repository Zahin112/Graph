#include<bits/stdc++.h>
#include<iostream>
#include<queue>
#include<stack>
#include<vector>
#include<math.h>
#include <fstream>
#define INF 9999999
using namespace std;



class edge{
public:
    int first, second;
    edge(int u, int c){
        first = u;
        second = c;
    }
};

class Graph
{
    vector<vector<edge>> adjList;
    vector<vector<int>> flowMatrix;
    int nVertices, dir;

public:
    Graph(int d);
    void setnVertices(int n);
    bool addEdge(int u, int v, int f);
    void printGraph();
    void removeEdge(int u, int v);
    int BFS(int s, int t, vector<int> &p);
    int ford_fulkerson(int s, int t);
    void printflow();
    void printflowMatrix();
    bool bipartite(vector<int> & color);
    int max_matching();
    void printMatching();

};


Graph::Graph(int d)
{
    dir = d;
    nVertices = 0;
}


void Graph::setnVertices(int n)
{
    n++;
    nVertices=n;
    adjList.resize(n);
    flowMatrix.resize(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            flowMatrix[i].push_back(0);
    }

}

bool Graph::addEdge(int u, int v, int f)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;

    for(int i = 0; i < adjList[u].size(); i++)
        if(adjList[u][i].first == v)
            return false;

    adjList[u].push_back(edge(v,f)); flowMatrix[u][v] = f;
    if(!dir){
        adjList[v].push_back(edge(u,f)); flowMatrix[v][u] = f;
    }
    return true;
}


int Graph::BFS(int s, int t, vector<int> &p){

    queue<edge>q;
    q.push({s,INF});
    p[s] = 0;
    while(!q.empty()){
        int u = q.front().first;
        int f = q.front().second;
        q.pop();
        for(int i = 0; i < adjList[u].size(); i++){
            int v = adjList[u][i].first;
            if(p[v]  <0 && flowMatrix[u][v]){               //p[v] ==-1
                int minFlow = min(f, flowMatrix[u][v]);
                p[v] = u;
                if(v == t) return minFlow;
                q.push({v,minFlow});
            }
        }
    }
    return 0;
}



int Graph::ford_fulkerson(int s, int t){
    vector<int> par(nVertices);
    int flow=1, maxflow=0;
    while(1)
    {
        for(int i = 0; i < nVertices; i++) par[i] = -1;
        flow=BFS(s,t,par);
        if(flow == 0)
            break;

        maxflow += flow;
        int d=t;
        while(par[d] != 0)
        {
            flowMatrix[par[d]][d] -= flow;
            flowMatrix[d][par[d]] += flow;
            d = par[d];
        }
    }
    return maxflow;

}

void Graph::printflow(){
    int visited[nVertices];
    for(int i = 0; i < nVertices; i++) visited[i] = 0;

    for(int i = 1; i < nVertices; i++)
    {
        if(!visited[i])
        {
            queue<int> q;
            q.push(i);
            visited[i] = 1;
            while(!q.empty())
            {
                int u = q.front();
                q.pop();
                for(int j = 0; j < adjList[u].size(); j++)
                {
                    int v = adjList[u][j].first;
                    cout << u - 1 <<" "<< v - 1 <<" "<<max(0,adjList[u][j].second-flowMatrix[u][v]) <<"/"<<adjList[u][j].second<<endl;
                    if(!visited[v])
                    {
                        q.push(v);
                        visited[v] = 1;
                    }
                }
            }
        }

    }


}

bool Graph::bipartite(vector<int> &color){
    for(int i = 1; i < nVertices; i++)
    {
        if(color[i]==0)
        {
            color[i] = 1;
            queue<int> q;
            q.push(i);
            while(!q.empty())
            {
                int u = q.front();
                q.pop();
                for(int i = 0; i < adjList[u].size(); i++)
                {
                    int v = adjList[u][i].first;
                    if(!color[v])
                    {
                        if(color[u] == 1) color[v] = 2;
                        else color[v] = 1;
                        q.push(v);
                    }
                    else if(color[u] == color[v]) return false;
                }
            }
        }
    }
    for(int i = 1; i < nVertices; i++)
    {
        if(color[i] == 2)
        {
            for(int j = 0; j < adjList[i].size(); j++)
            {
                adjList[i][j].second = 0;
                flowMatrix[i][j] = 0;
            }
        }
    }
    return true;

}




int Graph::max_matching(){
    int s = nVertices, t = nVertices + 1; nVertices += 2;

    adjList.resize(nVertices);
    flowMatrix.resize(nVertices);
    int d = dir; dir = 1;

    vector<int> color(nVertices);

    for(int i = 0; i < nVertices; i++) color[i] = 0;

    if(!bipartite(color)){
        cout << "NOT BIPARTITE" << endl;
        return 0;
    }
    //Add source and sink edges
    /*for(int i = nVertices - 2; i < nVertices; i++)
    {
        for(int j = 0; j < nVertices; j++)
        {
            flowMatrix[i].push_back(0);
            flowMatrix[j].push_back(0);
        }
    }*/
    for(int j = 0; j < nVertices; j++)
    {
        flowMatrix[nVertices-2].push_back(0);
        flowMatrix[nVertices-1].push_back(0);
        flowMatrix[j].push_back(0);
    }

    for(int i = 1; i < nVertices - 2; i++){
        if(color[i] == 1) addEdge(s,i,1);
        else addEdge(i,t,1);
    }
    int maxFlow = ford_fulkerson(s,t);
    nVertices -= 2;
    adjList.resize(nVertices);
    flowMatrix.resize(nVertices);
    dir = d;
    return maxFlow;

}


void Graph::printMatching(){

    int visited[nVertices], take[nVertices];//taken
    for(int i = 0; i < nVertices; i++)
    {
        visited[i] = 0;
        take[i] = 0;
    }
    queue<int> q;
    q.push(1);
    visited[1] = 1;

    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        for(int i = 0; i < adjList[u].size(); i++)
        {
            int v = adjList[u][i].first;
            int c = adjList[u][i].second;
            if(u != nVertices && v != nVertices + 1)
            {
                if(!flowMatrix[u][v] && !take[v] && !take[u])   //c - flowMatrix[u][t] == 1
                {
                    cout << u - 1 <<" "<< v - 1 << endl;
                    take[v] = 1;
                    take[u] = 1;
                }
                if(!visited[v])
                {
                    q.push(v);
                    visited[v] = 1;
                }
            }
        }
    }
}




void Graph::printflowMatrix()
{
    for(int i = 0; i < nVertices; i++)
    {
        for(int j = 0; j < nVertices; j++)
            cout << flowMatrix[i][j]<<" ";
        cout << endl;
    }
}

void Graph::printGraph()
{
    cout<<"Graph : "<<endl;
    for(int i=1;i<nVertices;i++)
    {
        cout<<i<<" : ";
        for(int j = 0; j < adjList[i].size(); j++)
            cout<<adjList[i][j].first<< "(" << adjList[i][j].second <<") ";
        cout<<endl;
    }
}




int main()
{
    int ch;
    cout << "1 for maxflow \n0 for max-bipartite"<<endl;
    cin >> ch;

    int n,m;
    cin>> n >> m;

    Graph g(ch);
    g.setnVertices(n);

    for(int i = 0; i < m; i++){
            int u,v,c;
            if(ch)
            {
                cin>> u >> v >> c;
                g.addEdge(u + 1,v + 1,c);
            }
            else
            {
                cin>> u >> v;
                g.addEdge(u + 1,v + 1,1);

            }

    }

    if(ch){

        int s,t;
        cin>> s >> t;
        cout<< g.ford_fulkerson(s + 1,t + 1) << endl;
        g.printflow();
    }
    else{

        int matching = g.max_matching();
        if(matching){
            cout<<matching << endl;
            g.printMatching();
            g.printflowMatrix();
            g.printGraph();
        }
    }



    /*


    if(c == 1){
        int n,m;
        cin>> n >> m;

        Graph g(1);
        g.setnVertices(n);
        for(int i = 0; i < m; i++){
            int u,v,c;
            cin>> u >> v >> c;
            g.addEdge(u + 1,v + 1,c);
        }
        int s,t;
        cin>> s >> t;
        cout<< g.ford_fulkerson(s + 1,t + 1) << endl;
        g.printflow();
    }
    else if(c == 2){
        int n,m;
        cin>> n >> m;
        Graph g(0);
        g.setnVertices(n);
        for(int i = 0; i < m; i++){
            int u,v,c;
            cin>> u >> v;
            g.addEdge(u + 1,v + 1,1);
        }
        int matching = g.max_matching();
        if(matching){
            cout<<matching << endl;
            g.printMatching();
            g.printflowMatrix();
            g.printGraph();
        }
    }*/

}
