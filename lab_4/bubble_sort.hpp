#ifndef bubble_sort_hpp
#define bubble_sort_hpp
#include "interface.hpp"

template<typename T>
class bubble_sort: public sorts<T>{
public:
    void sort(Sequence<T>& arr, bool(*cmp)(const T&, const T&)) {
        for (int i = 0; i < arr.GetLength(); i++){
            for (int k = 0; k < arr.GetLength() - 1; k++){
                if (cmp(arr.Get(k), arr.Get(k + 1))){
                    int tmp = arr.Get(k);
                    arr.Set(k, arr.Get(k+1));
                    arr.Set(k + 1, tmp);
            }
        }
    }
    }
};

#endif