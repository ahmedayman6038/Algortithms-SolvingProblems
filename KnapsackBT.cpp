// GROUP:   1
// ID:      20150009
// Assign:  12
// Assign:  KnapsackBT
// UVA:     10130
// Name:    Ahmed Ayman
// UVA Username: ahmedayman6038

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

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

struct Obj
{
	int v;
	int w;
};

int n;       // number of objects (input)
Obj a[1000]; // objects (input)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Obj& a, Obj& b) // return true if unit value of a is greater than unit value of b
{
    double r1 = (double)a.v / a.w;
    double r2 = (double)b.v / b.w;
    return r1>r2;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int best_val; // the best total value found until now

int Bound(int i, int w)// upper bound on the total value of items [i..n-1] that can fit in w
{
    int b = 0;
    int cw = 0;
    for(int j=i; j<n; j++)
    {
        if(cw <= w)
        {
            w -= a[j].w;
            b += a[j].v;
            cw += a[j].w;
        }
        else
        {
            b += (((double)a[j].v / a[j].w) * w);
            break;
        }
    }
    return b;
}

void BackTrack(int i, int w, int cur_val) // starting from item i, remaining weight w, cur_value of objects[0..i-1]
{
    if (i == n)
    {
        if(best_val < cur_val)
        {
            best_val = cur_val;
        }
        return;
    }
    if(cur_val + Bound(i,w) < best_val)
    {
        return;
    }
    if(a[i].w <= w)
    {
        BackTrack(i+1, w-a[i].w,cur_val+a[i].v);
    }
    BackTrack (i+1, w,cur_val);
}

int ComputeKnapsack(int N, int W) // solve knapsack of N objects and W weight
{
    MergeSort(a,N,IsBefore);
    BackTrack(0,W,0);
    return best_val;
}

void Compute()
{
    int weight,person,value = 0;
    cin >> n;
    for(int i=0;i<n;i++)
    {
        Obj o;
        cin>>o.v>>o.w;
        a[i] = o;
    }
    cin>>person;
    while(person--)
    {
        best_val = 0;
        cin >> weight;
        value += ComputeKnapsack(n,weight);
    }
    cout<<value<<endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign12_10130.txt", "r", stdin);
	int test;
	cin>>test;
	while(test--)
    {
        Compute();
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
