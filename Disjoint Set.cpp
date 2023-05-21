#include<iostream>

using namespace std;

class DisjointSet{
    int *PrintArray;
    int *parent;
    int *rank;
    int data;
    int j;
public:
    DisjointSet(){
        PrintArray = new int[1];
        parent = new int[1];
        rank = new int[1];
        j = 0;
    }
    void makeSet(int x){
        PrintArray[j] = x;
        parent[x] = x;
        rank[x] = 0;
        j++;
    }
    int findSet(int x){
        if(parent[x] != x){
            parent[x] = findSet(parent[x]);
        }
        return parent[x];
    }

    void unionSet(int u, int v){
        int a = findSet(u);
        int b = findSet(v);

        if(a == b){
            return;
        }

        if(rank[a] >= rank[b]){
            parent[b] = a;
            if(rank[a] == rank[b]){
                rank[a] = rank[a] + 1;
            }
        }
        else{
            parent[a] = b;
        }
    }

    void printSet(int x){

        for(int i = 0; i < j; i++){
            if(findSet(x) == findSet(PrintArray[i])){
                cout<<PrintArray[i]<<"\t";
            }

        }
        cout<<endl;

    }
};

int main(){
    DisjointSet s;
    s.makeSet(1);
    s.makeSet(2);
    s.makeSet(3);
    s.makeSet(4);
    s.unionSet(1,2);
    s.unionSet(2,3);
    s.unionSet(1,4);

    s.printSet(3);
    s.makeSet(5);
    s.makeSet(6);
    s.makeSet(7);
    s.makeSet(8);
    s.unionSet(5,6);
    s.unionSet(6,7);
    s.printSet(7);




}
