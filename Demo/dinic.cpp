#include<iostream>
#include <fstream> 
#include<list>
#include<vector>
#include<climits>

#define FREQ 2.60e9

using namespace std; 

unsigned long long rdtsc()
{
  unsigned long long int x;
  unsigned a, d;

  __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

  return ((unsigned long long)a) | (((unsigned long long)d) << 32);
}
  
struct Edge 
{ 
    int v ;  
    int flow ;
    int C;    
    int rev ; 
}; 
  
 
class Graph 
{ 
    int V; 
    int *level ; 
    vector< Edge > *adj; 
public : 
    Graph(int V) 
    { 
        adj = new vector<Edge>[V]; 
        this->V = V; 
        level = new int[V]; 
    } 
  
    void addEdge(int u, int v, int C) 
    { 
        
        Edge a{v, 0, C, adj[v].size()}; 
  
        Edge b{u, 0, 0, adj[u].size()}; 
  
        adj[u].push_back(a); 
        adj[v].push_back(b); 
    } 
  
    bool BFS(int s, int t); 
    int sendFlow(int s, int flow, int t, int ptr[]); 
    int DinicMaxflow(int s, int t); 
    void showLevelGraph();
    void showResidualGraph();
}; 
  
bool Graph::BFS(int s, int t) 
{ 
    for (int i = 0 ; i < V ; i++) 
        level[i] = -1; 
  
    level[s] = 0; 
  
    list< int > q; 
    q.push_back(s); 
  
    vector<Edge>::iterator i ; 
    while (!q.empty()) 
    { 
        int u = q.front(); 
        q.pop_front(); 
        for (i = adj[u].begin(); i != adj[u].end(); i++) 
        { 
            Edge &e = *i; 
            if (level[e.v] < 0  && e.flow < e.C) 
            { 
                
                level[e.v] = level[u] + 1; 
  
                q.push_back(e.v); 
            } 
        } 
    } 
  
    return level[t] < 0 ? false : true ; 
} 
  

int Graph::sendFlow(int u, int flow, int t, int start[]) 
{ 

    if (u == t) 
    {
        //cout<<"Bottleneck Flow: "<<flow<<endl;
        return flow;
    }     
  
    //cout<<"No. of Edges from source "<<adj[u].size()<<endl<<"No. traversed: "<<start[u]<<endl;  
    for (  ; start[u] < adj[u].size(); start[u]++) 
    { 
        Edge &e = adj[u][start[u]];  
        //cout<<"Next Edge Level: "<<level[e.v]<<endl;  

        if (level[e.v] == level[u]+1 && e.flow < e.C) 
        { 
        
            int curr_flow = min(flow, e.C - e.flow); 
  
            int temp_flow = sendFlow(e.v, curr_flow, t, start); 
  
        
            if (temp_flow > 0) 
            { 
                cout<<e.v<<"<-";
                if(level[e.v] == 1)
                    cout<<"0";
                e.flow += temp_flow; 
  
                adj[e.v][e.rev].flow -= temp_flow; 
                return temp_flow; 
            } 
        } 
    } 
    //cout<<"u: "<<u<< " t:s"<<t<<endl;
  
    return 0; 
} 
  
void Graph::showLevelGraph()
{
    cout<<"-------------LEVEL GRAPH--------------\n";
    cout<<"Vertex\t\t"<<"Level\n";
    for(int i = 0; i < V; i ++)
        cout<<i<<"\t\t"<<level[i]<<"\n";
}

void Graph::showResidualGraph()
{
    cout<<"-----------RESIDUAL GRAPH-----------\n";
    cout<<"Source\t "<<"Destination\t"<<"Capacity\t"<<"Flow\t"<<"Remaining Capacity\n";
    for (int i = 0; i < V; i++) 
    {
        for(int j = 0; j < adj[i].size(); j++)
        {
            cout<<i<<"\t\t"<<adj[i][j].v<<"\t\t"<<adj[i][j].C<<"\t"<<adj[i][j].flow<<"\t"<<adj[i][j].C - adj[i][j].flow<<"\n";
        }
    }
}


int Graph::DinicMaxflow(int s, int t) 
{ 
    
    if (s == t) 
        return -1; 
  
    int total = 0;  
  
    while (BFS(s, t) == true) 
    { 
        showLevelGraph();
        int *start = new int[V+1]; 
        int count = 0;
        cout<<"Before Sending Flows\n";
        showResidualGraph();
        while (int flow = sendFlow(s, INT_MAX, t, start)) 
        {
            cout<<endl;
            showResidualGraph();
            total += flow; 
            cout<<"Current Flow: "<<total<<endl;
        } 
            
    } 
  
    return total; 
} 
  
int main() 
{ 
    int s, t, n, e;
    int src, dest, cap;
    int i;
    char waste[4];
    fstream fd;
    
    fd.open("small.txt", ios::in);

    fd>>waste;
    fd>>waste;
    fd>>n>>e>>waste>>s>>waste>>waste>>t>>waste;
    
    s--;
    t--;
    
    Graph g(n);

    for(i = 0; i < e; i++)
    {
        fd>>waste>>src>>dest>>cap;
        if(cap)
            g.addEdge(src-1,dest-1,cap); 
    }    

    unsigned long long t0,t1;
    t0=rdtsc();      
    long long int max_flow = g.DinicMaxflow(s, t);
    t1=rdtsc();     
    double exec_time = (t1-t0)/FREQ;
    cout<<"small\n";
    cout<<"Maximum flow: "<<max_flow<<endl; 
    cout<<"Time Taken: "<<exec_time<<"\n";
    return 0; 
}
