// GROUP:   G1
// ID:     20150009
// Assign:  06
// Assign:  Prim
// UVA:     534
// Name:   Ahmed Ayman Hammad
// UVA Username: ahmedayman6038

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <iomanip>
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

    void Print()
    {
        for(int i = 0; i < n; i++)
        {
            cout << arr[i] << ",";
        }
    }

	Value& operator[](int i)
	{
        return arr[i];
	}
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int		v;  // id of the adjacent node
	double	w;  // edge weight = distance between the two nodes
};


struct Node
{
    int x,y; // x and y coordinates of the node
	Array<Edge> adj;

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

// Find the square root of "v" in "n" iterations
double Sqrt(double v, int n=100)
{
    if(v<0)
    {
        return -1;
    }
    if(v==0 || v==1)
    {
        return v;
    }
    double start = 0;
    double end = v;
    if(v<1)
    {
        end = 1;
    }
    while(n--)
    {
        double mid = (start+end)/2;
        double midSqr = mid*mid;
        if(midSqr==v)
        {
            return mid;
        }
        else if(midSqr<v)
        {
            start = mid;
        }
        else
        {
            end = mid;
        }
    }
    return (start+end)/2;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int stones;
    int cases = 1;
    input: cin>>stones;
    while(stones != 0)
    {
        Graph graph;
        graph.Initialize(stones);
        for(int i=0;i<stones;i++)
        {
            int x,y;
            cin>>x>>y;
            graph.nodes[i].x = x;
            graph.nodes[i].y = y;
        }
        for(int i=0;i<stones;i++)
        {
            for(int j=0;j<stones;j++)
            {
                if(i!=j)
                {
                    Edge edge;
                    edge.v = j;
                    int x1 = graph.nodes[i].x;
                    int x2 = graph.nodes[j].x;
                    int diff1 = abs(x1 - x2);
                    int y1 = graph.nodes[i].y;
                    int y2 = graph.nodes[j].y;
                    int diff2 = abs(y1 - y2);
                    edge.w = Sqrt((diff1*diff1)+(diff2*diff2));
                    graph.nodes[i].adj.AddLast(edge);
                }

            }
        }
        int mst[stones];
        bool visited[stones];
        for(int i=0;i<stones;i++)
        {
            visited[i] = false;
        }
        mst[0] = 0;
        visited[mst[0]] = true;
        int counter = 1;
        Graph result;
        result.Initialize(stones);
        while(counter < stones)
        {
            double min = 1000000;
            int minNode;
            int srcNode;
            for(int i=0;i<counter;i++)
            {
                for(int j=0;j<graph.nodes[mst[i]].adj.n;j++)
                {
                    if(graph.nodes[mst[i]].adj[j].w < min && !visited[graph.nodes[mst[i]].adj[j].v])
                    {
                        min = graph.nodes[mst[i]].adj[j].w;
                        minNode = graph.nodes[mst[i]].adj[j].v;
                        srcNode = mst[i];
                    }
                }
            }
            mst[counter] = minNode;
            Edge er;
            er.v = minNode;
            er.w = min;
            result.nodes[srcNode].adj.AddLast(er);
            visited[minNode] = true;
            counter++;
        }
        queue<vector<Edge> > q;
        vector<Edge> path;
        Edge e;
        e.v = 0;
        e.w = 0;
        path.push_back(e);
        q.push(path);
        double frogDistance = 0;
        while(!q.empty())
        {
            path = q.front();
            q.pop();
            Edge last = path[path.size()-1];
            if(last.v == 1)
            {
                for(int i = 0;i<path.size();i++)
                {
                   if(path[i].w > frogDistance)
                   {
                       frogDistance = path[i].w ;
                   }
                }
            }
            for(int i = 0; i < result.nodes[last.v].adj.n; i++)
            {
                vector<Edge> newPath(path);
                Edge ne;
                ne.v = result.nodes[last.v].adj[i].v;
                ne.w = result.nodes[last.v].adj[i].w;
                newPath.push_back(ne);
                q.push(newPath);
            }
        }
        cout<<"Scenario #"<<cases<<endl;
        cout<<"Frog Distance = "<<fixed<<setprecision(3)<<frogDistance<<endl<<endl;
        cases++;
        goto input;
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
