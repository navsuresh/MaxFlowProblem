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
  
int index=0;

struct Edge 
{ 
	long long int flow, capacity; 
	int u, v; 

	Edge(long long int flow,long long int capacity, int u, int v) 
	{ 
		this->flow = flow; 
		this->capacity = capacity; 
		this->u = u; 
		this->v = v; 
	} 
}; 

 
struct Vertex 
{ 
	int h;
	long long int e_flow; 

	Vertex(int h, long long int e_flow) 
	{ 
		this->h = h; 
		this->e_flow = e_flow; 
	} 
}; 

struct node
{
	int v;
	struct node* next;
};

struct neighbour
{
	int v;
	int e_index;
	int incoming_e_index;
};

class Graph 
{ 
	int V; 
	vector<Vertex> ver; 
	vector<Edge> edge;
	vector<vector<neighbour>> nList;
	node* queue_head;

	void push(int u, int v, int n_index); 

	void relabel(int u); 

	void preflow(int s); 

	void updateReverseEdgeFlow(int i, int flow); 

	void discharge(int u);

	void showResidualGraph();

	void printVerticesHeights();

public: 
	Graph(int V);

	void addEdge(int u, int v, int w); 

	long long int getMaxFlow(int s, int t); 
}; 

Graph::Graph(int V) 
{ 
	this->V = V; 

	for (int i = 0; i < V; i++) 
	{
		ver.push_back(Vertex(0, 0)); 
		nList.push_back(vector<neighbour>());
	}	
	queue_head = NULL;

} 

void Graph::addEdge(int u, int v, int capacity) 
{
	int i;
	neighbour nu, nv; 
	for (i = 0; i < nList[u].size(); ++i)
	{
		if(nList[u][i].v==v)
		{
			edge[nList[u][i].e_index].capacity=capacity;
			break;
		}
	}
	if(i==nList[u].size())
	{		
		edge.push_back(Edge(0, capacity, u, v)); 
		nu.v=v;
		nu.e_index=edge.size()-1;
	}
	for (i = 0; i < nList[v].size(); ++i)
	{
		if(nList[v][i].v==u)
		{
			edge[nList[v][i].e_index].capacity=capacity;
			break;
		}
	}
	if(i==nList[v].size())
	{
		nv.v=u;
		edge.push_back(Edge(0, 0, v, u)); 
		nv.e_index=edge.size()-1;
		nv.incoming_e_index = edge.size() - 2;	
		nu.incoming_e_index = edge.size() - 1;
		nList[v].push_back(nv);
		nList[u].push_back(nu);
	}
		
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
	
	for(int i=0; i<nList[s].size(); i++)
	{
		neighbour x = nList[s][i];
		edge[x.e_index].flow=edge[x.e_index].capacity;
		edge[x.incoming_e_index].flow-=edge[x.e_index].flow;
		ver[x.v].e_flow += edge[x.e_index].flow; 
	} 
} 

void Graph::printVerticesHeights()
{
	for (int i = 0; i < ver.size(); i++) 
	{
		cout<<"Vertex "<<i<<" height: "<<ver[i].h<<" Excess Flow: "<<ver[i].e_flow<<"\n";
	}
}

int overFlowVertex(vector<Vertex>& ver) 
{ 
	for (int i = 1; i < ver.size() - 1; i++) 
	if (ver[i].e_flow > 0) 
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


void Graph::push(int u, int v, int n_index) 
{ 
	neighbour x = nList[u][n_index];
	
	long long int flow = min(edge[x.e_index].capacity - edge[x.e_index].flow, ver[u].e_flow); 

	ver[u].e_flow -= flow; 

	ver[v].e_flow += flow; 

	edge[x.e_index].flow += flow;

	edge[x.incoming_e_index].flow -= flow; 

} 


void Graph::relabel(int u) 
{ 
	int mh = INT_MAX; 
	
	neighbour x;

	for(int i=0; i<nList[u].size(); i++)
	{
		x=nList[u][i];
	
		if (edge[x.e_index].flow == edge[x.e_index].capacity) 
			continue; 

		if (ver[edge[x.e_index].v].h < mh) 
		{ 
			mh = ver[edge[x.e_index].v].h; 
			ver[u].h = mh + 1; 
		} 
	}
} 

void Graph::discharge(int u)
{
	if(ver[u].e_flow==0)
		return;
	int x = 0, current = nList[u][0].v, v;
	while(ver[u].e_flow>0)
	{
		v = current;

		if(v==-1)
		{
			relabel(u);
			current = nList[u][0].v;
			x = 0;
		}
		else
		{
			int i;
			for ( i = 0; i < nList[u].size(); i++) 
			{ 
				neighbour x = nList[u][i];
				if (x.v == v) 
				{
					if(edge[x.e_index].capacity - edge[x.e_index].flow >0 && ver[u].h == ver[v].h+1)
					{
						push(u,v, i);
						break;
					}
				}
			}

			if(i==nList[u].size())
			{
				if(x+1 < nList[u].size())
					current = nList[u][++x].v;
				else
					current = -1;
			}
		}
	}
}


long long int Graph::getMaxFlow(int s, int t) 
{ 
	preflow(s); 
	node* curr = queue_head;
	
	for (int i = 0; i < ver.size(); ++i)
	{
		if(i!=s && i!=t)
		{
			if(queue_head)
			{
				node* temp = (node*)malloc(sizeof(node));
				temp->v = i;
				temp->next = NULL;
				curr->next = temp;
				curr = temp;
			}
			else
			{
				node* temp = (node*)malloc(sizeof(node));
				temp->v = i;
				temp->next = NULL;
				queue_head = temp;
				curr = queue_head;	
			}
		}
	}

	node *u = queue_head, *prev = NULL;
	
	while (u) 
	{ 
		int old_height = ver[u->v].h;
	
		discharge(u->v);
		
		if (ver[u->v].h > old_height) 
		{
			if(prev)
			{
				prev->next = u->next;
				u->next = queue_head;
				queue_head = u;
				prev = NULL;
				u = u->next;
			}
			else
			{
				prev = u;
				u = u->next;
			}
		}
		else
		{
			prev = u;
			u = u->next;
		}
	} 

	node* temp = NULL;
	curr = queue_head;
	while(curr)
	{
		temp = curr->next;
		free(curr);
		curr = temp;
	}
	
	return ver[t].e_flow; 
} 

int main()
{
	int s, t, n, e;
    char waste[4];
    fstream fd;
    fd.open("graph3x3.txt", ios::in);
    fd>>waste;
    fd>>waste;
    fd>>n>>e>>waste>>s>>waste>>waste>>t>>waste;
    s--;
    t--;
    Graph g(n);

    int src, dest, cap;
    int i;
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
    cout<<"g5x5\n";
    cout << "Maximum flow: " << max_flow<<endl; 
    cout<<"Time Taken: " << exec_time<<"\n";
    return 0; 
}
