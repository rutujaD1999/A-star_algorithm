#include<bits/stdc++.h>
#include<fstream>
#define V 26
using namespace std;


struct Node
{
    int path_cost;
    int hcost;
    int fcost;
    vector<int> parent;
    int vertex;
};

int initial=0;
// int vis[V]={0};
vector<int> vis(V,0);
ifstream fin;

struct CompareFcost { 
    bool operator()(Node const& a, Node const& b) 
    { 
       
        return a.fcost > b.fcost; 
    } 
}; 


priority_queue <Node,vector<Node>,CompareFcost> pq; 

bool goalState(Node node)
{
    for(int i=0;i<V;i++)
    {
        if(vis[i]==0)
        {
            return false;
        }
    }
    
    return true;
}

int minKey(int key[], bool mstSet[]) 
{ 
    // Initialize min value 
    int min = INT_MAX, min_index; 
 
    for (int v = 0; v < V; v++) 
        if (mstSet[v] == false && key[v] < min) 
            min = key[v], min_index = v; 
 
    return min_index; 
} 

int mst(int k,int graph[][V],vector<int> par)
{
    
    int key[V]; 
     
     bool mstSet[V]; 
 
     for (int i = 0; i < V; i++) 
        key[i] = INT_MAX, mstSet[i] = false; 
    for(int i=0;i<par.size();i++)
    {
        mstSet[par[i]]=true;
        key[par[i]]=0;
    }
    mstSet[k]=true;
     key[k] = 0; 
    int s=0;
    while(mstSet[s])
    {
        s++;
    }
    if(s<V)
    {
        key[s]=0;
        // cout<<"Starting mst from "<<s<<endl;
    }
    else
    {
        return 0;
    }
   
    int rem=V-par.size()-1;
    for (int count = 0; count < rem - 1; count++)
    { 
        int u = minKey(key, mstSet); 
        mstSet[u] = true; 
 
         for (int v = 0; v < V; v++) 
 
            
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v]) 
            {
                key[v] = graph[u][v]; 
                // cout<<"v "<<v<<" "<<key[v]<<endl;
            }
    } 
    
    int sum=0;
    // for (int i = 0; i < V; i++) 
   
    for(int i=0;i<V;i++)
    {
        // cout<<key[i]<<" ";
        sum=sum+key[i];
    }
    // cout<<endl;
    // cout<<"mst cost is "<<sum<<endl;
    return sum;
}


int nearestUnvisitedNode(int graph[][V],int v)
{
    int m=INT_MAX,flag=0;
    for(int i=0;i<V;i++)
    {
        if(i!=v)
        {
            if(vis[i]==0 && graph[i][v]<m)
            {
                m=graph[i][v];
                flag=1;
            }
        }
    }
    if(flag==0)
    {
        return 0;
    }
    return m;
}

int nearestDistanceFromInitial(int graph[][V],int v)
{
    int m=INT_MAX;
    for(int i=1;i<V;i++)
    {
        // if(i!=v)
        // {
            if(vis[i]==0 && graph[initial][i]<m)
            {
                m=graph[initial][i];
            }
        // }
    }
    return m;
}


Node makeNode(int v,Node p,int cost,int graph[][V])
{
    Node node;
    // if(p.parent.size()!=0)
    // {
	node.path_cost=cost+graph[p.vertex][v];
	node.parent=p.parent;
	node.parent.push_back(p.vertex);
    // }
    // else
    // {
    //     node.path_cost=cost;
    // }
    node.hcost=mst(v,graph,node.parent)+nearestDistanceFromInitial(graph,v)+nearestUnvisitedNode(graph,v);
    // node.hcost=mst(v,graph,node.parent);
    cout<<"v : "<<node.hcost<<endl;
    node.fcost=node.hcost+node.path_cost;
    cout<<"f : "<<node.fcost<<endl;
    
    node.vertex=v;
    return node;
}

void successor(Node v,int graph[][V])
{
    cout<<"Expanding : "<<v.vertex<<endl;
    for(int i=0;i<V;i++)
    {
        if(vis[i]==0 && graph[v.vertex][i]!=0)
        {
            cout<<"Pushing vertex : "<<i<<endl;
            pq.push(makeNode(i,v,v.path_cost,graph));
        }
    }
}


vector<int> assignVisited(Node n)
{
    vector<int> vis(V,0);
    for(int i=0;i<n.parent.size();i++)
    {
        vis[n.parent[i]]=1;
    }
    return vis;
}


int main()
{
    
    
     /*int graph[][V] = { {0,10,15,20},
                         {10,0,35,25},
                         {15,35,0,30},
                         {20,25,30,0} };*/
                        
    
	fin.open("input1.txt");
	int graph[V][V];
	for(int i=0;i<V;i++)
	{
		for(int j=0;j<V;j++)
		{
			fin>>graph[i][j];
		}
	}
	
	
	

    Node start;
    start.path_cost=0;
    start.hcost=mst(0,graph,start.parent)+nearestDistanceFromInitial(graph,0)+nearestUnvisitedNode(graph,0);
    // start.hcost=mst(0,graph,start.parent);
    cout<<"v : "<<start.hcost<<endl;
    start.fcost=start.hcost+start.path_cost;
    cout<<"f : "<<start.fcost<<endl;
    start.vertex=0;
    
    pq.push(start);
    
    int flag=0;
    // int prevNode=-1;
    while(!pq.empty())
    {
        Node node=pq.top();
        pq.pop();
        
        vis=assignVisited(node);
        vis[node.vertex]=1;
        if(goalState(node))
        {
            cout<<"GOAL STATE!!"<<endl<<"COST IS : "<<node.path_cost+graph[0][node.vertex]<<endl;
            cout<<"THE PATH IS : ";
            for(int i=0;i<node.parent.size();i++)
            {
                cout<<node.parent[i]<<" ";
            }
            cout<<node.vertex<<" 0"<<endl;
            flag=1;
            break;
        }
        
        // prevNode=node.vertex;
        successor(node,graph);
    }
    cout<<"TIME TAKEN : "<<(float)clock()/CLOCKS_PER_SEC<<" secs "<<endl;
    return 0;
}
