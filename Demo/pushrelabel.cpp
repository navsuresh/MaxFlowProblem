#include <bits/stdc++.h> 
using namespace std; 

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
	int flow, capacity; 
	int u, v; 

	Edge(int flow, int capacity, int u, int v) 
	{ 
		this->flow = flow; 
		this->capacity = capacity; 
		this->u = u; 
		this->v = v; 
	} 
}; 

struct Vertex 
{ 
	int h, e_flow; 

	Vertex(int h, int e_flow) 
	{ 
		this->h = h; 
		this->e_flow = e_flow; 
	} 
}; 

class Graph 
{ 
	int V; 
	vector<Vertex> ver; 
	vector<Edge> edge; 

	bool push(int u); 

	void relabel(int u); 

	void preflow(int s); 

	void updateReverseEdgeFlow(int i, int flow); 

	void showResidualGraph();

	void printVerticesHeights();

public: 
	Graph(int V); 

	void addEdge(int u, int v, int w); 

	int getMaxFlow(int s, int t); 
}; 

Graph::Graph(int V) 
{ 
	this->V = V; 

	for (int i = 0; i < V; i++) 
		ver.push_back(Vertex(0, 0)); 
} 

void Graph::addEdge(int u, int v, int capacity) 
{ 
	edge.push_back(Edge(0, capacity, u, v)); 
} 

void Graph::showResidualGraph()
{
	for (int i = 0; i < edge.size(); i++) 
	{
		cout<<"From "<<edge[i].u<<" to "<<edge[i].v<<": cap "<<edge[i].capacity<<" and flow "<<edge[i].flow<<"\n";
	}
}

void Graph::preflow(int s) 
{ 
	ver[s].h = ver.size(); 

	for (int i = 0; i < edge.size(); i++) 
	{ 
		if (edge[i].u == s) 
		{ 
			edge[i].flow = edge[i].capacity; 

			ver[edge[i].v].e_flow += edge[i].flow; 

			//updateReverseEdgeFlow(i,edge[i].flow);

			edge.push_back(Edge(-edge[i].flow, 0, edge[i].v, s));
		} 
	} 
} 

void Graph::printVerticesHeights()
{
	for (int i = 0; i < ver.size(); i++) 
	{
		cout<<"Vertex "<<i<<" height: "<<ver[i].h<<" Excess Flow: "<<ver[i].e_flow<<"\n";
	}
}


int overFlowVertex(vector<Vertex>& ver, int s, int t) 
{ 
	for (int i = 0; i < ver.size() ; i++) 
		if (i!=s && i!=t && ver[i].e_flow > 0) 
			return i; 

	return -1; 
} 

void Graph::updateReverseEdgeFlow(int i, int flow) 
{ 
	int u = edge[i].v, v = edge[i].u; 

	for (int j = 0; j < edge.size(); j++) 
	{ 
		if (edge[j].v == v && edge[j].u == u) 
		{ 
			edge[j].flow -= flow; 
			return; 
		} 
	} 

	Edge e = Edge(0, flow, u, v); 
	edge.push_back(e); 
} 


bool Graph::push(int u) 
{ 
	for (int i = 0; i < edge.size(); i++) 
	{ 
		if (edge[i].u == u) 
		{ 
			if (edge[i].flow == edge[i].capacity) 
				continue; 

			if (ver[u].h > ver[edge[i].v].h) 
			{ 
				cout<<"Flow can be pushed to vertex "<<edge[i].v<<"\n";

				int flow = min(edge[i].capacity - edge[i].flow, ver[u].e_flow); 

				ver[u].e_flow -= flow; 

				ver[edge[i].v].e_flow += flow; 

				edge[i].flow += flow; 

				updateReverseEdgeFlow(i, flow); 

				return true; 
			} 
		} 
	} 
	return false; 
} 

void Graph::relabel(int u) 
{ 

	cout<<"Relabel height of vertex "<<u<<"\n";
	int mh = INT_MAX; 

	for (int i = 0; i < edge.size(); i++) 
	{ 
		if (edge[i].u == u) 
		{ 
			
			if (edge[i].flow == edge[i].capacity) 
				continue; 

			if (ver[edge[i].v].h < mh) 
			{ 
				mh = ver[edge[i].v].h; 

				ver[u].h = mh + 1; 
			} 
		} 
	} 

	cout<<"New height of u is "<<ver[u].h<<"\n";
} 

int Graph::getMaxFlow(int s, int t) 
{ 
	preflow(s); 
	int u = overFlowVertex(ver,s,t); 

	while (u != -1) 
	{ 
		cout<<"Vertex with overflow is: "<<u<<"\n";
		showResidualGraph();
		cout<<"\n\n";
		printVerticesHeights();

		if (!push(u)) 
			relabel(u); 
		u = overFlowVertex(ver,s,t); 
	} 

	return ver[t].e_flow; 
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
    long long int max_flow = g.getMaxFlow(s, t);
    t1=rdtsc();     
    double exec_time = (t1-t0)/FREQ;
    cout<<"small\n";
    cout<<"Maximum flow: "<<max_flow<<endl; 
    cout<<"Time Taken: "<<exec_time<<"\n";
    return 0;   
} 
