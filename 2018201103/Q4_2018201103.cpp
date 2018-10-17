/*
    Priyendu Mori
    2018201103
    Q4 - Unordered_map
*/

#include<bits/stdc++.h>
#define ll long long
#define BUCKETS 100
#define prime 31

using namespace std;

/*
    class of Unordered map that accepts two generic data type T as key and U as value
    class contains methods and variables of Unordered map
*/
template <typename T, typename U>
class Unordered_map{
    public:

    //node of the linked list 
    class llnode{
        public:
        T key_element;
        U value;
        llnode* next;
    }; 

    //array of buckets containing pointers to linked list holding 
    //{key,value} pairs for this bucket
    llnode* table[BUCKETS];

    //constructor that initializes all the bucket pointer to NULL
    Unordered_map(){
        for(ll i=0;i<BUCKETS;i++){
            table[i]=NULL;
        }
    }

    /*
        function takes key as argument and returns index of hash table 
        into which this {key,value} pair should go  
    */
    ll hash(T k){
        //converts any type of object to string to calculate it's hash
        ostringstream os;
        os << k;
        string key=os.str();

        //calculate hash 
        //eg: abcd --> (ascii of a)*((prime)^0) + (ascii of b)*((prime)^1) + 
        //              (ascii of b)*((prime)^2) + (ascii of d)*((prime)^3)
        ll result = key[0];
        for (int i=1; i<key.size(); i++){ 
            result = ((result*prime)%BUCKETS + key[i])%BUCKETS; 
        }
        return result%BUCKETS;
    }

    /*
        inserts {key,value} to appropriate linked list
    */
    bool insert(T key, U value){
        ll index=hash(key);
        // cout<<index<<endl;
        if(table[index]!=NULL){
            llnode* temp=table[index];
            while(temp){
                if(temp->key_element!=key){
                    temp=temp->next;
                }
                else{
                    return false;
                }
            }
        }
        llnode* new_node = new llnode();
        new_node->key_element=key;
        new_node->value=value;
        llnode* p=table[index];
        new_node->next=p;
        table[index]=new_node;
        return true;
    }

    /*
        returns pair {value,true} if key is present
        returns pair {NULL,false} if key is absent
    */
    pair<U,bool> search(T key){
        ll index=hash(key);
        llnode* temp=table[index];
        while(temp){
            if(temp->key_element!=key){
                temp=temp->next;
            }
            else break;
        }
        if(temp==NULL)  return {NULL,false};
        return {temp->value,true};
    }

    /*
        deletes {key,value} node from the appropriate linked list if present
    */
    void delete_key(T key){
        ll index=hash(key);

        llnode* temp=table[index];
        llnode* prev=NULL;

        if(temp!=NULL && temp->key_element==key){
            table[index]=temp->next;
            free(temp);
            return;
        }

        while(temp!=NULL && temp->key_element!=key){
            prev=temp;
            temp=temp->next;
        }

        if(temp==NULL)  return;

        prev->next=temp->next;
        free(temp);
        return;

    }

    /*
        printing hash table
    */
    void printTable(){
        for(ll i=0;i<BUCKETS;i++){
            if(table[i]!=NULL){
                ll count=0;
                llnode* t=table[i];
                cout<<i<<" -----> ";
                while(t){
                    count++;
                    cout<< "( "<< t->key_element << ", "<< t->value << ", " << t->next << ")" <<"-> ";
                    t=t->next;
                }
                cout<<endl;
                // cout<<count<<endl;
            }
        }
    }

};

int main(){
    ios_base::sync_with_stdio(false);

    Unordered_map<string,int> m1;
    Unordered_map<string,string> m2;
    Unordered_map<int,int> m3;
    Unordered_map<int,string> m4;

    // m1.insert("priyendu",545);
    // m1.insert("jasani",554);
    // m1.insert("dhawal",422);
    // m1.insert("darshan",546);
    // m1.insert("vatsal",456);

    // m3.insert(522,545);
    // m3.insert(542,554);
    // m3.insert(892,422);
    // m3.insert(43233,546);
    // m3.insert(65422,456);
    // m3.insert(55422,545);
    // m3.insert(546464652,554);
    // m3.insert(895465452,422);
    // m3.insert(43235453,546);
    // m3.insert(6546557995452222222,456);
    // ll a,b,c,l=50000;
    // while(l--){
    //     cin>>a>>b>>c;
    //     m3.insert(b,c);
    // }
    // m3.printTable();
    while(1){
        ll t;
        cout<<"enter choice"<<endl;
        cin>>t;
        if(t==1){
            string key;
            ll value;
            cout<<"enter key"<<endl;
            cin>>key;
            cout<<"enter value"<<endl;
            cin>>value;
            m1.insert(key,value);
        }
        else if(t==2){
            string key;
            cout<<"enter key"<<endl;
            cin>>key;
            if(m1.search(key).second==true){
                cout<<m1.search(key).first<<endl;
            }
            else{
                cout<<"not found"<<endl;
            }
        }
        else if(t==3){
            string key;
            cout<<"enter key"<<endl;
            cin>>key;
            m1.delete_key(key);
        }
        else if(t==4){
            cout<<"print "<<endl;
            m1.printTable();
        }
        else{
            cout<<"wrong choice"<<endl;
        }
    }

    return 0;
}
