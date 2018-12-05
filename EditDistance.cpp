// GROUP:   G1
// ID:      20150009
// Assign:  11
// Assign:  EditDist
// UVA:     526
// Name:    ahmed ayman hammad
// UVA Username: ahmedayman6038

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

char a[82];
char b[82];

int D[81][81]; // D[][] is the same for all versions (no memory reduction)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[81][81];
int EditDist1(int n, int m)
{
    int oper;
    if(T1[n][m] != -1)
    {
        return T1[n][m];
    }
	if (n == 0)
    {
        T1[n][m]= m;
        return m;
    }
    if (m == 0)
    {
        T1[n][m]= n;
        return n;
    }
	if (a[n - 1] == b[m - 1])
    {
        T1[n][m] = EditDist1(n - 1, m - 1);
        oper = 0;
    }
    else
    {
        int ins = 1 + EditDist1(n, m - 1);
        int del = 1 + EditDist1(n - 1, m);
        int rep = 1 + EditDist1(n - 1, m - 1);
        int min = ins; oper = 1;
        if (del < min)
        {
            min = del; oper = 2;
        }
        if (rep < min)
        {
            min = rep; oper = 3;
        }
        T1[n][m] = min;
    }
    D[n][m] = oper;
	return T1[n][m];
}
int ComputeEditDist1(int N, int M) // Recursive - memoization - initialize T then call EditDist1(N,M);
{
    for(int i = 0; i <= N; i++)
    {
        for(int j = 0; j <= M; j++)
        {
            T1[i][j] = -1;
        }
    }
    return EditDist1(N,M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[81][81];
int ComputeEditDist2(int N, int M) // Bottom-up, do not save space
{
    int oper;
    for (int n = 0; n <= N; n++)
	{
		for (int m = 0; m <= M; m++)
		{
			if (n == 0)
            {
                T2[n][m]= m;
                continue;
            }
            if (m == 0)
            {
                T2[n][m]= n;
                continue;
            }
            if (a[n - 1] == b[m - 1])
            {
                T2[n][m] = T2[n - 1][m - 1];
                oper = 0;
            }
            else
            {
                int ins = 1 + T2[n][m - 1];
                int del = 1 + T2[n - 1][m];
                int rep = 1 + T2[n - 1][m - 1];
                int min = ins; oper = 1;
                if (del < min)
                {
                    min = del; oper = 2;
                }
                if (rep < min)
                {
                    min = rep; oper = 3;
                }
                T2[n][m] = min;
            }
            D[n][m] = oper;
		}
	}
	return T2[N][M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][81];
int ComputeEditDist3(int N, int M) // Bottom-up, use two rows only
{
    int cur = 0;
    int oper;
    for (int n = 0; n <= N; n++)
	{
		for (int m = 0; m <= M; m++)
		{
			if (n == 0)
            {
                T3[cur][m]= m;
                continue;
            }
            if (m == 0)
            {
                T3[cur][m]= n;
                continue;
            }
            if (a[n - 1] == b[m - 1])
            {
                T3[cur][m] = T3[1-cur][m - 1];
                oper = 0;
            }
            else
            {
                int ins = 1 + T3[cur][m - 1];
                int del = 1 + T3[1-cur][m];
                int rep = 1 + T3[1-cur][m - 1];
                int min = ins; oper = 1;
                if (del < min)
                {
                    min = del; oper = 2;
                }
                if (rep < min)
                {
                    min = rep; oper = 3;
                }
                T3[cur][m] = min;
            }
            D[n][m] = oper;
		}
		cur = 1 - cur;
	}
	return T3[1-cur][M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[81];
int ComputeEditDist4(int N, int M) // Bottom-up, save maximum space
{
    int cur;
    int oper;
    for (int n = 0; n <= N; n++)
	{
		for (int m = 0; m <= M; m++)
		{
			if (n == 0)
            {
                cur = T4[m];
                T4[m]= m;
                continue;
            }
            if (m == 0)
            {
                cur = T4[m];
                T4[m]= n;
                continue;
            }
            if (a[n - 1] == b[m - 1])
            {
                int temp = cur;
                cur = T4[m];
                T4[m] = temp;
                oper = 0;
            }
            else
            {
                int ins = 1 + T4[m - 1];
                int del = 1 + T4[m];
                int rep = 1 + cur;
                int min = ins; oper = 1;
                if (del < min)
                {
                    min = del; oper = 2;
                }
                if (rep < min)
                {
                    min = rep; oper = 3;
                }
                cur = T4[m];
                T4[m] = min;
            }
            D[n][m] = oper;
		}
	}
	return T4[M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Oper
{
	int n,m;
	int oper;
};

Oper opers[81];

int EditDistSol(int N, int M) // Print the solution using D[][]
{
	int i = 0;
	while (N > 0 || M > 0)
	{
	    if (D[N][M] == 1 || (N == 0 && M != 0))
		{
			Oper ins;
			ins.oper = 1;
			ins.n = N + 1;
			ins.m = M - 1;
			opers[i++] = ins;
			M -= 1;
			continue;
		}
		else if (D[N][M] == 2 || (N != 0 && M == 0))
		{
			Oper del;
			del.oper = 2;
			del.n = N;
			opers[i++] = del;
			N -= 1;
			continue;
		}
		else if (D[N][M] == 3)
		{
			Oper rep;
			rep.oper = 3;
			rep.n = N;
			rep.m = M - 1;
			opers[i++] = rep;
			N -= 1;
			M -= 1;
			continue;
		}
		N--; M--;
	}
	for (int j = 0; j < i; j++)
	{
        if(opers[j].oper == 1){
            cout<<j+1<<" Insert "<<opers[j].n<<","<<b[opers[j].m]<<endl;
        }
        if(opers[j].oper == 2){
            cout<<j+1<<" Delete "<<opers[j].n<<endl;
        }
        if(opers[j].oper == 3){
            cout<<j+1<<" Replace "<<opers[j].n<<","<<b[opers[j].m]<<endl;
        }
	}
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeEditDist(int N, int M) // Here we can choose the method
{
	//return ComputeEditDist1(N,M);
	//return ComputeEditDist2(N,M);
	//return ComputeEditDist3(N,M);
	return ComputeEditDist4(N,M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function does not need any modification:
void Compute() // Get input and call ComputeEditDist() whenever needed
{
	int cas=0;
	while(true)
	{
		a[0]=0; b[0]=0;
		if(!fgets(a,82,stdin)) break; fgets(b,82,stdin);
		a[strlen(a)-1]=0;
		b[strlen(b)-1]=0;
		if(cas) cout<<endl; // print an empty line between test cases
		int N=strlen(a), M=strlen(b);
		cout<<ComputeEditDist(N,M)<<endl;
		EditDistSol(N,M);
		cas++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign11_00526.txt", "r", stdin);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
