// GROUP:   1
// ID:      20150009
// Assign:  03
// Assign:  Graphs
// UVA:     924
// Name:    Ahmed Ayman Hammad
// UVA UserName: ahmedayman6038

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include<queue>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
	int  n, sz;
	Value* arr;

	void Initialize()
	{
        n = 0;
        sz = 1;
        arr = new Value[sz];
	}

	void Destroy()
	{
        delete[] arr;
	}

	void AddLast(Value v)
	{
        if(n == sz)
        {
            sz*=2;
            Value* new_arr = new Value[sz];
            for(int i = 0; i < n; i++)
            {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
        }
        arr[n++] = v;
	}

	void RemoveLast()
	{
        n--;
	}

	Value& operator[](int i)
	{
        return arr[i];
	}
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node
{
	Array<int> adj;

	void Initialize()
	{
	    adj.Initialize();
	}

	void Destroy()
	{
	    adj.Destroy();
	}
};

struct Graph
{
	int n;
	Node* nodes;

	void Initialize(int _n)
	{
	    n = _n;
	    nodes = new Node[n];
	    for(int i = 0; i < n; i++)
        {
            nodes[i].Initialize();
        }
	}

	void Destroy()
	{
	    for(int i = 0; i < n; i++)
        {
            nodes[i].Destroy();
            delete[] nodes;
        }
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Type>
struct Queue
{
	int f, n;
	Type* elems;

	void Initialize(int size)
	{
	    f = n = 0;
	    elems = new Type[size];
	}

	void Destroy()
	{
	    delete[] elems;
	}

	void Add(Type t)
	{
	    elems[n++] = t;
	}

	Type Pop()
	{
	    if(f == n)
        {
            cout<<"Queue is Empty"<<endl;
            return -1;
        }
	    return elems[f++];
	}

	Type Peek()
	{
	    return elems[f];
	}

	int Num()
	{
	    return n-f;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int employes;
    while(true)
    {
        cin>>employes;
        Graph graph;
        graph.Initialize(employes);
        for(int i = 0; i < employes; i++)
        {
            int friendsNum;
            cin >> friendsNum;
            for(int j = 0; j < friendsNum; j++)
            {
                int friends;
                cin >> friends;
                graph.nodes[i].adj.AddLast(friends);
            }
        }
        int cases;
        cin >> cases;
        while(cases > 0)
        {
            Queue<int> que;
            que.Initialize(employes);
            int *visit = new int[employes];
            int *coun = new int[employes];
            for(int k = 0; k < employes; k++)
            {
                visit[k] = 0;
                coun[k] = 0;
            }
            int source;
            cin >> source;
            que.Add(source);
            visit[source] = 1;
            int maxBoomSize = 0;
            int firstBoomDay;
            while(que.Num() > 0)
            {
                int pop = que.Pop();
                for(int i = 0; i < graph.nodes[pop].adj.n; i++)
                {
                    int f = graph.nodes[pop].adj[i];
                    if(visit[f] == 0)
                    {
                        visit[f] = visit[pop] + 1;
                        que.Add(f);
                        coun[visit[f]] += 1;
                        if(maxBoomSize < coun[visit[f]])
                        {
                            maxBoomSize = coun[visit[f]];
                            firstBoomDay = visit[f];
                        }
                    }
                }
            }
            if(graph.nodes[source].adj.n < 1)
            {
                cout << 0 << endl;
            }
            else
            {
                cout << maxBoomSize << " " << firstBoomDay - 1 << endl;
            }
            que.Destroy();
            cases--;
        }
        //graph.Destroy();
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
