#include<bits/stdc++.h>
using namespace std;

class Node {
    public:
    int key, val, cnt;
    Node *next; 
    Node *prev;
    Node(int a, int b) {
        key = a;
        val = b; 
        cnt = 1; 
    }
}; 
class NodeList {
    public:
    int size; 
    Node *h; 
    Node *t; 
    NodeList() {
        h = new Node(0,0); 
        t = new Node(0,0); 
        h->next = t;
        t->prev = h; 
        size = 0;
    }
    void front(Node *node) {
        Node* temp = h->next;
        node->next = temp;
        node->prev = h;
        h->next = node;
        temp->prev = node;
        size++; 
    }
    void remove(Node* node) {
        Node* q = node->prev;
        Node* x = node->next;
        q->next = x;
        x->prev = q;
        size--; 
    }
    
};


    unordered_map<int, Node*> hm1; 
    unordered_map<int, NodeList*> hm2; 
    int maxs;
    int minf; 
    int p; 

    void LFUCache(int capacity) {
        maxs = capacity; 
        minf = 0;
        p = 0; 
    }
    void helper(Node *node) {
        hm1.erase(node->key); 
        hm2[node->cnt]->remove(node); 
        if(node->cnt == minf && hm2[node->cnt]->size == 0) {
            minf++; 
        }
        
        NodeList* x = new NodeList();
        if(hm2.find(node->cnt + 1) != hm2.end()) {
            x = hm2[node->cnt + 1];
        } 
        node->cnt += 1; 
        x->front(node); 
        hm2[node->cnt] = x; 
        hm1[node->key] = node;
    }
    
    int get(int key) {
        if(hm1.find(key) != hm1.end()) {
            Node* node = hm1[key]; 
            int val = node->val; 
            helper(node); 
            return val; 
        }
        return -1; 
    }
    
    void put(int key, int val) {
        if (maxs == 0) {
            return;
        }
        if(hm1.find(key) != hm1.end()) {
            Node* node = hm1[key]; 
            node->val = val; 
            helper(node); 
        }
        else {
            if(p == maxs) {
                NodeList* list = hm2[minf]; 
                hm1.erase(list->t->prev->key); 
                hm2[minf]->remove(list->t->prev);
                p--; 
            }
            p++; 
            minf = 1; 
            NodeList* t = new NodeList(); 
            if(hm2.find(minf) != hm2.end()) {
                t = hm2[minf]; 
            }
            Node* node = new Node(key, val); 
            t->front(node);
            hm1[key] = node; 
            hm2[minf] = t; 
        }
    }
int main(){
int y;
cin>>y;
LFUCache(y);
//n is the number of inputs to the problem
int n;
cin>>n;
for(int i=0;i<n;i++){
    string s;
    cin>>s;
    if(s=="get"){
        int a;
        cin>>a;
        cout<<get(a)<<"\n";
    }
    if(s=="put"){
    int a,b;
    cin>>a>>b;
    put(a,b);
    }    
}
}