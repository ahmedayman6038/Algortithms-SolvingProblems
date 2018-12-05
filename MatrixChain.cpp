// GROUP:   G1
// ID:      20150009
// Assign:  10
// Assign:  MatChain
// UVA:     348
// Name:    Ahmed Ayman Hammad
// UVA Username: ahmedayman6038

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int p[11]; // the dimensions of matrices

int T[11][11]; // T[a][b]=the optimal number of multiplication of p[a]...p[b]
int D[11][11]; // D[a][b]=the decision (value of k) that gets T[a][b]

// Top down version
int MatChain(int a, int b) // Recursive, cost of multiplying the b-a matrices with indexes: a...b-1
{
    if(a+1 == b)
    {
        T[a][b] = 0;
        return 0;
    }
    if(T[a][b]>=0)
    {
        return T[a][b];
    }
    int k;
    T[a][b] =0x7fffffff;
    for(k=a+1;k<b;k++)
    {
        int v = MatChain(a,k)+MatChain(k,b)+p[a]*p[k]*p[b];
        if(v < T[a][b])
        {
            T[a][b] = v;
            D[a][b] = k;
        }
    }
}
void MatChainTopDown(int n) // Initialize T then call MatChain(0,n)
{
     for(int i = 0; i <11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            T[i][j] = -1;
        }
    }
    MatChain(0,n);
}

// BottomUp version
int MatChainBottomUp(int n)
{
    int a,b;
    for(int s=1; s<=n; s++)
    {
        for( a=0; a+s<=n; a++)
        {
            b=a+s;
            if(a+1==b)
            {
                T[a][b]=0;
                continue;
            }
            T[a][b]=0x7FFFFFFF;
            int k;
            for(k=a+1; k<b; k++)
            {
                int v=MatChain(a,k)+MatChain(k,b)+p[a]*p[k]*p[b];
                if(v<T[a][b])
                {
                    T[a][b]=v;
                    D[a][b]=k;
                }
            }

        }
    }
}


// Recursive to output the solution for both versions
void MatChainSol(int a, int b)
{
    int k = D[a][b];
    if(a+1 == b)
    {
        cout<<"A"<<b;
    }
    else
    {
        k = D[a][b];
        cout<<"(";
        MatChainSol(a,k);
        cout<<" x ";
        MatChainSol(k,b);
        cout<<")";
    }
}

void Compute()
{
    int cases;
    int counter = 1;
	while(true){
        cin>>cases;
        if(cases == 0){
            break;
        }
        int c=0;
        for(int i=0;i<cases;i++)
        {
            int x,y;
            cin>> x>>y;
            p[c]=x;
            c++;
            p[c]=y;
        }
        MatChainTopDown(cases);
       // MatChainBottomUp(cases);
        cout<<"Case "<<counter<<": ";
        MatChainSol(0,cases);
        cout<<endl;
        counter++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign10_00348.txt", "r", stdin);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
