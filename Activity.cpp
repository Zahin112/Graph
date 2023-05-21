#include<iostream>

using namespace std;

struct Activity{
    int x;
    int start;
    int finish;
};

void ActivitySelection(Activity arr[], int n){
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j<n-1 ; j++){
            if(arr[j].finish > arr[j].finish){
                Activity temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    cout<<"Selected activities are : ......"<<endl;
    cout<<"Activity : Start  Finish"<<endl;
    cout<<arr[0].x<<"        : "<<arr[0].start<<"      "<<arr[0].finish<<endl;

    int i = 0;
    for(int j = 1; j < n ; j++){
        if(arr[j].start >= arr[i].finish){
            cout<<arr[j].x<<"        : "<<arr[j].start<<"      "<<arr[j].finish<<endl;
            i = j;
        }

    }

}

int main(){
    Activity arr[6] = {
    {1,0,3},
    {2,1,4},
    {3,1,2},
    {4,4,6},
    {5,2,9},
    {6,5,8}
    };

    ActivitySelection(arr,6);
}
