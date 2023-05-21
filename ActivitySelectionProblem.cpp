#include <iostream>
#include<bits/stdc++.h>
#include <ctime>
using namespace std;

struct activity{
    int start, end;
};

bool compEnd(activity a1, activity a2){
    return (a1.end<=a2.end);
}

class ASL{
    activity *arr;
    int n;
public:
    void setActivities();
    void setRandActivities();
    void sortActivities();
    void printActivity();
    void SelectedActivity();
};

void ASL::setActivities(){
    cin >> n;
    arr=new activity[n];
    for(int i=0;i<n;i++){
        cin >> arr[i].start >> arr[i].end;
    }
}

void ASL::setRandActivities(){
    cin >> n;
    srand(time(0));
    arr=new activity[n];
    for(int i=0;i<n;i++){
        arr[i].start=rand()%23;
        arr[i].end=arr[i].start-rand()%24+24;
    }
}

void ASL::sortActivities(){
    sort(arr,arr+n,compEnd);
}

void ASL::printActivity(){
    for(int i=0;i<n;i++){
        cout << arr[i].start <<" "<<arr[i].end << endl;
    }
}

void ASL::SelectedActivity(){
    cout << arr[0].start <<" "<<arr[0].end<<endl;
    int x=arr[0].end;
    for(int i=0;i<n;i++){
        if(x<=arr[i].start){
            cout << arr[i].start <<" "<<arr[i].end<<endl;
            x=arr[i].end;
        }
    }
}
int main(){
    ASL s;
    s.setRandActivities();
    s.sortActivities();
    s.printActivity();
    s.SelectedActivity();
}
