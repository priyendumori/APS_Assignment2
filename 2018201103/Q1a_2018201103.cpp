/*
    Priyendu Mori
    2018201103
    Q1_a suffix array - minimum lexicographic rotation
*/
#include<bits/stdc++.h>
#define ll long long

using namespace std;

/*
    comparator to sort vector of pair<index, pair<rank,new rank>>
    according to rank and then according to next rank
*/
bool comp(pair<int,pair<int,int>> a, pair<int,pair<int,int>> b){
    if(a.second.first == b.second.first){
        if(a.second.second < b.second.second)   return true;
        else return false;
    }
    else{
        if(a.second.first < b.second.first) return true;
        else return false;
    }
}

/*
    function to build suffix array and return it
*/
vector<ll> buildSuffix(string str){
    //vector of {index,{rank,new rank}}
    vector<pair<int,pair<int,int>>> suffix(str.size());
    //index vector helps in finding the sorted index of next part of the string 
    //e.g abbc: there's bc after ab, so we need sorted index of ab which is found from index vector
    vector<ll> index(str.size());

    //considering one char of string
    //assign it's ascii value as it's current rank
    //assign next char's ascii value as it's next rank
    //if next char is not present, next rank should be -1
    for(ll i=0;i<str.size();i++){
        ll rank0=str[i]-'0';
        ll rank1;
        if((i+1)<str.size())   rank1=str[i+1]-'0';
        else rank1=-1;
        suffix[i]={i,{rank0,rank1}};
    }

    //sort the array according to comparator defined previously
    sort(suffix.begin(), suffix.end(), comp);

    //doing the same thing for next 2 chars than next 4 chars and so on
    for(ll p=4;p<2*str.size();p*=2){
        //assigning index and rank tothe first suffix
        ll rank=0;
        ll previous_rank=suffix[0].second.first;
        suffix[0].second.first=rank;
        index[suffix[0].first]=0;

        //iterating to assign ranks and new ranks to all the other suffixes
        for(ll i=1;i<str.size();i++){
            //if the previous {rank,new rank} pair is same as this {rank,new rank} pair
            //assign the same rank as previous
            //else increment the rank and assign that rank to this suffix
            if(suffix[i].second.first==previous_rank && suffix[i].second.second==suffix[i-1].second.second){
                previous_rank=suffix[i].second.first;
                suffix[i].second.first=rank;
            }
            else{
                rank++;
                previous_rank=suffix[i].second.first;
                suffix[i].second.first=rank;
            }
            index[suffix[i].first]=i;
        }

        //assign new rank to every suffix
        for(ll i=0;i<str.size();i++){
            //find the index where next suffix is residing
            //if next is within range assign rank of that suffix to this suffixes new rank
            //else assign -1 as new rank
            ll next=suffix[i].first + p/2;
            ll new_rank;
            if(next<str.size()){
                new_rank=suffix[index[next]].second.first;
            }
            else{
                new_rank=-1;
            }
            suffix[i].second.second=new_rank;
        }
        //sort suffixes according to comparator
        sort(suffix.begin(), suffix.end(), comp);
    }

    //construct the suffix array by copying index from vector of {index,{rank,new rank}}
    vector<ll> suffix_vector(str.size());
    for(ll i=0;i<str.size();i++){
        suffix_vector[i]=suffix[i].first;
    }
    
    return suffix_vector;
}

int main(){
    ios_base::sync_with_stdio(false);
    
    string str;
    cout<<"Enter String "<<endl;
    cin>>str;

    string str2=str+str;
    vector<ll> ans=buildSuffix(str2);

    ll start=0;
    for(ll i=0;i<str2.size();i++){
        if(ans[i]<str.size()){
            start=ans[i];
            break;
        }
    }

    cout<<"Minimum lexicographic rotated string is: "<<endl;
    cout<<str2.substr(start,str.size())<<endl;

    return 0;
}