#include <bits/stdc++.h>
#define ll long long
using namespace std;

#define MAXKEYS 2
#define MINKEYS MAXKEYS/2

/*
    btree node
    node_count maintains the number of elements present in node
    key array contains elements in node
    link contains child pointers
    link[0] is left pointer of key[1]
    link[1] is right pointer of key[1] and left pointer of key[2] and so on...
*/
struct btNode {
    ll key[MAXKEYS + 1];
    ll node_count;
    struct btNode *link[MAXKEYS + 1];
};

// root of the btree
struct btNode *root;

/*
    adds the key to the node at appropriate place 
*/
void add_key_to_node(ll key, ll place, struct btNode *node, struct btNode *child) {
    //index starts from last node and 
    //decrements to find the position where key should be inserted
    ll index=node->node_count;
    while (index>place) {
        //decrement index and move elements in node to right to 
        //make place for key at its position
        node->link[index + 1]=node->link[index];
        node->key[index + 1]=node->key[index];
        index--;
    }
    //now index+1 points to corrent position of key
    //so assign key to this place and make its right pointer to point to child
    //and increment node_count as 1 element is added to the node
    node->link[index + 1]=child;
    node->key[index + 1]=key;
    node->node_count++;
}

/*
    split node when insertion causes overflow in the node 
*/
void split_node(ll key, ll *p_val, ll place, struct btNode *node, struct btNode *child, struct btNode **new_node){
    ll middle;
    ll index;

    //middle determines which elements goes to which node
    //elements to the left of middle including middle goes 
    //to one node called "node" which is passed
    //elements from middle+1 to end goes to new_node

    middle=MINKEYS;
    if (place>MINKEYS)  middle++;

    //create new node which contains elements from middle+1 to end
    *new_node = (struct btNode *)malloc(sizeof(struct btNode));
    index=middle+1;
    while (index<=MAXKEYS) {
        //copy key and link from middle+1 to end from node to new_node
        (*new_node)->link[index-middle] = node->link[index];
        (*new_node)->key[index-middle] = node->key[index];
        index++;
    }
    //changing count of node to middle means deleting elements from middle+1 to end
    //which means now node contains elements from 1 to middle
    node->node_count=middle;
    (*new_node)->node_count=MAXKEYS-middle;

    //if place found is less than MINKEYS add element to node (left split)
    //else add element to new_node (right split)
    if (place<=MINKEYS) add_key_to_node(key, place, node, child);
    else    add_key_to_node(key, place-middle, *new_node, child);
    
    //store last element of node(left split) to p_val to make it root of both the splits
    *p_val=node->key[node->node_count];
    //assign right pointer of last element to left pointer 
    //of first element of new_node (right split)
    (*new_node)->link[0]=node->link[node->node_count];
    //decrementing node_count as last element of node is now sent to root node
    node->node_count--;
}

/*
    set key to be inserted in a node
    returns true if there's a need to create a new node
    returns false if key can be accommodated in a node and there's no need to create a new node
*/
bool set_key_in_node(ll key, ll *p_val, struct btNode *node, struct btNode **child){
    //recursively find the node where this key should be entered and 
    //find the place where it should be added using for loop
    
    ll place;
    //if found that new node is to be created
    //assign key to p_val (which holds parent node key) and make it's child NULL
    //and return true so calling function knows that new node is to be created
    if(!node){
        *child=NULL;
        *p_val=key;
        return true;
    }

    //if key is less than first element in node then its left child is to be searched
    //else check other elements of the same node
    if (key< node->key[1]){
        place=0;
    }else{
        //find place where elements to the right are greater than key
        for(place=node->node_count; (key< node->key[place] && place>1); place--);
        
        //if element at place is key itself than we cannot enter element to tree so return
        if (key==node->key[place]){
            cout<<"Cannot enter duplicate values...!"<<endl;
            return false;
        }
    }

    //now calling the function recursively to find the node and place 
    //at which the element is to be inserted
    if (set_key_in_node(key, p_val, node->link[place], child)){
        //if node is not overflowed, add key to node
        if (node->node_count<MAXKEYS) {
            add_key_to_node(*p_val, place, node, *child);
        } else {
            //if adding key overflows, then split node and return true to create new node
            split_node(*p_val, p_val, place, node, *child, child);
            return true;
        }
    }
    return false;
}

/* 
    creating new node 
*/
struct btNode * create_node(ll key, struct btNode *right) {
    //create new node
    //add key
    //root is the left child of the node
    //right is the right child of the node
    //make node_count 1
    struct btNode *new_btNode;
    new_btNode=(struct btNode *)malloc(sizeof(struct btNode));
    new_btNode->key[1]=key;
    new_btNode->node_count=1;
    new_btNode->link[1]=right;
    new_btNode->link[0]=root;
    return new_btNode;
}

/*
    driver function for inserting key to node
*/
void insert_key(ll val) {
    ll i;
    bool create_new=false;
    struct btNode *child;

    //add key and if it returns true (meaning this node leads to splitting of some node)
    //then create a new node
    //current root is left of the new root
    //new node created is the right child of the new root
    create_new=set_key_in_node(val, &i, root, &child);

    if (create_new) root=create_node(i, child);
}

void search_key(struct btNode *node, int key){
    if(!node){
        cout<<key<<" is not present in the tree"<<endl;
        return ;
    }

    ll place;

    if (key<node->key[1]){
        place=0;
    }else{
        for(place=node->node_count; (key< node->key[place] && place>1); place--);
        
        if (key==node->key[place]){
            cout<<key<<" is present in the tree"<<endl;
            return;
        }
    }

    search_key(node->link[place],key);
}

int main() {
    int val, ch;
    while (1) {
        printf("1. Insertion\t2. Deletion\n");
        printf("3. Searching\t4. Traversal\n");
        printf("5. Exit\nEnter your choice:");
        scanf("%d", &ch);
        switch (ch) {
            case 1:
                printf("Enter your input:");
                scanf("%d", &val);
                insert_key(val);
                break;
            case 2:
                printf("Enter the element to delete:");
                scanf("%d", &val);
                // deletion(val, root);
                break;
            case 3:
                printf("Enter the element to search:");
                scanf("%d", &val);
                search_key(root,val);
                break;
            case 4:
                // traversal(root);
                break;
            case 5:
                exit(0);
            default:
                printf("U have entered wrong option!!\n");
                break;
        }
        printf("\n");
    }
}