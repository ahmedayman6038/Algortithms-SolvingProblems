// GROUP:   CS_1
// ID:      20150009
// Assign:  09
// Assign:  Knapsack
// UVA:     10130
// Name:    Ahmed Ayman Hammad
// UVA Username: ahmedayman6038

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
	int v; // value (price) of object
	int w; // weight of object
};

Obj a[1000];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[1001][31];
int Knapsack1(int n, int w)
{
   if(T1[n][w] == -1)
    {
        if(a[n].w > w)
        {
            T1[n][w] = Knapsack1(n - 1, w);
        }
        else
        {
            T1[n][w] = max(Knapsack1(n - 1, w), Knapsack1(n - 1, w - a[n].w) + a[n].v);
        }
    }
    return T1[n][w];
}
int ComputeKnapsack1(int N, int W) // Recursive - memoization - initialize T then call Knapsack1(N,W);
{
    for(int i = 0; i <= N+1; i++)
    {
        for(int j = 0; j <= W+1; j++)
        {
            T1[i][j] = -1;
        }
    }
    return Knapsack1(N,W);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[1001][31];
int ComputeKnapsack2(int N, int W)  // Bottom-up, do not save space
{
   for (int i = 0; i <= N; i++)
   {
       for (int j = 0; j <= W; j++)
       {
           if (i==0 || j==0)
           {
               T2[i][j] = 0;
           }
           else if (a[i-1].w <= j)
           {
               T2[i][j] = max(a[i-1].v + T2[i-1][j-a[i-1].w],  T2[i-1][j]);
           }
           else
           {
               T2[i][j] = T2[i-1][j];
           }
       }
   }
   return T2[N][W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][31];
int ComputeKnapsack3(int N, int W)  // Bottom-up, use two rows only
{
    int cur= 0;
     for (int n = 0; n <= N; n++)
     {
       for (int w = W; w >= 0; w--)
       {
           if(n==0)
           {
                T3[cur][w] = 0;
                continue;
           }
           T3[cur][w] =T3[1-cur][w];
           int cw = a[n-1].w;
           int cv = a[n-1].v;
           if(cw<=w)
           {
               int r =cv+T3[1-cur][w-cw];
                if(r>T3[cur][w]){
                    T3[cur][w] = r;
                }
           }
       }
        cur = 1 -cur;
     }
     return T3[1-cur][W];


}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[31];
int ComputeKnapsack4(int N, int W)  // Bottom-up, save maximum space
{
    int cw= 0;
     for (int n = 0; n <= N; n++)
     {
       for (int w = W; w >= 0; w--)
       {
           if(n==0)
           {
                T4[w] = 0;
                continue;
           }
           cw = a[n-1].w;
           int cv = a[n-1].v;
           if(cw<=w)
           {
               int r =cv+T4[w-cw];
                if(r>T4[w]){
                    T4[w] = r;
                }
           }
       }
     }
     return T4[W];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeKnapsack(int N, int W) // Here we can choose the method
{
	return ComputeKnapsack1(N,W);
	//return ComputeKnapsack2(N,W);
	//return ComputeKnapsack3(N,W);
	//return ComputeKnapsack4(N,W);
}

void Compute() // Get input and call ComputeKnapsack() whenever needed
{
    int item,weight,person,value = 0;
    cin >> item;
    for(int i=0;i<item;i++)
    {
        Obj o;
        cin>>o.v>>o.w;
        a[i] = o;
    }
    cin>>person;
    while(person--)
    {
        cin >> weight;
        value += ComputeKnapsack(item,weight);
    }
    cout<<value<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign09_10130.txt", "r", stdin);
	int test;
	cin>>test;
	while(test--)
    {
        Compute();
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
