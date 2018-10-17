/*
    Priyendu Mori
    2018201103
    Q5 - StringBuilder
*/
#include <bits/stdc++.h>
#define ll long long

using namespace std;

//linked list node
struct llnode{
    const char* str;
    struct llnode* next;
};

/*
    class containing methods and variables for stringBuilder
*/
class stringBuilder{
    public:

    //points to first node of the linked list of this string
    struct llnode* start;
    //indicates total size of the string including all the nodes
    ll size_of_string;

    //empty constructor that initializes start and size_of_string to NULL and 0
    stringBuilder(){
        start=NULL;
        size_of_string=0;
    }

    //constructor that initializes start and size_of_string
    stringBuilder(const char* s){
        start=new struct llnode;
        start->str=s;
        start->next=NULL;

        size_of_string=strlen(s);
    }

};

/*
    create new stringBuilder object
    copy nodes of s1 and then nodes of s2
    ans then point new objects start to the start of new object
*/
stringBuilder stringAppend(stringBuilder s1, stringBuilder s2){
    stringBuilder s3=stringBuilder();
    struct llnode* temp=NULL;
    struct llnode* prev=NULL;
    bool s1null=true;
    if(s1.start!=NULL){
        s1null=false;
        s3.start=new struct llnode;
        s3.start->str=s1.start->str;
        temp=s1.start->next;
        prev=s3.start;
        while(temp){
            prev->next=new struct llnode;
            prev->next->str=temp->str;
            temp=temp->next;
            prev=prev->next;
        }
    }
    if(s2.start!=NULL){
        if(s1null){
            s3.start=new struct llnode;
            s3.start->str=s2.start->str;
            temp=s2.start->next;
            prev=s3.start;
        }      
        else    temp=s2.start;
    }
    while(temp){
        prev->next=new struct llnode;
        prev->next->str=temp->str;
        temp=temp->next;
        prev=prev->next;
    }
    // if(prev!=NULL)  prev->next=NULL;
    s3.size_of_string=s1.size_of_string+s2.size_of_string;
    return s3;
}

/*
    printing string
*/
void print(stringBuilder s){
    struct llnode* temp=s.start;
    while(temp){
        cout<<temp->str<<" - ";
        temp=temp->next;
    }
    cout<<endl;
}

//method to initialize string
stringBuilder stringInitialize(const char* s){
    return stringBuilder(s);
}

/*
    helper function that travels all nodes and merges them into 
    one for faster processing next time
*/
stringBuilder mergeNodes(stringBuilder s){
    struct llnode* list=s.start;
    struct llnode* prev=NULL;
    char* merged=new char[s.size_of_string];

    if(list!=NULL){
        strcpy(merged,list->str);
        list=list->next;
    }
    while(list){
        strcat(merged,list->str);
        prev=list;
        list=list->next;
        free(prev);
    }

    // const char* m=merged;
    s.start->str=merged;
    s.start->next=NULL;
    // cout<<"here "<<s.start->str<<endl;
    return s;

}

/*
    return index of first match of input in source string
*/
ll kmp(const char* source,const char* input){

    ll tl=strlen(source),pl=strlen(input);

    //constructing c array
    vector<ll> c(pl,0);
	ll k=0;
	for(ll i=1;i<pl;i++){
		while(k>0 && input[k] != input[i] ){
			k=c[k-1];
		}
		if( input[k] == input[i] ){
			k=k+1;
		}
		c[i]=k;
	}

    // for(auto i:c)   cout<<i<<" ";
    // cout<<endl;

    //match input string to source
    //return index if found, else -1
    ll matched_pos=0;
	for(ll current=0; current< tl; current++){
		while (matched_pos > 0 && input[matched_pos] != source[current] ){
			matched_pos = c[matched_pos-1];
        }
			
		if(input[matched_pos] == source[current])   matched_pos = matched_pos+1;
			
		if( matched_pos == pl ){
            return current - (pl -1 );
			matched_pos = c[matched_pos-1];
		}
	}
    return -1;
}

/*
    travel all nodes, merge them into one
    make a string
    call kmp with that string as source
*/
ll findSubstring(stringBuilder s, const char* input){
    s=mergeNodes(s);
    return kmp(s.start->str,input); 
}

int main(){
    ios_base::sync_with_stdio(false);

    stringBuilder s1=stringInitialize("hello");
    print(s1);
    stringBuilder s2=stringInitialize("world");
    print(s2);

    stringBuilder s4=stringInitialize(" hi there ");
    print(s4);

    stringBuilder s3=stringAppend(s1,s2);
    s3=stringAppend(s3,s4);
    print(s3);

    s3=mergeNodes(s3);
    print(s3);

    stringBuilder s5,s6;

    s1=stringAppend(s5,s6);
    cout<<"new s1 ";
    print(s1);
    cout<<"new s3 ";
    print(s3);
    cout<<endl;cout<<endl;

    stringBuilder s100=stringInitialize("hello world abababcmn");
    cout<<s100.start->str<<endl;
    cout<<findSubstring(s100,"abababc")<<endl;

    return 0;
}