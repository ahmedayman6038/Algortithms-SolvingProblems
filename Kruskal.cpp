// GROUP:   1
// ID:      20150009
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    Ahmed Ayman Hammad
// UVAUsername: ahmedayman6038
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Edge
{
	int u, v;
	int w;
};

struct DisjointSets
{
	int n;
	int* parent;
	int* num_nodes;

	void Initialize(int _n)
	{
	    n = _n;
	    parent = new int[n];
	    num_nodes = new int[n];
	    for(int i = 0; i < n; i++)
        {
            parent[i] = -1;
            num_nodes[i] = 1;
        }
	}

	void Destroy()
	{
	    delete[] parent;
	    delete[] num_nodes;
	}

	int Find(int i)
	{
	    int p = i;
	    while(parent[p] != -1)
        {
            p = parent[p];
        }
        return p;
	}

	bool Union(int i, int j)
	{
	    int a = Find(i);
	    int b = Find(j);
	    if(a == b)
        {
            return false;
        }
        if(num_nodes[a] >= num_nodes[b])
        {
            parent[b] = a;
            num_nodes[a] += num_nodes[b];
        }
        else
        {
            parent[a] = b;
            num_nodes[b] += num_nodes[a];
        }
        return true;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = n/2;
    Type temp[n];
    int i = 0;
    int j = mid;
    int k = 0;
    while(i < mid && j <= n-1)
    {
        if(IsBefore(a[i], a[j]))
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
        }
    }
    while (i < mid)
    {
        temp[k++] = a[i++];
    }
    while (j <= n-1)
    {
        temp[k++] = a[j++];
    }
    for (int i = 0 ; i < n ; i++)
    {
        a[i] = temp[i];
    }
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid;
    if(n > 1)
    {
        mid = n/2;
        MergeSort(a, mid, IsBefore);
        MergeSort(a + (mid), n - mid,IsBefore);
        Merge(a, n, IsBefore);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////


bool IsBeforeEdge(Edge& a, Edge& b)
{
	return a.w<b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int m, n;
    input: cin >> m >> n;
    while(m != 0 && n != 0){
        Edge edges[n];
        DisjointSets sets;
        sets.Initialize(n-1);
        int maxCost = 0;
        int minCost = 0;
        int diff;
        for(int i=0;i<n;i++){
            Edge edge;
            cin >> edge.u >> edge.v >> edge.w;
            edges[i] =  edge;
            maxCost += edge.w;
        }
        MergeSort(edges, n,IsBeforeEdge);
        for(int i=0;i<n;i++){
            if(sets.Union(edges[i].u,edges[i].v)){
                minCost += edges[i].w;
            }
        }
        diff = maxCost - minCost;
        cout<<diff<<endl;
        goto input;
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
