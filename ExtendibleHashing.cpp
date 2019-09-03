#include<bits/stdc++.h>
#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

class Bucket{
    public:
    int size;
    int curr;
    int localdepth;
    int *arr;
    Bucket(){
        curr=0;
        size = 3;
        localdepth = 1;
        arr = new int[size];
        memset(arr, 0, size*sizeof(arr[0]));
    }

};

class Directory{
    public:
    int globaldepth;
    vector<Bucket*> barr;
    void insertElement(int);
    void search(int);
    Directory(){
        globaldepth = 1;
        Bucket *newBucket = new Bucket();
        Bucket *newBucket1 = new Bucket();
        barr.push_back(newBucket);
        barr.push_back(newBucket1);
        
    }

};
void Directory :: search(int data){
    int x = (pow(2,globaldepth));
    int index = data % x;
    int i=0,flag=0;
    while(i<=barr[index]->curr-1){
        if(data == barr[index]->arr[i])
        {
            cout<<"data found"<<endl;
            flag=1;
            break;
        }
        i++;
    }
    if(!flag) cout<<"data not found"<<endl;
    

}
void  Directory :: insertElement(int data){
    int x = (pow(2,globaldepth));
    int index = data % x;
    //cout<<index<<endl;
    //cout<<barr[index]->curr;
    if(barr[index]->curr < 3){
        barr[index]->arr[barr[index]->curr++] = data;
    }
    else{
        if(barr[index]->localdepth == globaldepth){ //Directory Expansion and Perform Bucket Split
            //Expanding the directory
            vector<Bucket*> barr1;
            long entry = pow(2,globaldepth+1);
            int flag = 0;
            for(int i=0; i<entry; i++){
                if(i % (entry/2)==index){
                    if(flag==0){
                        Bucket *newbucket = new Bucket();
                        newbucket->localdepth = globaldepth+1;
                        barr1.push_back(newbucket);
                        flag = 1;
                    }
                    else{
                        this->barr[i % (entry/2)]->localdepth++;
                        barr1.push_back(this->barr[i % (entry/2)]);

                    }
                    
                }
                else{
                    barr1.push_back(this->barr[i % (entry/2)]);
                }
            }

            globaldepth++;
            this->barr = barr1;
            //barr.clear();
            x = pow(2,globaldepth);
            int z = index + entry/2;
            index = data % x;
             //The element in the overflowing bucket which is split are rehashed.
            int swapi=0;
            while(swapi<=barr[z]->curr-1){
                int index1 = (barr[z]->arr[swapi]) % x;
                if(index1!=z){
                    barr[index1]->arr[barr[index1]->curr++] = barr[z]->arr[swapi];
                    for(int j=swapi+1;j<=barr[z]->curr-1;j++){
                        barr[z]->arr[j-1] = barr[z]->arr[j];
                    }
                    
                    barr[z]->curr--;
                    barr[z]->arr[barr[z]->curr] = 0;
                    //swapi++;
                }
                else{
                    swapi++;
                }
            }
            if(barr[index]->curr == 3) insertElement(data);
            else barr[index]->arr[barr[index]->curr++] = data;
        }
        else{//Perform Bucket Split
            Bucket *newBucket = new Bucket();
            newBucket->localdepth++;
            barr[index]->localdepth++;
            if(index<=x/2-1){
                barr[index+x/2] = newBucket;
            }
            else{
                barr[index-x/2] = newBucket;
            }
            
            //The element in the overflowing bucket which is split are rehashed.
            int swapi=0;
            while(swapi<=barr[index]->curr-1){
                int index1 = (barr[index]->arr[swapi]) % x;
                if(index1!=index){
                    barr[index1]->arr[barr[index1]->curr++] = barr[index]->arr[swapi];
                    for(int j=swapi+1;j<=barr[index]->curr-1;j++){
                        barr[index]->arr[j-1] = barr[index]->arr[j];
                    }
                    barr[index]->curr--;
                    barr[index]->arr[barr[index]->curr] = 0;
                }
                else{
                    swapi++;
                }
            }
            if(barr[index]->curr == 3) insertElement(data);
            else barr[index]->arr[barr[index]->curr++] = data;
        }
    }

}

int main(){
    Directory dt;
    //cout<<dt.barr[0]->size<<endl;
    int option,element;
    
    while(1){
        cout<<"Enter 1 to insert :\n";
        cout<<"Enter 2 to search an element :\n";
        cout<<"Enter 3 to to start again :\n";
        cin>>option;
        switch(option){
            case 1:
                cin>>element;
                dt.insertElement(element);
                cout<<dt.globaldepth<<endl;
                break;
            case 2:
                cin>>element;
                dt.search(element);
            case 3:
                break;
            default :
                break;
        }
        if(option == 3) break;
    }
    

}

