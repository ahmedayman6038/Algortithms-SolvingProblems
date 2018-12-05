// GROUP:   G1
// ID:      20150009
// Assign:  04
// Assign:  CountInv
// UVA:     10810
// Name:    Ahmed Ayman Hammad
// UVA username: ahmedayman6038
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

long long CountInv(long long* a, long long n)
{
    long long mid = n/2;
    long long temp[n];
    long long i = 0;
    long long j = mid;
    long long k = 0;
    long long countInver = 0;
    while(i < mid && j <= n-1)
    {
        if(a[i] <= a[j])
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
            countInver += (mid - i);
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
    for (long long i = 0 ; i < n ; i++)
    {
        a[i] = temp[i];
    }
    return countInver;
}

long long CountInvMerge(long long* a, long long n)
{
    long long countInver = 0;
    long long mid;
    if(n > 1)
    {
        mid = n/2;
        countInver = CountInvMerge(a, mid);
        countInver += CountInvMerge(a + (mid), n - mid);
        countInver += CountInv(a, n);
    }
    return countInver;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    long long n;
    input : cin >> n;
    while(n != 0)
    {
        long long *arr = new long long[n];
        for(long long i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        cout << CountInvMerge(arr, n) <<"\n";
        goto input;
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
