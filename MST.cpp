#include<bits/stdc++.h>

using namespace std;

ofstream outf;

#define INF 999999

class edge
{
    int u,v,w;
public:
    edge(){
        u=0;
        v=0;
        w=0;
    }
    void setval(int u, int v, int w){
        this->u=u;
        this->v=v;
        this->w=w;
    }
    int getu() {return u;}
    int getv() {return v;}
    int getw() {return w;}
    //friend bool operator<(edge e1, edge e2);
};
/*bool operator<(edge e1, edge e2)
{
    return e1.w<e2.w;
}*/

bool compareedge(edge e1, edge e2)
{
    return e1.getw()<e2.getw();
};

class Graph
{
    vector<vector<pair<int,int>>> g;
    int nVertices, nEdges, *key, *tree, *parent;
    bool *visited;
    edge *e;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
public:
    Graph(int n, int m);
    ~Graph();
    void setnVertices(int n, int m);
    void addEdge(int u,int v, int w);
    void prim(int r);
    void kruskal();
    void printGraph();
    void printTree();
    int findset(int x);
    void Union(int x, int y);
};

Graph::Graph(int n, int m)
{
    nEdges=0;
    nVertices=n;
    key=new int[n];
    parent=new int[n];
    tree=new int[n];
    visited=new bool[n];
    e=new edge[m];
    g.resize(n);
}
/*
void Graph::setnVertices(int n, int m)
{

    nVertices=n;
    key=new int[n];
    parent=new int[n];
    tree=new int[n];
    visited=new bool[n];
    e=new edge[m];
    g.resize(n);

}
*/
void Graph::addEdge(int u, int v, int w)
{

    nEdges++;
    g[u].push_back(make_pair(v,w));
    g[v].push_back(make_pair(u,w));
    e[nEdges].setval(u,v,w);

}

void Graph::printTree()
{
    for(int i=0;i<nVertices;i++){
        if(tree[i]!=-1){
            cout<<tree[i]<<" "<<i<<endl;
            outf<<tree[i]<<" "<<i<<endl;
        }
    }
}

int Graph::findset(int x)
{

    while(parent[x]>=0){
        x=parent[x];
    }
    return x;

}

void Graph::Union(int x, int y)
{

    int p1=findset(x), p2=findset(y);
    int r1=-parent[p1], r2=-parent[p2];
    if(r1>r2){
        parent[p2]=p1;
        //r1++;
        //parent[p1]=-r1;
    }
    else if(r1<r2){
        parent[p1]=p2;
        //r2++;
        //parent[p2]=-r2;
    }
    else
    {
        parent[p2]=p1;
        r1++;
        parent[p1]=-r1;
    }

}

void Graph:: prim(int s)
{

    int sum=0;
    for(int i=0 ;i<nVertices; i++)
    {
        key[i]=INF;
        visited[i]=false;
        tree[i]=-1;
    }
    key[s]=0;
    for(int i=0;i<nVertices;i++){
        q.push({key[i],i});
    }

    while(!q.empty())
    {
        int u=q.top().second;
        q.pop();

        visited[u]=true;
        for(int i=0; i<g[u].size(); i++){
            int v=g[u][i].first ,w=g[u][i].second;
            if(!visited[v] && w<key[v])
                {
                key[v]=w;
                tree[v]=u;
                q.push({key[v],v});
                }
        }
    }

    for(int i=0; i<nVertices; i++){
        sum+=key[i];
    }
    cout<<"Total weight:"<<sum<<endl;
    outf<<"Total weight:"<<sum<<endl;

}

void Graph::kruskal()
{

    int s=0;
    for(int i=0; i<nVertices; i++){
        parent[i]=-1;
        tree[i]=-1;
        key[i]=INF;
    }

    sort(e,e+nEdges,compareedge);

    for(int i=0; i<nEdges; i++){
        int u=e[i].getu(), v=e[i].getv(), w=e[i].getw();
        if(findset(u)!=findset(v)){
            Union(u,v);
            cout<<u<<" "<<v<<endl;
            outf<<u<<" "<<v<<endl;
            //tree[v]=u;
            s+=w;
        }
    }

    cout<<"Total weight:"<<s<<endl;
    outf<<"Total weight:"<<s<<endl;


    //for(int i=0;i<nVertices;i++) cout<<tree[i]<<" ";
    //cout<<endl;
}

void Graph::printGraph()
{

    cout<<"Graph : "<<endl;
    for(int i=0;i<nVertices;i++){
        cout<<i<<" : ";
        //outf<<i<<" : ";
        for(auto j=g[i].begin(); j!=g[i].end(); j++){
            cout<<j->first<<"("<<j->second<<") ";
            //outf<<j->first<<"("<<j->second<<") ";
        }
        cout<<endl;
    }

}


Graph::~Graph()
{
    delete[] key;
    delete[] parent;
    delete[] visited;
    delete[] tree;
    delete[] e;
    /*key=0;
    parent=0;
    visited=0;*/

}


int main()
{

    //cout<<"RUNNING"<<endl;
    int n,m,u,v,w,s;
    //cin>>n>>m;
    //Graph g;


    ifstream inf;
    inf.open("input.txt");
    inf>>n>>m;
    Graph g(n,m);
    //cout<<"graph";
    for(int i =0; i<m ; i++)
        {
          inf>>u>>v>>w;
          //cout<<u<<" "<<v<<" "<<w<<endl;
          g.addEdge(u,v,w);
        }
    //inf>>src>>dest;
    //g.setnVertices(8,14);
//    for(int i=0;i<m;i++){
//        cin>>u>>v>>w;
//        g.addEdge(u,v,w);
//    }
    outf.open("output.txt", ios::trunc);//ios::app = for appending at last ios::ate = set the start,default begining
    //g.printGraph();
    cout<<"Prims Algo: "<<endl;
    outf<<"Prims Algo: "<<endl;
    g.prim(0);
    g.printTree();
    cout<<"Kruskals Algo: "<<endl;
    outf<<"Kruskals Algo: "<<endl;
    g.kruskal();
    //g.printTree();

}
