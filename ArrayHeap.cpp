// GROUP:   1
// ID:      20150009
// Assign:  01
// Assign:  ArrayHeap
// UVA:     10954
// Name:    Ahmed Ayman Hammad

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
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

template<class Elem>
struct Heap
{
	Array<Elem> arr;
	bool (*IsBefore)(int&, int&);

	void Initialize(bool (*_IsBefore)(int&, int&))
	{
	    IsBefore = _IsBefore;
	    arr.Initialize();
	}

	void Destroy()
	{
        arr.Destroy();
	}

	int Child(int i)
	{
        return i*2+1;
	}

	int Parent(int i)
	{
	    return (i-1)/2;
	}

	void Print()
	{
	    arr.Print();
	}

	void MoveUp(int ind)
	{
        if(ind == 0)
        {
            return;
        }
        int parentInd = Parent(ind);
        if(IsBefore(arr[ind],arr[parentInd]))
        {
            int temp = arr[parentInd];
            arr[parentInd] = arr[ind];
            arr[ind] = temp;
            MoveUp(parentInd);
        }
	}

	void MoveDown(int ind)
	{
	    int leftChildInd = Child(ind);
	    int rightChildInd = Child(ind) + 1;
	    if(leftChildInd >= arr.n)
        {
            return;
        }
        int minInd = ind;
        if(IsBefore(arr[leftChildInd],arr[ind]))
        {
            minInd = leftChildInd;
        }
        if(rightChildInd < arr.n)
        {
            if(IsBefore(arr[rightChildInd],arr[minInd]))
            {
                minInd = rightChildInd;
            }
        }
        if(minInd != ind)
        {
            int temp = arr[ind];
            arr[ind] = arr[minInd];
            arr[minInd] = temp;
            MoveDown(minInd);
        }
	}

	void Add(Elem e)
	{
	    int n = arr.n;
	    arr.AddLast(e);
	    MoveUp(n);
	}

	Elem GetFirst()
	{
        return arr[0];
	}

	Elem RetrieveFirst()
	{
        if(arr.n == 0)
        {
            return 0;
        }
        int first = arr[0];
        arr[0] = arr[arr.n-1];
        arr.RemoveLast();
        MoveDown(0);
        return first;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBeforeInt(int& a, int& b)
{
	return a<b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Heap<int> heap;
    int sz,input;
    while(true)
    {
        heap.Initialize(IsBeforeInt);
        cin >> sz;
        if(sz == 0)
        {
            break;
        }
        for(int i = 0; i < sz; i++)
        {
            cin >> input;
            heap.Add(input);
        }
        int sum = 0;
        int cost = 0;
        while(heap.arr.n > 1)
        {
            sum = heap.RetrieveFirst();
            sum += heap.RetrieveFirst();
            cost += sum;
            heap.Add(sum);
        }
        cout << cost << endl;
        heap.Destroy();
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
