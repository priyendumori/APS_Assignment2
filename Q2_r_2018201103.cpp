#include <bits/stdc++.h>
#define ll long long
using namespace std;

#define MAXKEYS 2
#define MINKEYS MAXKEYS/2

/*
    btree node
    node_count maintains the number of elements present in node
    key array contains elements in node
    pointer contains child pointers
    pointer[0] is left pointer of key[1]
    pointer[1] is right pointer of key[1] and left pointer of key[2] and so on...
*/
struct btNode {
    ll key[MAXKEYS + 1];
    ll node_count;
    struct btNode *pointer[MAXKEYS + 1];
};

struct btNode* root;

void insert(ll key, struct btNode* node){
    if(node==NULL){
        node->key=key;
        node->pointer[0]=NULL;
    }
}

int main(){
    ios_base::sync_with_stdio(false);

    ll key;
    cout<<"enter key"<<endl;
    cin>>key;

    insert(key,root);

    return 0;
}