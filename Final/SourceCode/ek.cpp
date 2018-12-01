#include <iostream> 
#include <limits.h> 
#include <string.h> 
#include <queue> 
#include <fstream>
using namespace std; 

#define FREQ 2.60e9

unsigned long long rdtsc()
{
  unsigned long long int x;
  unsigned a, d;

  __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

  return ((unsigned long long)a) | (((unsigned long long)d) << 32);
}

void print_matrix(int** graph,int max_flow,int V);

bool bfs(int** rGraph, int s, int t, int parent[],int V) 
{ 
	bool visited[V]; 
	memset(visited, 0, sizeof(visited)); 

	queue <int> q; 
	q.push(s); 
	visited[s] = true; 
	parent[s] = -1; 

	while (!q.empty()) 
	{ 
		int u = q.front(); 
		q.pop(); 

		for (int v=0; v<V; v++) 
		{ 
			if (visited[v]==false && rGraph[u][v] > 0) 
			{ 
				q.push(v); 
				parent[v] = u; 
				visited[v] = true; 
			} 
		} 
	} 
	return (visited[t] == true); 
} 

int fordFulkerson(int** graph, int s, int t,int V) 
{ 
	int u, v; 

	int** rGraph = new int*[V];
	for (int i = 0; i < V; ++i)
	{
		rGraph[i] = new int[V];
	}; 

	for (u = 0; u < V; u++) 
		for (v = 0; v < V; v++) 
			rGraph[u][v] = graph[u][v]; 

	int parent[V]; 

	int max_flow = 0;

	while (bfs(rGraph, s, t, parent, V)) 
	{ 
		int path_flow = INT_MAX; 
		for (v=t; v!=s; v=parent[v]) 
		{ 
			u = parent[v]; 
			path_flow = min(path_flow, rGraph[u][v]); 
		} 

		for (v=t; v != s; v=parent[v]) 
		{ 
			u = parent[v]; 
			rGraph[u][v] -= path_flow; 
			rGraph[v][u] += path_flow; 
		}

		max_flow += path_flow; 
	} 

	return max_flow; 
} 

void print_matrix(int** graph,int max_flow,int V)
{
	
	for (int i = 0; i < V; ++i)
	{
		for (int j = 0; j < V; ++j)
		{
			cout << graph[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "The flow in the residual graph is " << max_flow << "\n" << endl;
	
}

int main() 
{ 
	char p;
	char str[3];
	int line_count,V,v1,v2,capacity,s,t,x;
	fstream fd;

	fd.open("500x20000.txt", ios::in);

	fd >> p >> str >> V >> line_count;
	fd >> p >> s >> p;
	fd >> p >> t >> p;
	int** graph = new int*[V];
	for (int i = 0; i < V; ++i)
	{
		graph[i] = new int[V];
		for (int j = 0; j < V; ++j)
		{
			graph[i][j] = 0;
		}
	}
	for (int i = 0; i < line_count; ++i)
	{
		fd >> p >> v1 >> v2 >> capacity;
		graph[v1-1][v2-1] = capacity;
	}


	unsigned long long t0,t1;
    t0=rdtsc();   

    cout<<"500x20000\n";
	cout << "Maximum flow: " << fordFulkerson(graph, s-1, t-1, V) << endl;

	t1=rdtsc();   

    cout << "Time taken: " <<(t1-t0)/FREQ << endl; 
	return 0; 
}