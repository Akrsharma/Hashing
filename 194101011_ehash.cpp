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
    Bucket(int size,int globaldepth){
        curr=0;
        this->size = size;
        localdepth = globaldepth;
        arr = new int[size];
        memset(arr, 0, size*sizeof(arr[0]));
    }

};

class Directory{
    public:
    int globaldepth;
    set<Bucket*> uniqueBucket;
    vector<Bucket*> barr;
    void insertElement(int,int);
    bool search(int);
    void deleteElement(int, int);
    void insertElement1(int,int);
    Directory(int globaldepth,int size){
        this->globaldepth = globaldepth;
        int x = pow(2,globaldepth);
        for(int i=0; i<x; i++){
            Bucket *newBucket = new Bucket(size,globaldepth);
            barr.push_back(newBucket);
            uniqueBucket.insert(newBucket);
        }
        
    }

};
bool Directory :: search(int data){
    int x = (pow(2,globaldepth));
    int index = data % x;
    int i=0,flag=0;
    while(i<=barr[index]->curr-1){
        if(data == barr[index]->arr[i])
        {
            return true;
            flag=1;
        }
        i++;
    }
    if(!flag) return false;
    

}
void Directory :: insertElement1(int data,int size){
    bool bl = search(data);
    if(bl){
        //cout<<"Element is already present"<<endl;
    } 
    else insertElement(data,size);
}
void  Directory :: insertElement(int data,int size){
    int x = (pow(2,globaldepth));
    int index = data % x;
    //cout<<index<<endl;
    //cout<<barr[index]->curr;
    if(barr[index]->curr < size){
        barr[index]->arr[barr[index]->curr++] = data;
    }
    else{
        if(barr[index]->localdepth == globaldepth){ //Directory Expansion and Perform Bucket Split
            //Expanding the directory
            vector<Bucket*> barr1;
            long entry = pow(2,globaldepth+1);
            int flag = 0,flag1=0;
            for(int i=0; i<entry; i++){
                if(i % (entry/2)==index){
                    if(flag==0){
                        Bucket *newbucket = new Bucket(size,globaldepth);
                        newbucket->localdepth = globaldepth+1;
                        barr1.push_back(newbucket);
                        uniqueBucket.insert(newbucket);
                        flag = 1;
                    }
                    else{
                        this->barr[i % (entry/2)]->localdepth++;
                        barr1.push_back(this->barr[i % (entry/2)]);

                    }
                    
                }
                else{
                    double occupancy= ((double)(barr[index]->curr))/((double)size);
                    //cout<<"occupancy"<<occupancy<<endl;
                    if(occupancy > 0.7){
                        if(flag1==0){
                            Bucket *newbucket = new Bucket(size,globaldepth);
                            uniqueBucket.insert(newbucket);
                            newbucket->localdepth = globaldepth+1;
                            barr1.push_back(newbucket);
                            flag1=1;
                        }
                        else{
                            this->barr[i % (entry/2)]->localdepth++;
                            barr1.push_back(this->barr[i % (entry/2)]);
                            flag1==0;
                        }
                    }
                    else
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
            if(barr[index]->curr == size) insertElement(data,size);
            else barr[index]->arr[barr[index]->curr++] = data;
        }
        else{//Perform Bucket Split
            Bucket *newBucket = new Bucket(size,globaldepth);
            uniqueBucket.insert(newBucket);
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
            if(barr[index]->curr == size) insertElement(data,size);
            else barr[index]->arr[barr[index]->curr++] = data;
        }
    }

}

void Directory :: deleteElement(int data, int size){
    bool bl = search(data);
    if(!bl){
        //cout<<"Element is not present in the hash table"<<endl;
    }
    else{
        int x = (pow(2,globaldepth));
        int index = data % x;
        int flag=0,i;
        for(i=0; i<barr[index]->curr-1;i++){
            if(data == barr[index]->arr[i]){
                flag=1;
            }
            if(flag ==1 ){
                barr[index]->arr[i]=barr[index]->arr[i+1];
            }
        }
        barr[index]->arr[i]=0;
        barr[index]->curr--;
        double occupancy = ((double)(barr[index]->curr))/((double)(size));
        if(occupancy <= 0.25){
            int mirrorindex = (index + 4) % x;
            if(barr[mirrorindex]!=barr[index]){
                double mirroroccupancy  =((double)(barr[mirrorindex]->curr))/((double)(size));
                if(mirroroccupancy <= 0.25){
                    for(int i=0; i<=barr[mirrorindex]->curr-1; i++){
                        barr[index]->curr++;
                        barr[index]->arr[barr[index]->curr] = barr[mirrorindex]->arr[i];
                    }
                    uniqueBucket.erase(barr[mirrorindex]);
                    barr[mirrorindex] = barr[index];
                    barr[index]->localdepth--;
                }
            }
        }

    }

}

int main(){
    int option,globaldepth,size,choice,data;
    cin>>option;
    cin>>globaldepth;
    cin>>size;
    int changd = globaldepth,changeBuck = pow(2,globaldepth);
    Directory dt(globaldepth,size);
    cout<<dt.globaldepth<<" "<<dt.uniqueBucket.size()<<endl;
    while(cin>>choice){
        switch(choice){
            case 2:
                cin>>data;
                dt.insertElement1(data,size);
                if(dt.globaldepth != changd || changeBuck != dt.uniqueBucket.size()){
                    cout<<dt.globaldepth<<" "<<dt.uniqueBucket.size()<<endl;
                    changd = dt.globaldepth;
                    changeBuck = dt.uniqueBucket.size();
                }
                break;
            case 3:
                cin>>data;
                dt.deleteElement(data,size);
                if(dt.globaldepth != changd || changeBuck != dt.uniqueBucket.size()){
                    cout<<dt.globaldepth<<" "<<dt.uniqueBucket.size()<<endl;
                    changd = dt.globaldepth;
                    changeBuck = dt.uniqueBucket.size();
                }
                break;
            default :
                break;
        }

    }
    
    return 0;
}

