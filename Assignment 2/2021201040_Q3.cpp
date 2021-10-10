
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <typename K>
class deque{
    
public:
    int max_size,size=0,front,rear;
    K *arr;
    deque(){
        max_size=0;
        size=0;
        front=-1;
        rear=0;
    }
    deque(int size,K key){
        //int arr[size];
        arr=(K*)malloc(size*sizeof(K));
        for(int i=0;i<size;i++){
            arr[i]=key;
        }
        front=-1;
        rear=0;
        max_size=size;
    }
     K operator [](int n){
        if(n<size)
            return arr[(front+n)%max_size];
        return arr[n];
    }
    bool empty()
    {
    return (front == -1);
    }
    
    bool isFull()
    {
    return size==max_size;
    }
    void push_back(K key)
    {
    if (isFull())
    {
        return;
    }
        
    if (front == -1)
    {
        front = 0;
        rear = 0;
    }
    else if (rear == max_size-1)
        rear = 0;
    else
        rear = rear+1;
    arr[rear] = key ;
    size++;
    }
    void pop_back()
    {
    if (empty())
    {
        return ;
    }
    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else if (rear == 0)
        rear = max_size-1;
    else
        rear = rear-1;
    size--;
    }
    void push_front(K key)
    {
    if (isFull())
    {
        return;
    }
    if (front == -1)
    {
        front = 0;
        rear = 0;
    }
    else if (front == 0)
        front = max_size - 1 ;
    else
        front = front-1;
    arr[front] = key ;
    size++;
    }
    void pop_front()
    {
    if (empty())
    {
        return ;
    }
    if (front == rear)
    {
        front = -1;
        rear = -1;
    }
    else{
        if (front == max_size -1)
            front = 0;
        else 
            front = front+1;
    }
        size--;
    }
    K frontv(){
        if(empty()){
            return -1;
        }
        return arr[front];
    }
    K rearv(){
        if(empty()){
            return -1;
        }
        return arr[rear];
    }
    int sizev(){
        return size;
    }
    void clear(){
        free(arr);
        deque<K>();
    }
    void resize(int n,K key){
        K* temp=(K*)malloc(n*sizeof(K));
        max_size=n;
        int p=size;
        for(int i=0;i<n;i++)
            temp[i]=key;
        for(int i=0;i<p;i++)
        {
            temp[i]=frontv();
            pop_front();
        }
        size=p;
        free(arr);
        arr=temp;
        front=0;
        rear=size-1;
            
    }
    
};


int main() {
    
    
    //cout<<"hello";
    deque<int> dq(4,8);
    cout<<dq.front<<" "<<dq.rear<<"\n";
    dq.push_back(1);
    cout<<dq.front<<" "<<dq.rear<<"\n";
    dq.push_back(2);
    cout<<dq.front<<" "<<dq.rear<<"\n";
    cout<<dq[0]<<" "<<dq[1]<<" "<<dq[2]<<" "<<dq[3]<<"\n";
    //cout<<dq.sizev();
    dq.push_front(3);
    cout<<dq.front<<" "<<dq.rear<<"\n";
    dq.push_front(4);
    cout<<dq.front<<" "<<dq.rear<<"\n";
    cout<<dq[0]<<" "<<dq[1]<<" "<<dq[2]<<" "<<dq[3]<<"\n";
    dq.pop_back();
    cout<<dq.frontv()<<" "<<dq.rearv()<<"\n";
    dq.pop_front();
    cout<<dq.frontv()<<" "<<dq.rearv()<<"\n";
    dq.pop_back();
    cout<<dq.frontv()<<" "<<dq.rearv()<<"\n";
    dq.pop_back();
    cout<<dq.frontv()<<" "<<dq.rearv()<<"\n";
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    return 0;
}
