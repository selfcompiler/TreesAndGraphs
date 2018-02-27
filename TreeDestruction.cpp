//
// Created by Rahul Singh on 26/02/18.
//

 //#include</Users/selfcompiler/gitwork/clionProject/Practise/cmake-build-debug/stdc++.h>
 #include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long  ull;
#define inf  (0x7f7f7f7f) //>2e9
#define linf  (1LL<<62)//>4e18
#define  SZ 200006
#define ENABLELOG false
int nodes;
vector<int> graph[SZ];
set<int> leafSet;
int dist[SZ][2]={0};
int dig[SZ]={0};
bool visited[SZ]={false};
vector<int> path_from_a_to_b;
void constructGraph(){
    cin>>nodes;
    int x,y;
    for(int i=1;i<nodes;i++){
        cin>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
        dig[x]++;
        dig[y]++;
    }
    return;
}



void farthestNode(int parent,int distance,int& distantNode,int& distantNodesDistance){
    for(int i=0;i<graph[parent].size();i++){
        int child=graph[parent][i];
        if(!visited[child]){
            if(distantNodesDistance<(distance+1)){
                distantNode=child;
                distantNodesDistance=distance+1;
            }
            visited[child]=true;
            farthestNode(child,distance+1,distantNode,distantNodesDistance);
        }
    }
}

void setVisited(){
    for(int i=1;i<=SZ;i++){
        visited[i]=false;
    }
}

bool dfsA2B(int A,int B){
    if(A==B)
        return true;
    for(int i=0;i<graph[A].size();i++){
        int child=graph[A][i];
        if(!visited[child]){
            visited[child]=true;
            if(dfsA2B(child,B)){
                path_from_a_to_b.push_back(child);
                return true;
            }
        }
    }
    return false;
}

pair<int,int> getDiameter(){
    int a,b,d1,d2;
    d1=0,d2=0;
    a=1;
    setVisited();
    visited[1]=true;
    farthestNode(1,0,a,d1);
    setVisited();
    visited[a]=true;
    b=a;
    farthestNode(a,0,b,d2);
    if(ENABLELOG){
        cout<<"Diameter "<<a<<" "<<b<<" \n";
    }
    return std::make_pair(a,b);
};

void dfs(int parent,int option){
    for(int i=0;i<graph[parent].size();i++){
        int child=graph[parent][i];
        if(dist[child][option]<0) {
            dist[child][option] = dist[parent][option] + 1;
            dfs(child,option);
        }
    }
    return;
}

void initializeLeafSet(){
    for(int i=1;i<=nodes;i++){
        if(dig[i]==1){
            leafSet.insert(i);
        }
    }
}

void computeDistanceFromLeaftoAllOtherNodes(int leafNode,int option){
    for(int i=1;i<=nodes;i++)
        dist[i][option]=-1;
    dist[leafNode][option]=0;
    dfs(leafNode,option);
}

int main(){
    constructGraph();
    initializeLeafSet();
    pair<int,int> dia=getDiameter();
    leafSet.erase(dia.first);
    leafSet.erase(dia.second);
    computeDistanceFromLeaftoAllOtherNodes(dia.first,0);
    computeDistanceFromLeaftoAllOtherNodes(dia.second,1);
    setVisited();
    visited[dia.first]=true;
    if(dfsA2B(dia.first,dia.second)){
        path_from_a_to_b.push_back(dia.first);
    }
    setVisited();
    if(ENABLELOG){
        cout<<"Diameter path\n";
    }
    for(int i=0;i<path_from_a_to_b.size();i++){
        if(ENABLELOG)
            cout<<" "<<path_from_a_to_b[i]<<" ";
        visited[path_from_a_to_b[i]]=true;
    }
    if(ENABLELOG){
        cout<<"\n";
    }
    if(ENABLELOG){
        cout<<"Distance from Diameter Nodes = "<<dia.first<<" \n";

        for(int i=1;i<=nodes;i++){
            cout<<dist[i][0]<<" ";
        }
        cout<<"\n";
        cout<<"Distance from Diameter Nodes = "<<dia.second<<" \n";

        for(int i=1;i<=nodes;i++){
            cout<<dist[i][1]<<" ";
        }
        cout<<"\n";
    }
    long long int diav,ans=0;
    vector< pair < pair < int ,int>,int> > moves;
    while(leafSet.size()){
        int leaf=*leafSet.begin();
        if(!visited[leaf]){
            ans+=max(dist[leaf][0],dist[leaf][1]);
            int src=dia.first;
            if(dist[leaf][0]<dist[leaf][1]){
                src=dia.second;
            }
            leafSet.erase(leaf);
            for(int i=0;i<graph[leaf].size();i++){
                int child=graph[leaf][i];
                dig[child]--;
                if(dig[child]==1){
                    if(child!=dia.first && child!=dia.second)
                        leafSet.insert(child);
                }
            }
            moves.push_back(std::make_pair(std::make_pair(src,leaf),leaf));
        }
    }
    for(int i=0;i<path_from_a_to_b.size()-1;i++){
        int src=path_from_a_to_b[path_from_a_to_b.size()-1];
        int anothernode=path_from_a_to_b[i];
        moves.push_back(std::make_pair(std::make_pair(src,anothernode),anothernode));
    }
    if(ENABLELOG)
    {
        cout<<path_from_a_to_b.size()<<" ";
    }
    diav=0;
    diav=path_from_a_to_b.size();
    diav=diav*(diav-1);
    diav=diav/2;
    ans+=diav;
    cout<<ans<<"\n";
    for(int i=0;i<moves.size();i++){
        cout<<moves[i].first.first<<" "<<moves[i].first.second<<" "<<moves[i].second<<"\n";
    }
    moves.clear();

    return 0;
}