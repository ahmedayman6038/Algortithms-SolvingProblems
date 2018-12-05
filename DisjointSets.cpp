// GROUP:   1
// ID:      20150009
// Assign:  02
// Assign:  DisjointSets
// UVA:     10608
// Name:    Ahmed Ayman Hammad
// UVA UserName: ahmedayman6038

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

int main()
{
    DisjointSets sets;
    int cases;
    int n,m;
    int i,j;
    cin >> cases;
    while(cases > 0)
    {
        cin >> n;
        cin >> m;
        sets.Initialize(n);
        int maximum  = 1;
        while(m > 0)
        {
            cin >> i;
            cin >> j;
            sets.Union(--i,--j);
            m--;
        }
        for(int i = 0; i < sets.n; i++)
        {
            if(sets.num_nodes[i] > maximum)
            {
                maximum = sets.num_nodes[i];
            }
        }
        cout << maximum << endl;
        sets.Destroy();
        cases--;
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
