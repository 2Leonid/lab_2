#ifndef heap_sort_hpp
#define heap_sort_hpp
#include "interface.hpp"

template<typename T>
class heap_sort: public sorts<T>{
public:
    void sort(Sequence<T> & arr, bool (*cmp)(const T&, const T&)){
        heapSort(arr, cmp);
    }

    void heapify(Sequence<T> & arr,int n ,int i, bool (*cmp)(const T&, const T&)){
        int largest = i;   
        int l = 2*i + 1;
        int r = 2*i + 2;
        if (l < n && cmp(arr.Get(largest) , arr.Get(l) ) )
            largest = l;

        if (r < n && cmp(arr.Get(largest), arr.Get(r)) )
            largest = r;

        if (largest != i)
        {
            T tmp = arr.Get(i);
            arr.Set(i, arr.Get(largest));
            arr.Set(largest, tmp);

            heapify(arr, n, largest, cmp);
        }
    }

    void heapSort(Sequence<T> & arr, bool (*cmp)(const T&, const T&))
    {
        for (int i = arr.GetLength() / 2 - 1; i >= 0; i--)
            heapify(arr, arr.GetLength(), i, cmp);

        for (int i=arr.GetLength()-1; i>=0; i--)
        {
            T tmp = arr.Get(0);
            arr.Set(0, arr.Get(i));
            arr.Set(i, tmp);

            heapify(arr, i, 0, cmp);
        }

    }
};

#endif