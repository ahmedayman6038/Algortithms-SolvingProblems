// GROUP:   1
// ID:      20150009
// Assign:  07
// Assign:  Dijkstra
// UVA:     10986
// Name1:   Ahmed Ayman Hammad

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
    int n,sz;
    Value *arr;
    void initilize()
    {
        sz = 1;
        n =0;
        arr = new Value[sz];
    }

    void destroy()
    {
        delete [] arr;

    }

    void AddLast(Value v)
    {
        if(n == sz)
        {
            sz*=2;
            Value * newArr = new Value[sz];

            for(int i=0;i<n;i++)
            {

                newArr[i] = arr[i];
            }

            delete arr;

            arr = newArr;

        }

        arr[n++] = v;
    }

    void RemoveLast()
    {
        n--;

    }

    Value & operator [] (int i)
    {

        return arr[i];
    }

    void print()
    {
        for(int i=0;i<n;i++)
        {
            cout<<arr[i]<<endl;

        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Elem>
struct Heap
{
    int* pos; // pos[v]=i where a[i].v=v, otherwise pos[v]=-1
    int posSize;
    Array<Elem> a;
    bool (*IsBefore)(Elem&, Elem&);

    void Initialize(bool (*_IsBefore)(Elem&, Elem&), int n) // n is required to allocate and initialize pos[]
    {
        IsBefore = _IsBefore;
        a.initilize();
        posSize=n;
        pos= new int [n];
        for(int i=0;i<n;i++)
        {
            pos[i]=-1;
        }
    }
    void Destroy()
    {
        a.destroy();
        delete[] pos;
    }
    void Print();
    int Child(int i)
    {
        return (i*2)+1;
    }
    int Parent(int i)
    {
        return (i-1)/2;
    }
    Elem GetFirst()
    {
        return a[0];
    }
    Elem RetrieveFirst()
    {
        Elem temp=a[0];
        a[0]=a[a.n-1];
        MoveDown(0);
        a.RemoveLast();
        for(int i=0;i<posSize;i++)
        {
            pos[i]=-1;
        }
        for(int i=0;i<a.n;i++)
        {
            pos[a[i].v]=i;
        }
        return temp;
    }
    void Add(Elem e)
    {
        a.AddLast(e);
        MoveUp(a.n-1);
        for(int i=0;i<posSize;i++)
        {
            pos[i]=-1;
        }
        for(int i=0;i<a.n;i++)
        {
            pos[a[i].v]=i;
        }
    }
    void MoveUp(int ind)
    {
        if(ind<a.n&&Parent(ind)<a.n)
        {
            if(IsBefore(a[ind],a[Parent(ind)]))
            {
                Elem temp;
                temp=a[ind];
                a[ind]= a[Parent(ind)];
                a[Parent(ind)]= temp;
                MoveUp(Parent(ind));
            }
        }
    }
    void MoveDown(int ind)
    {
        if(ind<a.n&&Child(ind)<a.n&&Child(ind+1)<a.n)
        {
            int index_min;
            if(IsBefore(a[Child(ind)],a[Child(ind)+1]))
            {
                index_min=Child(ind);
            }
            else
            {
                index_min=Child(ind)+1;
            }
            if(IsBefore(a[index_min],a[ind]))
            {
                Elem temp;
                temp=a[ind];
                a[ind]= a[index_min];
                a[index_min]= temp;
                MoveDown(index_min);
            }
        }
        else if(ind<a.n&&Child(ind)<a.n)
        {
            if(IsBefore(a[Child(ind)],a[ind]))
            {
                Elem temp;
                temp=a[ind];
                a[ind]= a[Child(ind)];
                a[Child(ind)]= temp;
                MoveDown(Child(ind));
            }
        }
    }

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
    int v;
    int w;
};

struct Node
{
    Array<Edge> adj;

    void Initialize()
    {
        adj.initilize();
    }
    void Destroy()
    {
        adj.destroy();
    };
};

struct Graph
{
    int n;
    Node* nodes;

    void Initialize(int _n)
    {
        int i;
        n=_n;
        nodes=new Node[n];
        for(i=0;i<n;i++)
        {
            nodes[i].Initialize();
        }
    }

    void Destroy()
    {
        int i;
        for(i=0;i<n;i++)
        {
            nodes[i].Destroy();
        }
        delete[] nodes;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Edge& a, Edge& b)
{
    return a.w<b.w;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
int shortestPath(int src,int Dist,Graph allServers,int numberOfCables)
{
    Array<Edge> dist;
    dist.initilize();
    Heap <Edge> *heap=new Heap<Edge>;
    heap->Initialize(&IsBefore,numberOfCables);
    Edge *temp=new Edge;
    temp->v=src;
    temp->w=0;
    heap->Add(*temp);
    delete temp;
    for(int i=0;i<allServers.n;i++)
    {
        if(i!=src)
        {
          temp=new Edge;
          temp->v=i;
          temp->w=10001;
          heap->Add(*temp);
          delete temp;
        }
    }
    while (heap->a.n!=0)
    {
        Edge SrcEdge=heap->RetrieveFirst();
        dist.AddLast(SrcEdge);
        for(int i=0;i<allServers.nodes[SrcEdge.v].adj.n;i++)
        {
            int v=allServers.nodes[SrcEdge.v].adj[i].v;
            int w=allServers.nodes[SrcEdge.v].adj[i].w;
            int index =heap->pos[v];
            if(index!=-1)
            {
                heap->a[index].w=(SrcEdge.w+w);

            }
        }

    }
    for(int i=0;i<dist.n;i++)
    {
        if(dist[i].v==Dist)
        {
            return dist[i].w;
        }
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int numberOfTestCases=0;
    cin>>numberOfTestCases;
    for(int i=0;i<numberOfTestCases;i++)
    {
        int numberOfStmpServers=0;
        int numberOfCables=0;
        int ServerSrc=0;
        int ServerDist=0;
        cin>>numberOfStmpServers>>numberOfCables>>ServerSrc>>ServerDist;
        Graph *allServers=new Graph;
        allServers->Initialize(numberOfStmpServers);
        for(int j=0;j<numberOfCables;j++)
        {
            int src=0;
            int dist=0;
            int cost=0;
            cin>>src>>dist>>cost;
             Edge  *temp = new Edge;
            temp->v=dist;
            temp->w=cost;
            allServers->nodes[src].adj.AddLast(*temp);
            delete temp;
            temp = new Edge;
            temp->v=src;
            temp->w=cost;
            allServers->nodes[dist].adj.AddLast(*temp);
            delete temp;


        }
        cout<<"Case #"<<i<<": ";
        int shortestpath=shortestPath(ServerSrc,ServerDist,*allServers,numberOfCables);
        if(shortestpath!=10001)
        {
            cout<<shortestpath<<endl;
        }
        else
        {
            cout<< "unreachable"<<endl;
        }



    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
